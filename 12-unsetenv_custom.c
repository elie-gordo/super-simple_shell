#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <unistd.h>
#include "environ_custom.h"

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

	/* Validate variable name syntax first. */
	if (name == NULL || *name == '\0')
		return (-1);
	if (strchr(name, '=') != NULL)
		return (-1);
	name_len = strlen(name);
	/* Scan environ and remove all matching NAME=... entries. */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0)
		{
			if (environ[i][name_len] != '=')
				continue;
			/* Shift left to fill removed slot and keep NULL termination. */
			for (j = i; environ[j] != NULL; j++)
				environ[j] = environ[j + 1];
			/* Re-check same index because a new entry moved into it. */
			i--;
		}
	}
	return (0);
}
