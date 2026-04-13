#include <stdio.h>

extern char **environ;

/**
 * main - prints addresses of env and environ
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 * @env: environment from main parameter
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    printf("Address of env:     %p\n", (void *)env);
    printf("Address of environ: %p\n", (void *)environ);

    return (0);
}
