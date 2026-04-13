#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - execute "ls -l /tmp" dans 5 processus enfants, l'un apres l'autre
 *
 * Return: 0 en cas de succes, 1 en cas d'echec
 */
int main(void)
{
	pid_t child_pid;
	int status;
	int i;
	/* argv for execve: command, arg1, arg2, NULL sentinel. */
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

	/* Create 5 children sequentially, one command execution per child. */
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
			/* Child replaces itself with /bin/ls. */
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve");
				return (1);
			}
		}
		else
		{
			/* Parent waits before starting the next iteration. */
			if (wait(&status) == -1)
			{
				perror("wait");
				return (1);
			}
		}
	}
	return (0);
}
