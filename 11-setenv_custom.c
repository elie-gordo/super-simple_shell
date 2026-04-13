#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _setenv - adds or changes an environment variable
 * @name: variable name
 * @value: variable value
 * @overwrite: overwrite existing value if non-zero
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    size_t i;
    size_t name_len;
    size_t entry_len;
    char *entry;
    char **new_environ;

    if (name == NULL || value == NULL || *name == '\0' || strchr(name, '=') != NULL)
        return (-1);

    name_len = strlen(name);
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            if (!overwrite)
                return (0);

            entry_len = name_len + 1 + strlen(value) + 1;
            entry = malloc(entry_len);
            if (entry == NULL)
                return (-1);
            snprintf(entry, entry_len, "%s=%s", name, value);
            environ[i] = entry;
            return (0);
        }
    }

    entry_len = name_len + 1 + strlen(value) + 1;
    entry = malloc(entry_len);
    if (entry == NULL)
        return (-1);
    snprintf(entry, entry_len, "%s=%s", name, value);

    new_environ = malloc((i + 2) * sizeof(char *));
    if (new_environ == NULL)
    {
        free(entry);
        return (-1);
    }

    for (name_len = 0; name_len < i; name_len++)
        new_environ[name_len] = environ[name_len];

    environ = new_environ;
    environ[i] = entry;
    environ[i + 1] = NULL;

    return (0);
}
