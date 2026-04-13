# super-simple_shell

Depot d exercices C autour des bases d un shell Unix, avec une version de code en mode strict (fonctions separees quand la consigne demande explicitement une fonction).

## Fichiers programmes (avec main)

- 0-getppid.c
- 0-av.c
- 1-readline.c
- 3-fork_wait_execve_5.c
- 4-super_simple_shell.c
- 5-which_path.c
- 6-printenv_environ.c
- 7-env_vs_environ.c

## Fichiers fonctions (sans main)

- 2-commandline.c
- 8-getenv_custom.c
- 9-path_print_dirs.c
- 10-path_linked_list.c
- 11-setenv_custom.c
- 12-unsetenv_custom.c

## Script

- 1-pid_max.sh

## Build

Compilation des programmes + verification de compilation des fichiers fonctions:

```sh
make
```

Compilation des programmes uniquement:

```sh
make programs
```

Compilation des fichiers fonctions en objets:

```sh
make functions
```

Nettoyage:

```sh
make clean
```

## Revision

La fiche complete pour preparer la man review est ici:
- FICHE_REVISION_MAN_REVIEW.md
