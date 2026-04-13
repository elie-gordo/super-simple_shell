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

    parent_pid = getppid();
    printf("%u\n", (unsigned int)parent_pid);

    return (0);
}
