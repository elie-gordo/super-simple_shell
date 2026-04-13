#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main - affiche un prompt, lit une ligne, puis l'affiche
 *
 * Return: 0 en cas de succes
 */
int main(void)
{
    char *line;
    size_t len;
    ssize_t nread;

    /* getline alloue/agrandit ce buffer automatiquement. */
    line = NULL;
    len = 0;

    while (1)
    {
        /* Affiche le prompt avant d'attendre la saisie utilisateur. */
        printf("$ ");
        /* Force l'affichage immediat du prompt (mode interactif). */
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        /* EOF (Ctrl+D) ou erreur: on sort proprement de la boucle. */
        if (nread == -1)
            break;

        /* Reaffiche exactement la ligne saisie. */
        printf("%s", line);
    }

    /* Libere la memoire allouee par getline. */
    free(line);
    return (0);
}
