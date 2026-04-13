#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main - prints a prompt, reads a line, and prints it
 *
 * Return: 0 on success
 */
int main(void)
{
    char *line;
    size_t len;
    ssize_t nread;

    line = NULL;
    len = 0;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
            break;

        printf("%s", line);
    }

    free(line);
    return (0);
}
