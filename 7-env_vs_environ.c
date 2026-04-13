#include <stdio.h>
#include "environ_custom.h"

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
	/* Keep full signature for demonstration, ignore unused args. */
	(void)ac;
	(void)av;
	/* Show both pointers to compare address identity in practice. */
	printf("Address of env: %p\n", (void *)env);
	printf("Address of environ: %p\n", (void *)environ);
	return (0);
}
