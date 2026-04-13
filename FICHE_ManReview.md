# Fiche Man Review - super-simple_shell

## 1) Pitch court

Ce projet reconstruit les briques d un shell Unix:
- lecture commande
- creation processus
- execution programme
- attente parent
- recherche PATH
- gestion environnement

## 2) Definitions a connaitre

- Processus: programme en cours d execution.
- PID: identifiant unique du processus.
- PPID: identifiant du parent.
- EOF: fin d entree (Ctrl+D en terminal).
- PATH: liste de repertoires de recherche des executables.
- environ: tableau global de chaines NAME=value.

## 3) System calls / fonctions cle

- getppid: lire PPID.
- getline: lire une ligne complete.
- strtok: decouper une chaine en tokens.
- fork: dupliquer processus.
- execve: remplacer image processus.
- wait: attendre fin enfant.
- stat: verifier existence/metadata d un chemin.

## 4) Questions classiques + reponses

Q: Pourquoi fork avant execve?
A: execve remplace le processus appelant. Le shell doit rester vivant, donc execve est fait dans l enfant.

Q: Pourquoi wait dans le parent?
A: pour synchroniser et eviter des zombies.

Q: Pourquoi dupliquer PATH avant strtok?
A: strtok modifie la chaine source.

Q: Pourquoi tester NAME puis '=' dans _getenv/_setenv/_unsetenv?
A: pour eviter une collision de prefixe (ex: PATH vs PATHNAME).

## 5) Flux du shell minimal (4-super_simple_shell.c)

1. afficher prompt
2. getline
3. nettoyer newline
4. ignorer vide
5. fork
6. enfant: execve
7. parent: wait
8. recommencer

## 6) Fichiers et role a reciter

- 0-getppid.c: affiche PPID
- 1-pid_max.sh: affiche pid_max noyau
- 0-av.c: affiche argv sans ac
- 1-readline.c: prompt + getline + echo
- 2-commandline.c: split_line avec strtok
- 3-fork_wait_execve_5.c: 5 exec sequentiels
- 4-super_simple_shell.c: shell full path sans args
- 5-which_path.c: recherche binaire dans PATH
- 6-printenv_environ.c: print environnement via environ
- 7-env_vs_environ.c: compare env et environ
- 8-getenv_custom.c: recode getenv
- 9-path_print_dirs.c: affiche dirs PATH
- 10-path_linked_list.c: PATH en liste chainee
- 11-setenv_custom.c: recode setenv
- 12-unsetenv_custom.c: recode unsetenv

## 7) Points de vigilance en review

- verifier retours d erreur (fork, execve, wait, malloc)
- parler des allocations/liberations
- expliquer que execve ne retourne pas en cas de succes
- expliquer le NULL final dans argv/environ

## 8) Checklist finale

- je sais expliquer fork/execve/wait dans l ordre
- je sais expliquer PATH + stat
- je sais expliquer environ + format NAME=value
- je sais expliquer pourquoi strtok impose une copie
- je sais relier chaque fichier a une brique shell
