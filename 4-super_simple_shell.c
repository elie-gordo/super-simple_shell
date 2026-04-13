#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

/**
 * main - shell tres simple: execute des commandes en chemin complet sans arguments
 *
 * Return: 0 en cas de succes
 */
int main(void)
{
    char *line;
    size_t len;
    ssize_t nread;
    pid_t child_pid;
    int status;
    char *argv[2];

    /* getline gere l'allocation/reallocation de ce buffer. */
    line = NULL;
    len = 0;

    /* Boucle REPL infinie: prompt -> lecture -> execution -> attente. */
    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        /* EOF (Ctrl+D) ou erreur de lecture: on sort du shell. */
        if (nread == -1)
            break;

        /* Supprime le '\n' final pour donner a execve un chemin propre. */
        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Ignore les lignes vides et reaffiche le prompt. */
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
            /* Cette premiere version accepte uniquement un chemin complet, sans argument. */
            argv[0] = line;
            argv[1] = NULL;
            /* Conserve l'environnement courant (PATH/HOME/etc.) pour le programme lance. */
            if (execve(argv[0], argv, environ) == -1)
            {
                perror("execve");
                return (1);
            }
        }
        else
        {
            /* Le parent attend la fin de l'enfant (flux simple et deterministe). */
            wait(&status);
        }
    }

    /* Libere le buffer getline avant de quitter le programme. */
    free(line);
    return (0);
}
