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

    /* Reject invalid input early. */
    if (name == NULL || *name == '\0')
        return (NULL);

    /* Compute once, reuse in each comparison. */
    name_len = strlen(name);
    env = environ;

    while (*env != NULL)
    {
        /* Match exact variable name followed by '=' (avoid prefix collisions). */
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
            /* Return pointer right after '=' so caller gets only value. */
            return (&((*env)[name_len + 1]));
        env++;
    }

    return (NULL);
}
