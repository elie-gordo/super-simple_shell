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

    /* Demande au noyau le PID du processus qui a lance ce programme. */
    parent_pid = getppid();
    /* Affiche la valeur dans un format simple a lire dans le terminal. */
    printf("%u\n", (unsigned int)parent_pid);

    return (0);
}
