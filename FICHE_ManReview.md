# FICHE Man Review

## Pourquoi on a fait ca ?

On a fait ces exercices pour comprendre comment un shell fonctionne vraiment, pas seulement pour ecrire du code qui marche.

Un shell doit savoir:
- lire une commande
- creer un processus enfant
- executer la commande dans cet enfant
- attendre la fin de la commande
- gerer PATH et les variables d environnement

Donc chaque fichier du projet correspond a une brique indispensable.

En version tres simple:
- le shell est le "chef"
- il lit ce que tu demandes
- il envoie un "assistant" (processus enfant) faire la tache
- il attend le resultat

---

## Comment on en est arrive la ?

On a suivi une progression logique, du plus simple au plus complet:

1. Comprendre les processus
- [0-getppid.c](0-getppid.c): voir le parent d un processus
- [1-pid_max.sh](1-pid_max.sh): connaitre la limite max des PID

2. Comprendre les entrees d un programme
- [0-av.c](0-av.c): lire les arguments avec `av`
- [1-readline.c](1-readline.c): lire une ligne utilisateur avec `getline`

3. Transformer une ligne en commande exploitable
- [2-commandline.c](2-commandline.c): decouper en mots avec `strtok`

4. Executer des commandes
- [3-fork_wait_execve_5.c](3-fork_wait_execve_5.c): boucle fork/execve/wait en 5 enfants
- [4-super_simple_shell.c](4-super_simple_shell.c): mini shell complet (full path, sans args)

5. Trouver les commandes dans PATH
- [5-which_path.c](5-which_path.c): recherche d un nom dans les dossiers PATH

6. Lire et manipuler l environnement
- [6-printenv_environ.c](6-printenv_environ.c): afficher `environ`
- [7-env_vs_environ.c](7-env_vs_environ.c): comparer `env` et `environ`
- [8-getenv_custom.c](8-getenv_custom.c): reimplementer `_getenv`
- [9-path_print_dirs.c](9-path_print_dirs.c): afficher les dossiers de PATH
- [10-path_linked_list.c](10-path_linked_list.c): PATH en liste chainee
- [11-setenv_custom.c](11-setenv_custom.c): reimplementer `_setenv`
- [12-unsetenv_custom.c](12-unsetenv_custom.c): reimplementer `_unsetenv`

---

## Qu est-ce qu on a utilise, et pourquoi ?

### Appels systeme / fonctions principales

- `getppid`
Pourquoi: identifier le parent du processus.

- `getline`
Pourquoi: lire une ligne complete sans taille fixe dangereuse.

- `strtok`
Pourquoi: decouper la commande en tokens (mots).

- `fork`
Pourquoi: creer un enfant pour executer une commande sans tuer le shell parent.

- `execve`
Pourquoi: remplacer le code de l enfant par le programme cible.

- `wait`
Pourquoi: synchroniser le parent avec la fin de l enfant.

- `stat`
Pourquoi: verifier qu un chemin candidat existe.

- `environ`
Pourquoi: lire/mettre a jour l environnement du processus.

- `malloc`, `realloc`, `free`
Pourquoi: gerer la memoire dynamique pour tableaux/chaines.

- `strlen`, `strncmp`, `strchr`, `snprintf`
Pourquoi: comparer et construire des chaines proprement.

---

## Comment l expliquer de facon comprehensible pour tous

Version enfant:
- Tu donnes un ordre au shell.
- Le shell lit ton ordre.
- Il cree un petit assistant pour faire le travail.
- L assistant execute la commande.
- Le shell attend qu il revienne.
- Pour trouver les outils, il regarde dans une liste d adresses (PATH).
- Les reglages de base (HOME, PATH...) sont les variables d environnement.

Version technique courte:
Le flux standard est: prompt -> getline -> parsing -> fork -> execve -> wait -> boucle.

---

## Ce que tu dois absolument savoir dire en review

- Pourquoi `fork` avant `execve`:
`execve` remplace le processus courant. Sans `fork`, le shell disparait.

- Pourquoi `wait`:
pour eviter les zombies et garder un comportement propre.

- Pourquoi copier PATH avant `strtok`:
`strtok` modifie la chaine.

- Pourquoi tester les retours d erreur:
`fork`, `execve`, `wait`, `malloc`, `getline` peuvent echouer.

- Pourquoi `argv` finit par `NULL`:
c est le contrat des API C/POSIX, notamment `execve`.

---

## Resume final a reciter (45 secondes)

On a construit le shell par etapes pedagogiques. D abord la base processus, ensuite la lecture et le decoupage des commandes, puis le cycle d execution `fork + execve + wait`. Ensuite on a ajoute la recherche dans PATH et la gestion de l environnement avec des fonctions custom. Le but etait de comprendre la logique systeme de A a Z avec un code simple, clair et strictement aligne avec la consigne.

---

## Pour la decomposition ligne par ligne

Tu peux completer cette fiche avec la decomposition tres detaillee dans:
- [CODE_explications.md](CODE_explications.md)
