#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * print_found_path - affiche le premier executable correspondant dans PATH
 * @filename: fichier a rechercher
 *
 * Return: 0 si trouve, 1 sinon
 */
int print_found_path(const char *filename)
{
    char *path_env;
    char *path_copy;
    char *dir;
    char *fullpath;
    size_t needed;
    struct stat st;

    /* PATH est une liste de dossiers separes par ':'. */
    path_env = getenv("PATH");
    if (path_env == NULL)
        return (1);

    /* Duplique PATH car strtok modifie la chaine en place. */
    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return (1);

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        /* Reserve l'espace pour "dir" + '/' + "filename" + '\0'. */
        needed = strlen(dir) + 1 + strlen(filename) + 1;
        fullpath = malloc(needed);
        if (fullpath == NULL)
        {
            free(path_copy);
            return (1);
        }

        /* Construit le chemin candidat de facon bornee et sure. */
        snprintf(fullpath, needed, "%s/%s", dir, filename);

        /* stat == 0 signifie que le fichier existe a cet emplacement. */
        if (stat(fullpath, &st) == 0)
        {
            printf("%s\n", fullpath);
            free(fullpath);
            free(path_copy);
            return (0);
        }

        free(fullpath);
        /* Passe au dossier suivant de PATH. */
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (1);
}

/**
 * main - recherche chaque argument de fichier dans PATH
 * @ac: nombre d'arguments
 * @av: tableau des arguments
 *
 * Return: 0 en cas de succes
 */
int main(int ac, char **av)
{
    int i;

    /* Il faut au moins un nom de fichier a chercher. */
    if (ac < 2)
    {
        printf("Usage: %s filename ...\n", av[0]);
        return (1);
    }

    /* Traite chaque argument independamment. */
    for (i = 1; i < ac; i++)
    {
        if (print_found_path(av[i]) != 0)
            printf("%s: not found\n", av[i]);
    }

    return (0);
}
