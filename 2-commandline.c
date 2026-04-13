#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_line - split a line using blanks as separators
 * @line: input string to tokenize
 *
 * Return: allocated array of tokens, or NULL on failure
 */
char **split_line(char *line)
{
	char *token;
	char **words;
	char **tmp;
	size_t size;
	size_t i;

	/* Start with a small dynamic argv-like array. */
	size = 8;
	i = 0;
	words = malloc(size * sizeof(char *));
	if (words == NULL)
		return (NULL);
	/* Split on blanks: space, tab, and newline. */
	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		/* Store pointers into the original modified input buffer. */
		words[i] = token;
		i++;
		/* Keep one extra slot for the final NULL terminator. */
		if (i + 1 >= size)
		{
			size *= 2;
			tmp = realloc(words, size * sizeof(char *));
			if (tmp == NULL)
			{
				/* words is no longer needed if resize failed. */
				free(words);
				return (NULL);
			}
			words = tmp;
		}
		/* Continue tokenization from strtok internal state. */
		token = strtok(NULL, " \t\n");
	}
	/* NULL-terminate to make the result compatible with exec-like APIs. */
	words[i] = NULL;
	return (words);
}
