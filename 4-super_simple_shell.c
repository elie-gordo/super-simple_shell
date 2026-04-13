#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

/**
 * main - super simple shell: executes full-path commands without arguments
 *
 * Return: 0 on success
 */
int main(void)
{
    char *line;
    size_t len;
    ssize_t nread;
    pid_t child_pid;
    int status;
    char *argv[2];

    /* getline manages allocation/reallocation of this buffer. */
    line = NULL;
    len = 0;

    /* Infinite REPL loop: prompt -> read -> execute -> wait. */
    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        /* EOF (Ctrl+D) or read error: exit shell loop. */
        if (nread == -1)
            break;

        /* Drop trailing newline so execve receives a clean path string. */
        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Ignore empty commands and show prompt again. */
        if (line[0] == '\0')
            continue;

        child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            free(line);
            return (1);
        }

        if (child_pid == 0)
        {
            /* This first shell version accepts only full path, no arguments. */
            argv[0] = line;
            argv[1] = NULL;
            /* Keep current environment so executed program sees PATH/HOME/etc. */
            if (execve(argv[0], argv, environ) == -1)
            {
                perror("execve");
                return (1);
            }
        }
        else
        {
            /* Parent blocks until child terminates (simple, deterministic flow). */
            wait(&status);
        }
    }

    /* Release getline buffer before exiting program. */
    free(line);
    return (0);
}
