#include <stdio.h>
#include "environ_custom.h"

/**
 * main - affiche l'environnement via la variable globale environ
 *
 * Return: 0 en cas de succes
 */
int main(void)
{
	unsigned int i;

	/* environ is NULL-terminated: iterate until sentinel. */
	i = 0;
	while (environ[i] != NULL)
	{
		/* Each entry has NAME=value format. */
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
