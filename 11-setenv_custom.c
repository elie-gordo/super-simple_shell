#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environ_custom.h"

/**
 * make_entry - build NAME=value string
 * @name: variable name
 * @value: variable value
 *
 * Return: allocated string or NULL
 */
static char *make_entry(const char *name, const char *value)
{
	size_t len;
	char *entry;

	/* NAME + '=' + VALUE + '\0'. */
	len = strlen(name) + strlen(value) + 2;
	entry = malloc(len);
	if (entry == NULL)
		return (NULL);
	/* Build canonical environment entry representation. */
	snprintf(entry, len, "%s=%s", name, value);
	return (entry);
}

/**
 * append_entry - append new entry to environ
 * @entry: allocated NAME=value string
 *
 * Return: 0 on success, -1 on failure
 */
static int append_entry(char *entry)
{
	size_t i;
	char **new_env;

	/* Count existing entries. */
	for (i = 0; environ[i] != NULL; i++)
		;
	/* Allocate new pointer table: old entries + new one + NULL. */
	new_env = malloc((i + 2) * sizeof(char *));
	if (new_env == NULL)
		return (-1);
	/* Copy pointers and append new entry at the end. */
	for (i = 0; environ[i] != NULL; i++)
		new_env[i] = environ[i];
	new_env[i] = entry;
	new_env[i + 1] = NULL;
	environ = new_env;
	return (0);
}

/**
 * _setenv - add or change an environment variable
 * @name: variable name
 * @value: variable value
 * @overwrite: replace existing value when non-zero
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t i;
	size_t name_len;
	char *entry;

	/* Reject invalid input according to setenv rules. */
	if (name == NULL || value == NULL)
		return (-1);
	if (*name == '\0' || strchr(name, '=') != NULL)
		return (-1);
	name_len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Compare variable name before '='. */
		if (strncmp(environ[i], name, name_len) == 0)
		{
			if (environ[i][name_len] != '=')
				continue;
			/* Keep current value if overwrite is disabled. */
			if (!overwrite)
				return (0);
			/* Replace existing entry with freshly built NAME=value. */
			entry = make_entry(name, value);
			if (entry == NULL)
				return (-1);
			environ[i] = entry;
			return (0);
		}
	}
	entry = make_entry(name, value);
	if (entry == NULL)
		return (-1);
	/* Variable not found: append as new environment entry. */
	if (append_entry(entry) == -1)
	{
		free(entry);
		return (-1);
	}
	return (0);
}
