#include <stdio.h>
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

/**
 * main - demo for _getenv
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    char *value;

    if (ac != 2)
    {
        printf("Usage: %s VARIABLE_NAME\n", av[0]);
        return (1);
    }

    value = _getenv(av[1]);
    if (value == NULL)
        printf("%s not found\n", av[1]);
    else
        printf("%s\n", value);

    return (0);
}
