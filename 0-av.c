#include <stdio.h>

/**
 * main - affiche tous les arguments sans utiliser ac
 * @ac: nombre d'arguments (non utilise)
 * @av: tableau des arguments
 *
 * Return: 0 en cas de succes
 */
int main(int ac, char **av)
{
    unsigned int i;

    /* ac est volontairement ignore: la consigne impose d'utiliser uniquement av. */
    (void)ac;
    /* On part de av[0] (nom du programme) jusqu'au marqueur final NULL. */
    i = 0;
    while (av[i] != NULL)
    {
        /* Affiche un argument par ligne pour voir la structure exacte de av. */
        printf("%s\n", av[i]);
        i++;
    }

    return (0);
}
