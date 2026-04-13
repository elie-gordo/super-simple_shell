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

	/* ac is intentionally unused: the exercise forbids using it. */
	(void)ac;
	/* Start from argv[0] and walk until the final NULL pointer. */
	i = 0;
	while (av[i] != NULL)
	{
		/* Print each argument on its own line. */
		printf("%s\n", av[i]);
		i++;
	}

	return (0);
}
