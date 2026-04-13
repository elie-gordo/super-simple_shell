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
    /* execve needs a NULL-terminated argv array. */
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

    /* Launch the command in 5 distinct children, one after another. */
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
            /* Child process: replace itself with /bin/ls. */
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("execve");
                return (1);
            }
        }
        else
        {
            /* Parent process: wait before creating the next child. */
            if (wait(&status) == -1)
            {
                perror("wait");
                return (1);
            }
        }
    }

    return (0);
}
