# Doc Man Review - Explication complete du code

Objectif de ce document:
- t aider a expliquer chaque element du code pendant la man review
- dire pourquoi on a ecrit chaque bloc a cet endroit
- rester simple, concret et technique a la fois

---

## 1) Vision globale

On construit un shell par briques.
Chaque fichier enseigne une brique precise.
Ensuite on assemble ces briques dans le mini shell.

Ordre logique:
1. Processus (PID/PPID)
2. Arguments
3. Lecture utilisateur
4. Decoupage de commande
5. Execution avec fork/execve/wait
6. Recherche dans PATH
7. Environnement (lecture + modification)

Phrase orale courte:
Je n ai pas essaye de faire un shell complet directement. J ai construit chaque mecanisme essentiel separement pour comprendre exactement le role de chaque appel systeme.

---

## 2) Fichiers programmes (avec main)

## 2.1 0-getppid.c

Pourquoi ce fichier existe:
- montrer qu un processus a un parent
- visualiser le PPID du shell qui lance le programme

Elements du code et justification:
- `#include <unistd.h>`: donne acces a `getppid()`
- `pid_t parent_pid;`: type systeme adapte aux IDs de processus
- `parent_pid = getppid();`: recupere le parent
- `printf("%u\n", (unsigned int)parent_pid);`: affichage lisible

Comment l expliquer simplement:
Le programme demande: "Qui m a cree ?" et affiche son numero.

---

## 2.2 0-av.c

Pourquoi ce fichier existe:
- prouver qu on peut parcourir les arguments sans `ac`

Elements du code et justification:
- `(void)ac;`: indique qu on respecte la consigne sans utiliser `ac`
- `while (av[i] != NULL)`: `av` est termine par sentinelle `NULL`
- `printf("%s\n", av[i]);`: affiche chaque argument

Point oral important:
Le tableau `av` se suffit a lui-meme car sa fin est marquee par `NULL`.

---

## 2.3 1-readline.c

Pourquoi ce fichier existe:
- simuler la boucle d entree d un shell
- apprendre a arreter proprement sur EOF

Elements du code et justification:
- `_POSIX_C_SOURCE 200809L`: active la declaration de `getline` en mode POSIX
- `char *line = NULL; size_t len = 0;`: contrat attendu par `getline`
- `printf("$ "); fflush(stdout);`: prompt visible avant la saisie
- `nread = getline(...)`: lit une ligne complete
- `if (nread == -1) break;`: stop sur EOF/Ctrl+D
- `free(line);`: evite fuite memoire

Point oral important:
`getline` alloue/agrandit le buffer pour nous, mais nous devons liberer a la fin.

---

## 2.4 3-fork_wait_execve_5.c

Pourquoi ce fichier existe:
- montrer le cycle classique parent/enfant
- executer une commande dans 5 enfants differents
- attendre chaque enfant avant d en creer un nouveau

Elements du code et justification:
- `char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};`: format exact attendu par `execve`
- `for (i = 0; i < 5; i++)`: repetition demandee
- `child_pid = fork();`: creation d enfant
- `if (child_pid == 0) execve(...)`: seul l enfant se remplace
- `else wait(&status)`: le parent synchronise

Point oral important:
On n enchaine pas les 5 enfants en parallele, on attend chaque fin, comme demande.

---

## 2.5 4-super_simple_shell.c

Pourquoi ce fichier existe:
- assembler la premiere version d un shell minimal
- executer une commande en chemin absolu sans arguments

Elements du code et justification:
- `extern char **environ;`: transmettre l environnement a `execve`
- boucle `while (1)`: shell interactif continu
- `getline`: lire la commande utilisateur
- suppression du `\n`: `line[nread - 1] = '\0'`
- `if (line[0] == '\0') continue;`: ignore ligne vide
- `fork` puis `execve` dans l enfant
- `wait` dans le parent

Pourquoi `argv[2]`:
- `argv[0]` = commande
- `argv[1]` = `NULL` (pas d argument)

Point oral important:
Le shell parent reste vivant, l enfant fait le travail.

---

## 2.6 5-which_path.c

Pourquoi ce fichier existe:
- reproduire la logique de recherche d un binaire dans `PATH`

Elements du code et justification:
- `getenv("PATH")`: lit la variable PATH
- `strdup(path_env)`: copie car `strtok` modifie la chaine
- `strtok(path_copy, ":")`: decoupe chaque repertoire
- `snprintf(fullpath, ...)`: construit `dir/filename` sans debordement
- `stat(fullpath, &st) == 0`: teste existence du fichier

Pourquoi fonction + main:
- `print_found_path` fait le travail principal reutilisable
- `main` gere les arguments utilisateur

Point oral important:
On cherche dans chaque dossier du PATH jusqu a trouver le premier match.

---

## 2.7 6-printenv_environ.c

Pourquoi ce fichier existe:
- afficher l environnement via la variable globale `environ`

Elements du code et justification:
- `extern char **environ;`: declaration de la variable globale
- `while (environ[i] != NULL)`: parcours classique tableau termine par `NULL`

Point oral important:
Chaque entree est une chaine `NOM=VALEUR`.

---

## 2.8 7-env_vs_environ.c

Pourquoi ce fichier existe:
- comparer `env` (parametre de `main`) et `environ` (globale)

Elements du code et justification:
- `(void)ac; (void)av;`: evite warning variables non utilisees
- affichage des adresses `%p`: comparaison memoire directe

Point oral important:
En pratique les deux pointent souvent vers la meme liste d environnement.

---

## 3) Fichiers fonctions (sans main)

## 3.1 2-commandline.c - split_line

Pourquoi cette fonction existe:
- transformer une commande texte en tableau de mots

Elements du code et justification:
- `malloc(size * sizeof(char *))`: tableau dynamique de pointeurs
- `strtok(line, " \t\n")`: coupe par espaces/tab/newline
- `realloc` quand capacite insuffisante: gestion flexible
- `words[i] = NULL`: terminaison standard pour tableau de chaines

Pourquoi on retourne des pointeurs vers `line`:
- plus simple et suffisant pour l exercice
- `strtok` remplace les separateurs par `\0`

Point oral important:
`line` est modifiee volontairement pour separer les tokens.

---

## 3.2 8-getenv_custom.c - _getenv

Pourquoi cette fonction existe:
- reimplementer `getenv` sans utiliser `getenv`

Elements du code et justification:
- validation `name` (non NULL, non vide)
- `strlen(name)` une fois, pour efficacite
- boucle sur `environ`
- test double:
  - `strncmp(*env, name, name_len) == 0`
  - `(*env)[name_len] == '='`

Pourquoi le test `=` est indispensable:
- evite confusion entre `PATH` et `PATHNAME`

Valeur retour:
- adresse du debut de la valeur (juste apres `=`)

---

## 3.3 9-path_print_dirs.c - print_path_dirs

Pourquoi cette fonction existe:
- exercice demande: afficher chaque dossier de PATH

Elements du code et justification:
- lecture PATH avec `getenv`
- copie avec `strdup`
- decoupage avec `strtok(":")`
- `printf` dossier par dossier
- `free(path_copy)` a la fin

Point oral important:
Sans copie, `strtok` pourrait corrompre la chaine source de PATH.

---

## 3.4 10-path_linked_list.c - build_path_list

Pourquoi cette fonction existe:
- convertir PATH en liste chainee pour manipulations futures

Elements du code et justification:
- `struct path_node`: noeud minimal `dir + next`
- `add_node_end`: ajoute proprement en fin
- `free_list`: liberation centralisee
- `build_path_list`: lit PATH, decoupe, remplit la liste

Point oral important:
On separe creation, ajout et liberation pour un code plus clair et testable.

---

## 3.5 11-setenv_custom.c - _setenv

Pourquoi cette fonction existe:
- modifier/ajouter une variable sans `setenv`

Elements du code et justification:
- validation entree: `name`, `value`, pas de `=` dans `name`
- recherche de variable existante
- si trouvee:
  - si `overwrite == 0`, on garde la valeur
  - sinon on remplace l entree par nouvelle chaine `name=value`
- si non trouvee:
  - allocation d un nouveau tableau `environ`
  - copie des pointeurs existants
  - ajout de la nouvelle entree puis `NULL`

Point oral important:
Le parametre `overwrite` controle si on ecrase une valeur existante.

---

## 3.6 12-unsetenv_custom.c - _unsetenv

Pourquoi cette fonction existe:
- supprimer une variable sans `unsetenv`

Elements du code et justification:
- validation `name`
- recherche des entrees correspondant a `name=`
- decalage a gauche du tableau pour supprimer l element
- `i--` pour re-verifier la position courante apres decalage

Point oral important:
Le decalage maintient un tableau continu jusqu au `NULL` final.

---

## 4) Reponses pretes a des questions pieges

Pourquoi `fork` avant `execve`:
- `execve` remplace le processus courant; sans `fork`, le shell disparait.

Pourquoi `wait`:
- pour synchroniser le parent et eviter des processus zombies.

Pourquoi `strdup` avant `strtok`:
- `strtok` modifie la chaine; on protege la source.

Pourquoi tester les retours de fonctions:
- system calls et allocations peuvent echouer; il faut gerer les erreurs proprement.

Pourquoi `argv` termine par `NULL`:
- c est le contrat de nombreuses fonctions C/Unix (`execve` notamment).

---

## 5) Pitch oral final (30 secondes)

J ai suivi une progression systeme: identification des processus, lecture et decoupage des commandes, creation d enfants, execution via execve, synchronisation avec wait, puis gestion de PATH et de l environnement. Chaque fichier isole un mecanisme precis pour que je puisse expliquer a la fois le quoi, le pourquoi et le comportement memoire/processus associe.
