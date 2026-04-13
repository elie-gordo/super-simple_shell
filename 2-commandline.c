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

    /* Start with a small dynamic array and grow when needed. */
    size = 8;
    i = 0;
    words = malloc(size * sizeof(char *));
    if (words == NULL)
        return (NULL);

    /* First token using whitespace delimiters (space/tab/newline). */
    token = strtok(line, " \t\n");
    while (token != NULL)
    {
        /* Store pointer to token inside the modified input buffer. */
        words[i] = token;
        i++;

        /* Keep one extra slot for the final NULL terminator. */
        if (i + 1 >= size)
        {
            size *= 2;
            tmp = realloc(words, size * sizeof(char *));
            if (tmp == NULL)
            {
                /* On realloc failure, free current array and report failure. */
                free(words);
                return (NULL);
            }
            words = tmp;
        }

        /* Continue tokenization from the previous strtok state. */
        token = strtok(NULL, " \t\n");
    }

    /* NULL-terminate the returned argv-like array. */
    words[i] = NULL;
    return (words);
}
