#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _setenv - ajoute ou modifie une variable d'environnement
 * @name: nom de la variable
 * @value: valeur de la variable
 * @overwrite: ecrase la valeur existante si non nul
 *
 * Return: 0 en cas de succes, -1 en cas d'echec
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    size_t i;
    size_t name_len;
    size_t entry_len;
    char *entry;
    char **new_environ;

    /* Valide les entrees selon les regles des variables d'environnement. */
    if (name == NULL || value == NULL || *name == '\0' || strchr(name, '=') != NULL)
        return (-1);

    /* Recherche d'abord si la variable "name" existe deja. */
    name_len = strlen(name);
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            /* Conserve la valeur actuelle si overwrite est desactive. */
            if (!overwrite)
                return (0);

            /* Remplace l'entree existante NAME=value par une nouvelle chaine. */
            entry_len = name_len + 1 + strlen(value) + 1;
            entry = malloc(entry_len);
            if (entry == NULL)
                return (-1);
            snprintf(entry, entry_len, "%s=%s", name, value);
            environ[i] = entry;
            return (0);
        }
    }

    /* Variable absente: construit une nouvelle chaine NAME=value. */
    entry_len = name_len + 1 + strlen(value) + 1;
    entry = malloc(entry_len);
    if (entry == NULL)
        return (-1);
    snprintf(entry, entry_len, "%s=%s", name, value);

    /* Agrandit la table de pointeurs environ (+1 entree + NULL final). */
    new_environ = malloc((i + 2) * sizeof(char *));
    if (new_environ == NULL)
    {
        free(entry);
        return (-1);
    }

    /* Copie les anciennes entrees, puis ajoute la nouvelle. */
    for (name_len = 0; name_len < i; name_len++)
        new_environ[name_len] = environ[name_len];

    environ = new_environ;
    environ[i] = entry;
    environ[i + 1] = NULL;

    return (0);
}
