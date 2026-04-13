#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - prints each PATH directory on its own line
 *
 * Return: 0 on success
 */
int main(void)
{
    char *path_env;
    char *path_copy;
    char *dir;

    path_env = getenv("PATH");
    if (path_env == NULL)
        return (1);

    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return (1);

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        printf("%s\n", dir);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (0);
}
