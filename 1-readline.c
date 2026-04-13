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

    /* getline will allocate/resize this buffer for us. */
    line = NULL;
    len = 0;

    while (1)
    {
        /* Print shell-like prompt before waiting for input. */
        printf("$ ");
        /* Force prompt to appear immediately (important in interactive mode). */
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        /* EOF (Ctrl+D) or read error: stop the loop cleanly. */
        if (nread == -1)
            break;

        /* Echo back the exact command line that was entered. */
        printf("%s", line);
    }

    /* Release memory allocated by getline. */
    free(line);
    return (0);
}
