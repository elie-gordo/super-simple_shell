# Super Simple Shell - Exercices Guides

Ce depot contient des exercices C de base pour comprendre comment un shell fonctionne.

Le but est simple :
- comprendre les processus (PID, PPID)
- comprendre les arguments d'un programme
- lire une ligne utilisateur
- creer des processus avec `fork`
- executer des programmes avec `execve`
- attendre un enfant avec `wait`
- chercher un binaire dans `PATH`
- manipuler l'environnement (`environ`, `_getenv`, `_setenv`, `_unsetenv`)

## 1) Processus: PID et PPID

Un **processus** = un programme en cours d'execution.

Chaque processus a:
- un **PID** (Process ID): son numero unique
- un **PPID** (Parent Process ID): le PID de son parent

### Exercice: getppid
Fichier: `pid_ppid_getppid.c`
- appelle `getppid()`
- affiche le PID du processus parent

Pourquoi la valeur reste souvent la meme dans le meme terminal ?
- parce que le parent est le shell (bash, sh, etc.)
- tant que tu restes dans le meme shell, son PID ne change pas

`echo $$` affiche souvent ce meme PID, car `$$` est le PID du shell courant.

### Exercice: pid_max
Fichier: `pid_max.sh`
- lit `/proc/sys/kernel/pid_max`
- affiche la valeur maximale possible d'un PID sur Linux

## 2) Arguments de ligne de commande

Dans `int main(int ac, char **av)`:
- `ac` = nombre d'arguments
- `av` = tableau de chaines termine par `NULL`

### Exercice: afficher `av` sans `ac`
Fichier: `args_av.c`
- parcourt `av` jusqu'a `NULL`
- affiche chaque argument

### Exercice: read line
Fichier: `read_line.c`
- affiche `$ `
- lit avec `getline`
- re-affiche la ligne lue
- s'arrete quand `getline` retourne `-1` (EOF, ex: Ctrl+D)

### Exercice: command line to av
Fichier: `split_line.c`
- fonction `split_line` qui coupe une ligne en mots via `strtok`
- renvoie un tableau de pointeurs vers les mots

## 3) Exec, Fork, Wait

### Rappel rapide
- `fork()` duplique le processus: parent + enfant
- `execve()` remplace le code du processus courant par un autre programme
- `wait()` fait patienter le parent jusqu'a la fin de l'enfant

### Exercice: fork + wait + execve
Fichier: `fork_wait_execve_5.c`
- lance `ls -l /tmp`
- dans 5 enfants differents
- attend chaque enfant avant de creer le suivant

### Exercice: super simple shell
Fichier: `super_simple_shell.c`
- boucle de prompt `#cisfun$ `
- lit une commande (chemin complet, sans argument)
- `fork` + `execve`
- parent attend avec `wait`

## 4) Informations de fichier et PATH

### Exercice: find a file in PATH
Fichier: `which_path.c`
- recupere `PATH`
- coupe `PATH` par `:`
- construit `dir/filename`
- utilise `stat` pour verifier l'existence
- affiche le premier chemin trouve

## 5) Environnement

L'environnement est un tableau de chaines `VAR=value`.
Un processus enfant herite d'une copie de l'environnement du parent.

### Exercice: printenv avec environ
Fichier: `printenv_environ.c`
- utilise `extern char **environ`
- affiche toutes les variables

### Exercice: env vs environ
Fichier: `env_vs_environ.c`
- affiche l'adresse de `env` (3e argument de `main`)
- affiche l'adresse de `environ` (globale)
- en pratique, ces adresses sont generalement identiques

### Exercice: _getenv
Fichier: `getenv_custom.c`
- implemente `char *_getenv(const char *name)` sans `getenv`
- cherche `name=` dans `environ`
- renvoie l'adresse de la valeur

### Exercice: PATH -> directories
Fichier: `path_print_dirs.c`
- lit `PATH`
- affiche chaque repertoire sur une ligne

### Exercice: PATH -> linked list
Fichier: `path_linked_list.c`
- cree une liste chainee de tous les repertoires de `PATH`
- affiche puis libere la liste

### Exercice: _setenv
Fichier: `setenv_custom.c`
- prototype: `int _setenv(const char *name, const char *value, int overwrite)`
- remplace la variable si elle existe et `overwrite != 0`
- sinon ajoute une nouvelle variable

### Exercice: _unsetenv
Fichier: `unsetenv_custom.c`
- prototype: `int _unsetenv(const char *name)`
- supprime toutes les occurrences de `name` dans `environ`

## Compilation (Linux)

Exemples de compilation stricts:

```sh
gcc -Wall -Wextra -Werror -pedantic pid_ppid_getppid.c -o ppid
gcc -Wall -Wextra -Werror -pedantic args_av.c -o av
gcc -Wall -Wextra -Werror -pedantic read_line.c -o prompt
gcc -Wall -Wextra -Werror -pedantic split_line.c -o split
gcc -Wall -Wextra -Werror -pedantic fork_wait_execve_5.c -o run5
gcc -Wall -Wextra -Werror -pedantic super_simple_shell.c -o shell
gcc -Wall -Wextra -Werror -pedantic which_path.c -o _which
gcc -Wall -Wextra -Werror -pedantic printenv_environ.c -o printenv_env
gcc -Wall -Wextra -Werror -pedantic env_vs_environ.c -o env_addr
gcc -Wall -Wextra -Werror -pedantic getenv_custom.c -o my_getenv
gcc -Wall -Wextra -Werror -pedantic path_print_dirs.c -o path_dirs
gcc -Wall -Wextra -Werror -pedantic path_linked_list.c -o path_list
gcc -Wall -Wextra -Werror -pedantic setenv_custom.c -o my_setenv
gcc -Wall -Wextra -Werror -pedantic unsetenv_custom.c -o my_unsetenv
```

Script:

```sh
chmod +x pid_max.sh
./pid_max.sh
```

## Explication simple (niveau enfant)

Imagine l'ordinateur comme une ecole:
- un **processus** = un eleve qui fait un exercice
- le **PID** = son numero de badge
- le **PPID** = le numero du prof qui lui a donne le travail
- `fork` = le prof fait une copie de l'eleve (un jumeau)
- `execve` = l'eleve range son ancien exercice et commence un nouveau
- `wait` = le prof attend que l'eleve termine
- `PATH` = la liste des salles ou on cherche les outils
- `environ` = le sac avec toutes les infos utiles (HOME, PATH, etc.)

## Limites voulues (respect des consignes)

Cette version reste volontairement simple:
- pas d'arguments dans `super_simple_shell.c`
- pas de gestion avancee des erreurs shell
- pas de parsing complexe
- uniquement les notions deja introduites dans les exercices
