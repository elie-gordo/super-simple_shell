#define _POSIX_C_SOURCE 200809L
#include <string.h>

extern char **environ;

/**
 * _unsetenv - supprime une variable d'environnement de environ
 * @name: nom de la variable
 *
 * Return: 0 en cas de succes, -1 en cas d'echec
 */
int _unsetenv(const char *name)
{
    size_t i;
    size_t j;
    size_t name_len;

    /* Rejette les noms de variable invalides. */
    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
        return (-1);

    name_len = strlen(name);

    /* Parcourt environ et supprime chaque occurrence correspondant a NAME=... */
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            /* Decale vers la gauche pour combler le trou et garder un tableau continu. */
            for (j = i; environ[j] != NULL; j++)
                environ[j] = environ[j + 1];
            /* Recontrole le meme index car une nouvelle entree y a ete deplacee. */
            i--;
        }
    }

    return (0);
}
