#include <stdio.h>

/**
 * main - prints all arguments without using ac
 * @ac: argument count (unused)
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    unsigned int i;

    /* ac is intentionally unused: the exercise requires walking only with av. */
    (void)ac;
    /* Start at argv[0] (program name), then continue until the NULL sentinel. */
    i = 0;
    while (av[i] != NULL)
    {
        /* Print one argument per line to show exact argv layout. */
        printf("%s\n", av[i]);
        i++;
    }

    return (0);
}
