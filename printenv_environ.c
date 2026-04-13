#include <stdio.h>

extern char **environ;

/**
 * main - prints environment using the global variable environ
 *
 * Return: 0 on success
 */
int main(void)
{
    unsigned int i;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }

    return (0);
}
