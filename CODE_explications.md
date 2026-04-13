# Explications code - super-simple_shell

Ce document decrit le comportement exact de chaque fichier source.

## 0-getppid.c

Role:
- afficher le PPID du processus courant.

Logique:
1. getppid recupere l identifiant du parent.
2. printf affiche cette valeur.

## 1-pid_max.sh

Role:
- afficher la limite maximale des PID Linux.

Logique:
1. lecture de /proc/sys/kernel/pid_max.

## 0-av.c

Role:
- afficher tous les arguments sans utiliser ac.

Logique:
1. ignorer ac via (void)ac.
2. parcourir av jusqu au NULL final.
3. afficher chaque element.

## 1-readline.c

Role:
- prompt "$ ", lecture avec getline, reaffichage.

Logique:
1. initialiser line = NULL, len = 0.
2. afficher prompt et fflush.
3. getline lit la ligne complete.
4. sortir sur EOF/erreur.
5. afficher la ligne lue.
6. free(line) a la fin.

## 2-commandline.c

Role:
- split_line decoupe une ligne en mots.

Logique:
1. allouer un tableau dynamique de pointeurs.
2. strtok avec separateurs " \t\n".
3. agrandir le tableau via realloc quand besoin.
4. terminer le tableau par NULL.

## 3-fork_wait_execve_5.c

Role:
- executer "ls -l /tmp" dans 5 enfants, sequentiellement.

Logique:
1. boucle de 5 iterations.
2. fork.
3. enfant: execve.
4. parent: wait avant iteration suivante.

## 4-super_simple_shell.c

Role:
- shell minimal full path sans argument.

Flux:
1. prompt "#cisfun$ ".
2. getline.
3. suppression du '\n' final.
4. ignorer ligne vide.
5. run_cmd fait fork + execve + wait.
6. sortie propre sur EOF.

Fonctions:
- run_cmd: execute une commande avec environnement passe en parametre.
- main: boucle interactive.

## 5-which_path.c

Role:
- chercher un fichier dans PATH et afficher le premier chemin trouve.

Logique:
1. lire PATH via getenv.
2. dupliquer PATH (strtok modifie la chaine).
3. iterer chaque dossier.
4. construire dir/filename avec snprintf.
5. tester avec stat.

## 6-printenv_environ.c

Role:
- afficher toutes les variables d environnement via environ.

Logique:
1. parcourir environ jusqu a NULL.
2. afficher chaque entree.

## 7-env_vs_environ.c

Role:
- comparer adresse de env (3e parametre main) et environ.

Logique:
1. afficher les deux pointeurs.

## 8-getenv_custom.c

Role:
- implementer _getenv sans getenv.

Logique:
1. valider name.
2. parcourir environ.
3. trouver l entree "NAME=".
4. retourner pointeur sur la valeur.

## 9-path_print_dirs.c

Role:
- afficher chaque repertoire contenu dans PATH.

Logique:
1. lire PATH.
2. dupliquer PATH.
3. strtok avec ':'.
4. afficher chaque token.

## 10-path_linked_list.c / 10-path_linked_list.h

Role:
- construire une liste chainee de repertoires PATH.

Fonctions:
- add_node_end: ajoute un noeud en fin.
- free_list: libere toute la liste.
- build_path_list: parse PATH et construit la liste.

## 11-setenv_custom.c

Role:
- implementer _setenv sans setenv.

Fonctions internes:
- make_entry: construit "NAME=value".
- append_entry: ajoute une entree dans un nouveau tableau environ.

Logique _setenv:
1. valider name/value.
2. chercher variable existante.
3. si trouvee et overwrite actif: remplacer.
4. sinon: ajouter nouvelle entree.

## 12-unsetenv_custom.c

Role:
- implementer _unsetenv sans unsetenv.

Logique:
1. valider name.
2. parcourir environ.
3. sur match exact NAME=..., decaler le tableau vers la gauche.
4. continuer pour supprimer toutes les occurrences.

## environ_custom.h

Role:
- declaration partagee de extern char **environ.

## Qualite et verification

Commandes recommandees:

```sh
make clean
make all
betty-style *.c
betty-doc *.c
```

Le code est structure pour rester lisible:
- commentaires de fonction
- commentaires d etape dans les blocs critiques
- gestion explicite des erreurs systeme
