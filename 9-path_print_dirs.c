#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_path_dirs - affiche chaque dossier de PATH sur sa propre ligne
 *
 * Return: rien
 */
void print_path_dirs(void)
{
	char *path_env;
	char *path_copy;
	char *dir;

	/* Read PATH from process environment. */
	path_env = getenv("PATH");
	if (path_env == NULL)
		return;
	/* Duplicate before strtok because it mutates the string. */
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return;
	/* Print each PATH directory on its own line. */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}
	/* Release duplicated PATH buffer. */
	free(path_copy);
}
