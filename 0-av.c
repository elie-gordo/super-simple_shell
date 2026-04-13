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

    (void)ac;
    i = 0;
    while (av[i] != NULL)
    {
        printf("%s\n", av[i]);
        i++;
    }

    return (0);
}
