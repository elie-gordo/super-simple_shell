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

    line = NULL;
    len = 0;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
            break;

        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

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
            argv[0] = line;
            argv[1] = NULL;
            if (execve(argv[0], argv, environ) == -1)
            {
                perror("execve");
                return (1);
            }
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (0);
}
