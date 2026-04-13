#include <string.h>

extern char **environ;

/**
 * _getenv - gets an environment variable value
 * @name: variable name
 *
 * Return: pointer to value string, or NULL if not found
 */
char *_getenv(const char *name)
{
    size_t name_len;
    char **env;

    if (name == NULL || *name == '\0')
        return (NULL);

    name_len = strlen(name);
    env = environ;

    while (*env != NULL)
    {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
            return (&((*env)[name_len + 1]));
        env++;
    }

    return (NULL);
}
