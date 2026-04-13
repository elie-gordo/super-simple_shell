#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main - affiche l'identifiant du processus parent (PPID)
 *
 * Return: 0 en cas de succes
 */
int main(void)
{
	pid_t parent_pid;

	/* Ask the kernel for the parent process identifier. */
	parent_pid = getppid();
	/* Print it once, one value per line for easy testing. */
	printf("%u\n", (unsigned int)parent_pid);

	return (0);
}
