#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
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

    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
        return (-1);

    name_len = strlen(name);

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            for (j = i; environ[j] != NULL; j++)
                environ[j] = environ[j + 1];
            i--;
        }
    }

    return (0);
}

/**
 * main - demo for _unsetenv
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Usage: %s VARIABLE_NAME\n", av[0]);
        return (1);
    }

    if (_unsetenv(av[1]) == -1)
    {
        perror("_unsetenv");
        return (1);
    }

    if (getenv(av[1]) == NULL)
        printf("%s removed\n", av[1]);
    else
        printf("%s still present\n", av[1]);

    return (0);
}
