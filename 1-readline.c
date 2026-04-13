#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main - affiche un prompt, lit une ligne, puis l'affiche
 *
 * Return: 0 en cas de succes
 */
int main(void)
{
	char *line;
	size_t len;
	ssize_t nread;

	/* Let getline allocate and grow this buffer as needed. */
	line = NULL;
	len = 0;
	while (1)
	{
		/* Prompt before reading user input. */
		printf("$ ");
		/* Force prompt display in interactive mode. */
		fflush(stdout);
		/* Read one full line, including spaces, until newline or EOF. */
		nread = getline(&line, &len, stdin);
		/* Stop on EOF (Ctrl+D) or read error. */
		if (nread == -1)
			break;
		/* Echo the exact line that was typed. */
		printf("%s", line);
	}
	/* Release memory allocated by getline before exit. */
	free(line);
	return (0);
}
