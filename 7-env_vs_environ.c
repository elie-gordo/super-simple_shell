#include <stdio.h>

extern char **environ;

/**
 * main - affiche les adresses de env et environ
 * @ac: nombre d'arguments (non utilise)
 * @av: tableau des arguments (non utilise)
 * @env: environnement recu comme 3e parametre de main
 *
 * Return: 0 en cas de succes
 */
int main(int ac, char **av, char **env)
{
    /* Signature complete gardee pour montrer explicitement le parametre env. */
    (void)ac;
    (void)av;

    /* Compare les adresses pour voir si les deux pointeurs visent la meme table. */
    printf("Address of env:     %p\n", (void *)env);
    printf("Address of environ: %p\n", (void *)environ);

    return (0);
}
