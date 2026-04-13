#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main - prints the parent process id (PPID)
 *
 * Return: 0 on success
 */
int main(void)
{
    pid_t parent_pid;

    /* Ask the kernel for the PID of the process that started this program. */
    parent_pid = getppid();
    /* Print it as an unsigned integer for easy reading in the terminal. */
    printf("%u\n", (unsigned int)parent_pid);

    return (0);
}
