#include <stdio.h>

extern char **environ;

/**
 * main - affiche l'environnement via la variable globale environ
 *
 * Return: 0 en cas de succes
 */
int main(void)
{
    unsigned int i;

    /* environ est termine par NULL: on parcourt jusqu'a ce marqueur. */
    i = 0;
    while (environ[i] != NULL)
    {
        /* Chaque entree respecte le format NOM=valeur. */
        printf("%s\n", environ[i]);
        i++;
    }

    return (0);
}
