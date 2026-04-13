# Fiche de revision complete - man review (simple shell)

## 1. But du projet

Le but est de comprendre, pas seulement de coder.
On apprend comment un shell fonctionne en reconstruisant ses briques de base une par une.

Un shell, c est un programme qui:
- affiche un prompt
- lit une commande
- cree un processus enfant
- lance la commande dans cet enfant
- attend la fin de la commande

## 2. Pourquoi on a fait ces exercices

On a suivi un ordre pedagogique volontaire:

1. Comprendre les processus
- Si on ne comprend pas PID et PPID, on ne comprend pas qui execute quoi.

2. Comprendre les entrees d un programme
- Un shell lit du texte et le transforme en arguments.

3. Comprendre la lecture utilisateur
- Un shell est interactif: il attend des commandes en boucle.

4. Comprendre l execution reelle
- fork + execve + wait = le coeur d un shell Unix.

5. Comprendre PATH
- Quand on tape une commande, le shell la cherche dans des repertoires.

6. Comprendre l environnement
- Variables comme PATH, HOME, USER influencent le comportement des programmes.

## 3. Comment on en est arrive la (chemin logique)

On est passe du plus simple au plus concret:

- Etape A: observer les identites des processus
  - 0-getppid.c
  - 1-pid_max.sh

- Etape B: observer les arguments
  - 0-av.c

- Etape C: lire une ligne utilisateur
  - 1-readline.c

- Etape D: decouper une ligne en mots
  - 2-commandline.c

- Etape E: creer et controler des processus
  - 3-fork_wait_execve_5.c

- Etape F: assembler une premiere version de shell
  - 4-super_simple_shell.c

- Etape G: chercher une commande dans PATH
  - 5-which_path.c

- Etape H: manipuler l environnement
  - 6-printenv_environ.c
  - 7-env_vs_environ.c
  - 8-getenv_custom.c
  - 9-path_print_dirs.c
  - 10-path_linked_list.c
  - 11-setenv_custom.c
  - 12-unsetenv_custom.c

Conclusion: chaque etape est une piece du puzzle shell.

## 4. Les notions techniques essentielles (simples + precises)

### Processus
- Definition: programme en cours d execution.
- PID: identifiant unique du processus.
- PPID: identifiant du parent.

Image mentale enfant:
- Un processus = un eleve.
- PID = numero de badge.
- PPID = numero du prof qui l a cree.

### fork
- Cree un enfant presque identique au parent.
- Retour:
  - -1 en cas d erreur
  - 0 dans l enfant
  - PID de l enfant dans le parent

Pourquoi important:
- Le shell ne doit pas se remplacer lui meme quand il lance une commande.
- Il cree un enfant qui execute la commande.

### execve
- Remplace le programme courant par un autre.
- Si execve reussit, il ne revient pas.

Pourquoi important:
- C est comme si l enfant changeait de mission.
- L enfant devient par exemple /bin/ls.

### wait
- Le parent attend qu un enfant se termine.

Pourquoi important:
- Evite d avoir des zombies.
- Permet un comportement propre et predictible du shell.

### getline
- Lit une ligne complete depuis stdin.
- Gere la memoire dynamiquement.

Pourquoi important:
- Lecture simple d une commande tapee.
- On s arrete proprement sur EOF (Ctrl+D).

### strtok
- Coupe une chaine en tokens selon des separateurs.
- Ici: espace, tabulation, retour ligne.

Pourquoi important:
- Transformer texte brut en tableau d arguments.

### PATH
- Variable d environnement contenant des repertoires separes par :
- Exemple logique: /usr/local/bin:/usr/bin:/bin

Pourquoi important:
- Le shell y cherche les executables.

### environ
- Tableau global de chaines formees comme NOM=VALEUR.

Pourquoi important:
- Permet de lire et modifier les variables d environnement.

## 5. Ce qu on a utilise et pourquoi

### Fonctions/system calls principales
- getppid: connaitre le parent
- getline: lire l entree utilisateur
- strtok: decouper la ligne
- fork: creer l enfant
- execve: lancer le programme cible
- wait: synchroniser parent et enfant
- stat: verifier qu un chemin existe
- environ: acceder a l environnement global
- strlen/strncmp/strchr/snprintf/malloc/free: construire et gerer les chaines et la memoire

### Pourquoi ces choix
- Ce sont les briques minimales et classiques d un shell Unix.
- Elles correspondent exactement aux objectifs pedagogiques de l exercice.

## 6. Explication fichier par fichier (ce que je dois savoir dire)

### 0-getppid.c
- Affiche le PPID.
- Message oral: je montre que le parent est le shell courant.

### 1-pid_max.sh
- Affiche la limite max des PID via /proc/sys/kernel/pid_max.
- Message oral: le noyau fixe une borne de PID.

### 0-av.c
- Affiche tous les arguments sans utiliser ac.
- Message oral: av est un tableau termine par NULL.

### 1-readline.c
- Affiche "$ ", lit avec getline, reaffiche, stop sur EOF.
- Message oral: base d une boucle interactive.

### 2-commandline.c
- Fonction split_line qui transforme une ligne en tableau de mots.
- Message oral: on passe du texte a des arguments exploitables.

### 3-fork_wait_execve_5.c
- Lance 5 fois ls -l /tmp dans 5 enfants successifs.
- Message oral: le pere cree, l enfant execute, le pere attend.

### 4-super_simple_shell.c
- Mini shell full path sans argument.
- Prompt, lecture, fork, execve, wait.
- Message oral: c est le flux complet minimal d un shell.

### 5-which_path.c
- Recherche un fichier dans PATH avec stat.
- Message oral: reproduit le principe de la commande which.

### 6-printenv_environ.c
- Affiche toutes les variables via environ.
- Message oral: environ est la source globale de l environnement.

### 7-env_vs_environ.c
- Compare les adresses de env et environ.
- Message oral: en pratique, ce sont la meme base de donnees.

### 8-getenv_custom.c
- Recode _getenv sans getenv.
- Message oral: on parcourt environ et on match NOM=.

### 9-path_print_dirs.c
- Affiche chaque dossier de PATH, un par ligne.
- Message oral: PATH est une liste de repertoires.

### 10-path_linked_list.c
- Construit une liste chainee de PATH.
- Message oral: exercice de structure de donnees applique a un cas reel.

### 11-setenv_custom.c
- Recode _setenv sans setenv.
- Message oral: ajouter/remplacer NOM=VALEUR avec gestion overwrite.

### 12-unsetenv_custom.c
- Recode _unsetenv sans unsetenv.
- Message oral: supprimer toutes les entrees d un nom donne.

## 7. Flux d execution d un shell (a reciter)

1. Afficher le prompt
2. Lire la ligne utilisateur
3. Nettoyer la ligne
4. Si ligne vide, recommencer
5. fork
6. Enfant: execve commande
7. Parent: wait
8. Recommencer

Phrase courte orale:
Le shell reste vivant dans le parent, et delegue l execution des commandes a des enfants.

## 8. Questions classiques de man review + bonnes reponses

### Pourquoi fork avant execve
- Parce que execve remplace le processus courant.
- Si on execve directement dans le shell, le shell disparait.

### Pourquoi wait dans le parent
- Pour attendre la fin de l enfant et garder un comportement propre.

### Pourquoi strtok modifie la chaine
- Il remplace les separateurs par des fins de chaine.
- C est pour cela qu on travaille sur une zone modifiable.

### Pourquoi utiliser environ
- Pour acceder a PATH et aux variables globales sans API cachee.

### Pourquoi stat pour which
- On veut verifier si un chemin candidat existe sur le disque.

### Pourquoi lire les pages man
- Pour connaitre prototype, retour, erreurs, et comportement exact.

## 9. Erreurs courantes a eviter

- Oublier de tester les retours d erreur
- Oublier free sur la memoire allouee
- Confondre parent et enfant apres fork
- Croire que execve revient toujours
- Mal gerer EOF sur getline
- Modifier PATH directement sans copie avant strtok

## 10. Mini script de presentation orale (2-3 minutes)

Je suis parti des bases Unix. D abord j ai verifie l identite des processus avec PPID, puis j ai travaille l entree utilisateur avec les arguments et getline. Ensuite j ai implemente le coeur d un shell avec fork, execve, wait: le parent garde le shell vivant, l enfant execute la commande. Apres ca, j ai reproduit la logique de recherche dans PATH, puis j ai manipule l environnement avec environ, _getenv, _setenv et _unsetenv. L idee generale est d assembler des briques simples et fiables pour construire un shell minimal, compréhensible et conforme aux consignes.

## 11. Checklist finale avant review

- Je sais definir PID et PPID
- Je sais expliquer fork/execve/wait dans l ordre
- Je sais expliquer pourquoi le shell ne doit pas execve lui meme
- Je sais expliquer comment on parse une ligne
- Je sais expliquer PATH et la recherche de commande
- Je sais expliquer environ et les variables NOM=VALEUR
- Je sais justifier les choix de fonctions utilises
- Je sais decrire chaque fichier en 1 phrase claire

## 12. Plan de revision conseille (45 minutes)

- 10 min: relire notions systeme (PID, fork, execve, wait)
- 10 min: relire parsing (getline, strtok, tableau d arguments)
- 10 min: relire PATH + environnement
- 10 min: rehearse oral avec le script section 10
- 5 min: refaire la checklist section 11
