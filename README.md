# super-simple_shell

Exercices C autour des bases d un shell Unix.
Le depot contient des petits programmes, des fonctions isolees, et un script shell.
Le code est commente et respecte une compilation stricte.

## Objectif pedagogique

Construire les briques d un shell dans l ordre logique:
- processus (PID, PPID)
- lecture utilisateur
- parsing de ligne
- fork + execve + wait
- recherche dans PATH
- environnement (environ, _getenv, _setenv, _unsetenv)

## Structure du projet

### Programmes (avec main)
- 0-getppid.c
- 0-av.c
- 1-readline.c
- 3-fork_wait_execve_5.c
- 4-super_simple_shell.c
- 5-which_path.c
- 6-printenv_environ.c
- 7-env_vs_environ.c

### Fonctions (sans main)
- 2-commandline.c
- 8-getenv_custom.c
- 9-path_print_dirs.c
- 10-path_linked_list.c
- 11-setenv_custom.c
- 12-unsetenv_custom.c

### Headers utilitaires
- 10-path_linked_list.h
- environ_custom.h

### Script
- 1-pid_max.sh

### Documents
- CODE_explications.md
- FICHE_ManReview.md

## Build

Compiler tout (programmes + verification des fonctions en objets):

```sh
make
```

Compiler seulement les programmes:

```sh
make programs
```

Compiler seulement les fonctions (objets):

```sh
make functions
```

Nettoyer:

```sh
make clean
```

Rebuild complet:

```sh
make re
```

## Qualite

Verification style/doc Betty:

```sh
betty-style *.c
betty-doc *.c
```

Compilation stricte utilisee par le projet:
- -Wall
- -Wextra
- -Werror
- -pedantic

## Execution rapide

Exemples:

```sh
./ppid
./av one two three
printf 'hello\n' | ./prompt
./run5
./whichpath ls cat nosuchcmd
```

Test shell minimal:

```sh
./shell
#cisfun$ /bin/ls
#cisfun$ /bin/echo
#cisfun$ Ctrl+D
```

## Notes

- Le shell de 4-super_simple_shell.c attend un chemin complet et ne gere pas les arguments.
- Les fonctions de 11-setenv_custom.c et 12-unsetenv_custom.c manipulent environ sans setenv/unsetenv.
- 10-path_linked_list.c construit une liste chainee des repertoires PATH.
