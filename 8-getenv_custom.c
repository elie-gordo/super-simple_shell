#include <string.h>

extern char **environ;

/**
 * _getenv - recupere la valeur d'une variable d'environnement
 * @name: nom de la variable
 *
 * Return: pointeur vers la valeur, ou NULL si non trouvee
 */
char *_getenv(const char *name)
{
    size_t name_len;
    char **env;

    /* Rejette immediatement les entrees invalides. */
    if (name == NULL || *name == '\0')
        return (NULL);

    /* Calcule la longueur une seule fois pour la reutiliser ensuite. */
    name_len = strlen(name);
    env = environ;

    while (*env != NULL)
    {
        /* Match exact: NOM suivi de '=' pour eviter les collisions de prefixe. */
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
            /* Retourne l'adresse juste apres '=' pour obtenir uniquement la valeur. */
            return (&((*env)[name_len + 1]));
        env++;
    }

    return (NULL);
}
