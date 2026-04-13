#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - executes "ls -l /tmp" in 5 child processes, one after another
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    pid_t child_pid;
    int status;
    int i;
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

    for (i = 0; i < 5; i++)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            return (1);
        }

        if (child_pid == 0)
        {
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("execve");
                return (1);
            }
        }
        else
        {
            if (wait(&status) == -1)
            {
                perror("wait");
                return (1);
            }
        }
    }

    return (0);
}
