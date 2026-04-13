#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_path_dirs - affiche chaque dossier de PATH sur sa propre ligne
 *
 * Return: rien
 */
void print_path_dirs(void)
{
    char *path_env;
    char *path_copy;
    char *dir;

    /* Lit PATH depuis l'environnement du processus courant. */
    path_env = getenv("PATH");
    if (path_env == NULL)
        return;

    /* Duplique PATH avant strtok, car strtok modifie la chaine. */
    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return;

    /* Affiche un dossier par ligne, comme demande dans l'exercice. */
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        printf("%s\n", dir);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
}
