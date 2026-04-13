# Fiche de revision complete - decomposition code par code

But de cette fiche:
- expliquer chaque fichier completement en man review
- savoir dire pourquoi chaque bloc est ecrit a cet endroit
- parler simplement, mais avec des mots techniques justes

---

## 0) Methode pour presenter n importe quel fichier

Quand on te montre un fichier, reponds dans cet ordre:
1. Role du fichier (a quoi il sert)
2. Entrees / sorties (ce qu il lit, ce qu il affiche/retourne)
3. Structure (variables, boucle, conditions)
4. Appels systeme / libc utilises et pourquoi
5. Gestion des erreurs
6. Ce qui pourrait casser si on enleve un bloc

---

## 1) 0-getppid.c

### Role
Afficher le PPID (PID du parent).

### Decomposition complete
- `#include <stdio.h>`: pour `printf`.
- `#include <sys/types.h>`: pour le type `pid_t`.
- `#include <unistd.h>`: pour `getppid()`.
- `int main(void)`: programme sans argument.
- `pid_t parent_pid;`: variable typee pour stocker un identifiant de processus.
- `parent_pid = getppid();`: recuperation du parent.
- `printf("%u\n", (unsigned int)parent_pid);`: affichage du resultat.
- `return (0);`: fin normale.

### Pourquoi ce choix
On utilise le type systeme `pid_t` car c est le format natif des PID.

### Ce que tu peux dire a l oral
Ce programme sert juste a verifier qui a cree notre processus.

---

## 2) 1-pid_max.sh

### Role
Afficher la valeur maximale possible d un PID Linux.

### Decomposition complete
- `#!/bin/sh`: script shell portable.
- `cat /proc/sys/kernel/pid_max`: lit le fichier noyau expose dans `/proc`.

### Pourquoi ce choix
`/proc/sys/kernel/pid_max` est la source directe de la valeur configuree par le noyau.

---

## 3) 0-av.c

### Role
Afficher tous les arguments sans utiliser `ac`.

### Decomposition complete
- `#include <stdio.h>`: `printf`.
- `int main(int ac, char **av)`: signature classique des arguments.
- `unsigned int i;`: index de parcours.
- `(void)ac;`: marque `ac` comme volontairement non utilise.
- `i = 0;`: debut du tableau.
- `while (av[i] != NULL)`: fin detectee par sentinelle `NULL`.
- `printf("%s\n", av[i]);`: impression de chaque element.
- `i++;`: passe a l argument suivant.
- `return (0);`.

### Pourquoi ce choix
La consigne impose de ne pas utiliser `ac`, donc on s appuie uniquement sur `av` termine par `NULL`.

---

## 4) 1-readline.c

### Role
Afficher un prompt, lire une ligne, la reafficher, et s arreter sur EOF.

### Decomposition complete
- `_POSIX_C_SOURCE 200809L`: expose `getline` en mode POSIX.
- includes:
  - `stdio.h`: `printf`, `fflush`, `getline`
  - `stdlib.h`: `free`
  - `sys/types.h`/`unistd.h`: types POSIX
- variables:
  - `char *line;` buffer dynamique
  - `size_t len;` taille du buffer
  - `ssize_t nread;` resultat de lecture
- initialisation:
  - `line = NULL; len = 0;` contrat de `getline`
- boucle infinie:
  - `printf("$ ");` prompt
  - `fflush(stdout);` force affichage immediat
  - `nread = getline(&line, &len, stdin);`
  - `if (nread == -1) break;` sortie propre (EOF)
  - `printf("%s", line);` echo
- `free(line);`: liberation memoire
- `return (0);`

### Pourquoi ce choix
`getline` est plus robuste qu un buffer fixe car la ligne peut etre longue.

---

## 5) 2-commandline.c

### Role
Fournir une fonction qui split une ligne en mots (`char **`).

### Decomposition complete
- `_POSIX_C_SOURCE 200809L`: pour fonctions POSIX.
- includes:
  - `stdio.h` (pas indispensable ici, mais present)
  - `stdlib.h`: `malloc`, `realloc`, `free`
  - `string.h`: `strtok`
- prototype/fonction: `char **split_line(char *line)`.

#### Interieur de la fonction
- variables:
  - `char *token;`: mot courant renvoye par `strtok`
  - `char **words;`: tableau resultat
  - `char **tmp;`: buffer temporaire pour `realloc` securise
  - `size_t size = 8;`: capacite initiale
  - `size_t i = 0;`: index ecriture
- `words = malloc(size * sizeof(char *));`: allocation initiale
- `token = strtok(line, " \t\n");`: premier token
- boucle `while (token != NULL)`:
  - `words[i] = token;`
  - `i++`
  - si tableau presque plein: `realloc`
  - en cas echec `realloc`: `free(words); return NULL;`
  - token suivant avec `strtok(NULL, ...)`
- `words[i] = NULL;`: terminaison obligatoire
- `return words;`

### Pourquoi ce choix
- `strtok` colle a la consigne.
- tableau dynamique = pas de limite arbitraire dure.

### Point review important
`split_line` modifie `line` (comportement normal de `strtok`).

---

## 6) 3-fork_wait_execve_5.c

### Role
Executer `ls -l /tmp` dans 5 enfants, un par un.

### Decomposition complete
- includes:
  - `stdio.h`: `perror`
  - `sys/types.h`: `pid_t`
  - `sys/wait.h`: `wait`
  - `unistd.h`: `fork`, `execve`
- variables:
  - `pid_t child_pid;`
  - `int status;`
  - `int i;`
  - `char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};`
- boucle `for (i = 0; i < 5; i++)`:
  - `child_pid = fork();`
  - si `-1`: erreur fork
  - si `0` (enfant): `execve(argv[0], argv, NULL)`
    - si erreur: `perror("execve")`, return 1
  - sinon (parent): `wait(&status)`
    - si erreur: `perror("wait")`, return 1
- fin `return (0)`

### Pourquoi ce choix
Le `wait` dans la boucle garantit un enchainement sequentiel: on attend chaque enfant avant de creer le suivant.

---

## 7) 4-super_simple_shell.c

### Role
Mini shell: lit une commande en chemin absolu et l execute sans argument.

### Decomposition complete
- define POSIX + includes standards process/IO.
- `extern char **environ;`: pour passer l environnement a `execve`.
- variables:
  - `line`, `len`, `nread`: lecture utilisateur
  - `child_pid`, `status`: gestion process
  - `char *argv[2];`: commande + NULL
- init: `line = NULL; len = 0;`
- boucle shell:
  - afficher `#cisfun$ ` + `fflush`
  - lire avec `getline`
  - stop sur EOF (`-1`)
  - supprimer `\n` final
  - ignorer ligne vide
  - `fork`
    - erreur: `perror`, `free(line)`, return 1
    - enfant:
      - `argv[0] = line; argv[1] = NULL;`
      - `execve(argv[0], argv, environ)`
      - en cas echec: `perror`, return 1
    - parent:
      - `wait(&status)`
- sortie: `free(line); return 0;`

### Pourquoi ce choix
- `argv[2]` suffit car pas d arguments demandes.
- `fork + execve + wait` est le schema canonique d un shell.

### Point oral
Le shell parent reste vivant; seul l enfant est remplace par la commande.

---

## 8) 5-which_path.c

### Role
Chercher un fichier dans les repertoires de PATH.

### Decomposition complete

### Fonction `print_found_path(const char *filename)`
- lit `PATH` avec `getenv`
- copie `PATH` avec `strdup` (car `strtok` modifie)
- decoupe par `:`
- pour chaque dossier:
  - calcule taille `needed`
  - alloue `fullpath`
  - construit `dir/filename` avec `snprintf`
  - teste existence via `stat`
  - si trouve: affiche et retourne 0
- si rien trouve: retourne 1

### `main(int ac, char **av)`
- verifie qu au moins un argument est fourni
- boucle sur `av[1..]`
- appelle `print_found_path`
- affiche `not found` si echec

### Pourquoi ce choix
`stat` est une verification simple et conforme au cours pour savoir si un chemin existe.

---

## 9) 6-printenv_environ.c

### Role
Afficher toutes les variables d environnement via `environ`.

### Decomposition complete
- `extern char **environ;`
- boucle indexee jusqu a `NULL`
- affiche chaque ligne brute `NOM=VALEUR`

### Pourquoi ce choix
C est la forme la plus directe de l exercice "printenv with environ".

---

## 10) 7-env_vs_environ.c

### Role
Montrer l adresse de `env` (parametre main) et de `environ` (globale).

### Decomposition complete
- `extern char **environ;`
- signature `main(int ac, char **av, char **env)`
- `(void)ac; (void)av;`
- `printf` des deux pointeurs avec `%p`

### Pourquoi ce choix
Comparer les adresses est la facon la plus claire de verifier s ils referencent la meme zone.

---

## 11) 8-getenv_custom.c

### Role
Implanter `_getenv` sans appeler `getenv`.

### Decomposition complete
- includes: `string.h` pour `strlen`, `strncmp`
- `extern char **environ;`
- validation entree:
  - `name == NULL` ou `*name == '\0'` -> `NULL`
- `name_len = strlen(name)`
- `env = environ`
- boucle tant que `*env != NULL`
  - compare prefixe avec `strncmp`
  - verifie `=` juste apres le nom
  - retourne pointeur sur valeur `&((*env)[name_len + 1])`
- si non trouve: `NULL`

### Pourquoi ce choix
La verif du caractere `=` evite les faux positifs de prefixe.

---

## 12) 9-path_print_dirs.c

### Role
Fonction `print_path_dirs` qui affiche chaque dossier de PATH.

### Decomposition complete
- `getenv("PATH")`
- garde-fou si `PATH` absent
- copie avec `strdup`
- split avec `strtok(":")`
- `printf` pour chaque dossier
- `free(path_copy)`

### Pourquoi ce choix
C est la version la plus simple et lisible de l exigence "one directory per line".

---

## 13) 10-path_linked_list.c

### Role
Construire une liste chainee de dossiers PATH.

### Decomposition complete

### `struct path_node`
- `char *dir;`
- `struct path_node *next;`

### `add_node_end`
- alloue un noeud
- duplique `dir`
- ajoute en tete si liste vide
- sinon parcourt jusqu a la fin et chainage

### `free_list`
- parcourt la liste
- libere `dir` puis noeud

### `build_path_list`
- lit et copie PATH
- split par `:`
- ajoute chaque dossier via `add_node_end`
- en cas erreur: nettoyage complet
- retourne tete de liste

### Pourquoi ce choix
Separation en 3 fonctions = code maintenable et gestion memoire propre.

---

## 14) 11-setenv_custom.c

### Role
Implanter `_setenv(name, value, overwrite)` sans `setenv`.

### Decomposition complete
- validation:
  - `name`/`value` non NULL
  - `name` non vide
  - `name` ne contient pas `=`
- parcours `environ` pour trouver `name=`
- si variable existe:
  - si `overwrite == 0`, ne rien changer
  - sinon construire nouvelle chaine `name=value` et remplacer
- si variable absente:
  - construire `name=value`
  - allouer un nouveau tableau de pointeurs `environ`
  - copier anciennes entrees
  - ajouter nouvelle entree + `NULL`

### Pourquoi ce choix
Respect exact de la semantique `setenv`: ajouter ou remplacer selon `overwrite`.

---

## 15) 12-unsetenv_custom.c

### Role
Implanter `_unsetenv(name)` sans `unsetenv`.

### Decomposition complete
- validation de `name`
- calcul `name_len`
- parcours `environ`
- si match `name=`:
  - decalage a gauche de toutes les entrees suivantes
  - `i--` pour recontroler la case courante apres decalage
- retour 0

### Pourquoi ce choix
Le decalage conserve une liste continue jusqu au `NULL` final.

---

## 16) Makefile (outil de build)

### Role
Compiler rapidement les programmes et verifier les fichiers fonctions.

### Decomposition complete
- `CC` et `CFLAGS`: compilation stricte (`-Wall -Wextra -Werror -pedantic`).
- `PROGRAMS`: cibles executables.
- `FUNC_OBJECTS`: cibles `.o` pour fichiers sans `main`.
- `all`: lance `programs` et `functions`.
- une regle par cible.
- `clean`: supprime binaires et objets.
- `re`: rebuild complet.

### Pourquoi ce choix
Permet de verifier en une commande que tout compile, meme les fichiers fonctions.

---

## 17) README.md (doc d usage)

### Role
Donner une vue claire du depot.

### Decomposition complete
- liste separee des fichiers programmes et fonctions
- section build (`make`, `make programs`, `make functions`, `make clean`)
- section revision qui pointe vers les fiches

### Pourquoi ce choix
Facilite la prise en main pour toi et pour le correcteur.

---

## 18) Questions man review frequentes + reponses

Pourquoi `fork` puis `execve` ?
- Parce que `execve` remplace le processus courant. Sans `fork`, le shell serait remplace.

Pourquoi `wait` ?
- Pour synchroniser le parent et eviter des zombies.

Pourquoi `strdup` avant `strtok` sur PATH ?
- Parce que `strtok` modifie la chaine.

Pourquoi tester les retours d erreur ?
- `fork`, `execve`, `malloc`, `wait`, `getline` peuvent echouer.

Pourquoi `argv` se termine par `NULL` ?
- C est le contrat C/POSIX de nombreuses API.

---

## 19) Pitch final (1 minute)

J ai construit le shell par couches. D abord les bases de processus (PID/PPID), ensuite la lecture et le parsing de commande, puis le noyau d execution `fork + execve + wait`. Apres cela, j ai implemente la recherche dans PATH et la gestion de l environnement avec des fonctions personnalisees (`_getenv`, `_setenv`, `_unsetenv`). Chaque fichier a une responsabilite precise, avec gestion d erreurs et memoire adaptee au niveau demande par la consigne.
