#include <string.h>
#include "environ_custom.h"

/**
 * _getenv - recupere la valeur d'une variable d'environnement
 * @name: nom de la variable
 *
 * Return: pointeur vers la valeur, ou NULL si non trouvee
 */
char *_getenv(const char *name)
{
	size_t name_len;
	char **env;

	/* Reject invalid names early. */
	if (name == NULL || *name == '\0')
		return (NULL);
	/* Compute once for repeated prefix checks. */
	name_len = strlen(name);
	env = environ;
	while (*env != NULL)
	{
		/* Exact variable match must be followed by '='. */
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			/* Return pointer right after '=' to expose only value. */
			return (&((*env)[name_len + 1]));
		/* Move to next environment entry. */
		env++;
	}
	return (NULL);
}
