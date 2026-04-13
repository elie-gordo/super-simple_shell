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

    /* Read PATH from current process environment. */
    path_env = getenv("PATH");
    if (path_env == NULL)
        return;

    /* Duplicate PATH before strtok, which edits the input string. */
    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return;

    /* Print one directory per line as required by exercise. */
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        printf("%s\n", dir);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
}
