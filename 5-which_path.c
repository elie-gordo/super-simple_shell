#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * print_found_path - prints the first matching executable in PATH for filename
 * @filename: file to look for
 *
 * Return: 0 if found, 1 otherwise
 */
int print_found_path(const char *filename)
{
    char *path_env;
    char *path_copy;
    char *dir;
    char *fullpath;
    size_t needed;
    struct stat st;

    /* PATH is a ':'-separated list of directories to scan. */
    path_env = getenv("PATH");
    if (path_env == NULL)
        return (1);

    /* Duplicate PATH because strtok modifies the string in place. */
    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return (1);

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        /* Space for "dir" + '/' + "filename" + '\0'. */
        needed = strlen(dir) + 1 + strlen(filename) + 1;
        fullpath = malloc(needed);
        if (fullpath == NULL)
        {
            free(path_copy);
            return (1);
        }

        /* Build candidate path in a bounded, safe way. */
        snprintf(fullpath, needed, "%s/%s", dir, filename);

        /* stat == 0 means file exists at this path. */
        if (stat(fullpath, &st) == 0)
        {
            printf("%s\n", fullpath);
            free(fullpath);
            free(path_copy);
            return (0);
        }

        free(fullpath);
        /* Check next directory in PATH. */
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (1);
}

/**
 * main - looks for each file argument in PATH
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    int i;

    /* Need at least one filename to search. */
    if (ac < 2)
    {
        printf("Usage: %s filename ...\n", av[0]);
        return (1);
    }

    /* Process each argument independently. */
    for (i = 1; i < ac; i++)
    {
        if (print_found_path(av[i]) != 0)
            printf("%s: not found\n", av[i]);
    }

    return (0);
}
