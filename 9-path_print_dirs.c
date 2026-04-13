#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_path_dirs - prints each PATH directory on its own line
 *
 * Return: nothing
 */
void print_path_dirs(void)
{
    char *path_env;
    char *path_copy;
    char *dir;

    path_env = getenv("PATH");
    if (path_env == NULL)
        return;

    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        printf("%s\n", dir);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
}
