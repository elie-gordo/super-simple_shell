#define _POSIX_C_SOURCE 200809L
#include <string.h>

extern char **environ;

/**
 * _unsetenv - removes an environment variable from environ
 * @name: variable name
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
    size_t i;
    size_t j;
    size_t name_len;

    /* Reject invalid variable names. */
    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
        return (-1);

    name_len = strlen(name);

    /* Scan environ and remove every matching NAME=... occurrence. */
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            /* Shift left to overwrite removed entry and keep array contiguous. */
            for (j = i; environ[j] != NULL; j++)
                environ[j] = environ[j + 1];
            /* Re-check same index because a new entry moved into position i. */
            i--;
        }
    }

    return (0);
}
