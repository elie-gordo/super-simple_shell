#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_line - decoupe une chaine en mots separes par espaces/tabulations/retours ligne
 * @line: chaine d'entree (sera modifiee)
 *
 * Return: tableau de mots termine par NULL, ou NULL en cas d'echec
 */
char **split_line(char *line)
{
    char *token;
    char **words;
    char **tmp;
    size_t size;
    size_t i;

    /* Demarre avec une petite capacite et agrandit si necessaire. */
    size = 8;
    i = 0;
    words = malloc(size * sizeof(char *));
    if (words == NULL)
        return (NULL);

    /* Premier mot avec delimiters blancs (espace/tabulation/newline). */
    token = strtok(line, " \t\n");
    while (token != NULL)
    {
        /* Stocke le pointeur vers le mot dans le buffer d'entree modifie. */
        words[i] = token;
        i++;

        /* Garde toujours une case libre pour le NULL final. */
        if (i + 1 >= size)
        {
            size *= 2;
            tmp = realloc(words, size * sizeof(char *));
            if (tmp == NULL)
            {
                /* Si realloc echoue, libere puis retourne l'echec. */
                free(words);
                return (NULL);
            }
            words = tmp;
        }

        /* Continue la tokenisation a partir de l'etat interne de strtok. */
        token = strtok(NULL, " \t\n");
    }

    /* Termine le tableau comme un argv: dernier element a NULL. */
    words[i] = NULL;
    return (words);
}
