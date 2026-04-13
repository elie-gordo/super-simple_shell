#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_line - splits a string into words separated by spaces/tabs/newlines
 * @line: input string (will be modified)
 *
 * Return: NULL-terminated array of words, or NULL on failure
 */
char **split_line(char *line)
{
    char *token;
    char **words;
    char **tmp;
    size_t size;
    size_t i;

    size = 8;
    i = 0;
    words = malloc(size * sizeof(char *));
    if (words == NULL)
        return (NULL);

    token = strtok(line, " \t\n");
    while (token != NULL)
    {
        words[i] = token;
        i++;

        if (i + 1 >= size)
        {
            size *= 2;
            tmp = realloc(words, size * sizeof(char *));
            if (tmp == NULL)
            {
                free(words);
                return (NULL);
            }
            words = tmp;
        }

        token = strtok(NULL, " \t\n");
    }

    words[i] = NULL;
    return (words);
}
