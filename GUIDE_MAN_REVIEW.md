# Fiche de revision man review - decomposition complete A a Z

Objectif:
- qu une personne debutante puisse ouvrir le code et tout comprendre
- expliquer chaque element de chaque fichier
- savoir repondre au pourquoi de chaque choix

Comment lire cette fiche:
- pour chaque fichier: role, lecture pas a pas, logique, erreurs possibles, phrase orale prete

--------------------------------------------------

## 1) 0-getppid.c

Role du fichier:
- afficher le PPID (parent process id) du processus courant

Lecture pas a pas:
1. include stdio.h
- apporte printf pour afficher du texte

2. include sys/types.h
- apporte le type pid_t

3. include unistd.h
- apporte getppid

4. main(void)
- programme sans arguments

5. declaration pid_t parent_pid
- reserve une variable adaptee aux id processus

6. parent_pid = getppid()
- recupere le pid du parent

7. printf("%u\n", (unsigned int)parent_pid)
- affiche le nombre
- cast en unsigned int pour format d affichage stable

8. return 0
- fin normale

Pourquoi ce code est ecrit comme ca:
- minimal et strict pour montrer uniquement PPID

Si on retire un bloc:
- sans unistd.h -> getppid non declare
- sans parent_pid -> pas de stockage du resultat

Phrase orale prete:
Ce fichier montre la relation parent/enfant entre processus en affichant le parent du programme lance.

--------------------------------------------------

## 2) 1-pid_max.sh

Role du fichier:
- afficher la limite maximale de PID du noyau Linux

Lecture pas a pas:
1. #!/bin/sh
- indique quel interpreteur execute le script

2. cat /proc/sys/kernel/pid_max
- lit le fichier virtuel du noyau expose dans /proc

Pourquoi ce code est ecrit comme ca:
- c est la source systeme directe de la valeur pid_max

Si on retire un bloc:
- sans shebang le script peut ne pas etre execute correctement selon contexte

Phrase orale prete:
On lit une valeur noyau dans /proc pour connaitre la borne maximale des PID.

--------------------------------------------------

## 3) 0-av.c

Role du fichier:
- afficher tous les arguments sans utiliser ac

Lecture pas a pas:
1. include stdio.h
- printf

2. main(int ac, char **av)
- ac = nombre d arguments
- av = tableau de chaines termine par NULL

3. unsigned int i
- index de parcours

4. (void)ac
- marque ac comme volontairement non utilise

5. i = 0
- debut du tableau

6. while (av[i] != NULL)
- parcourt jusqu a la sentinelle NULL

7. printf("%s\n", av[i])
- affiche argument courant

8. i++
- passe au suivant

9. return 0
- fin normale

Pourquoi ce code est ecrit comme ca:
- la consigne impose de ne pas utiliser ac
- av suffit grace a NULL final

Si on retire un bloc:
- sans condition NULL on sort du tableau

Phrase orale prete:
J utilise la fin NULL de av pour parcourir tous les arguments sans me servir de ac.

--------------------------------------------------

## 4) 1-readline.c

Role du fichier:
- boucle interactive: prompt, lecture, reaffichage

Lecture pas a pas:
1. define _POSIX_C_SOURCE 200809L
- expose getline en environnement POSIX

2. includes
- stdio.h: printf, fflush, getline
- stdlib.h: free
- sys/types.h: ssize_t
- unistd.h: environnement POSIX

3. variables
- char *line: buffer dynamique
- size_t len: taille buffer
- ssize_t nread: nb caracteres lus

4. initialisation
- line = NULL
- len = 0
- getline alloue le buffer

5. while (1)
- boucle shell-like

6. printf("$ ")
- prompt

7. fflush(stdout)
- force affichage du prompt avant saisie

8. nread = getline(&line, &len, stdin)
- lit une ligne complete

9. if (nread == -1) break
- EOF ou erreur -> sortir

10. printf("%s", line)
- reaffiche ce qui a ete lu

11. free(line)
- liberation memoire allouee par getline

12. return 0

Pourquoi ce code est ecrit comme ca:
- getline est le moyen robuste demande par la consigne

Si on retire un bloc:
- sans free -> fuite memoire
- sans fflush -> prompt peut apparaitre en retard

Phrase orale prete:
Ce fichier reproduit le cycle de base d un shell interactif en gerant proprement EOF.

--------------------------------------------------

## 5) 2-commandline.c

Role du fichier:
- fonction split_line qui transforme une ligne en tableau de mots

Lecture pas a pas:
1. define POSIX + includes
- stdlib.h pour malloc/realloc/free
- string.h pour strtok

2. signature
- char **split_line(char *line)
- retourne un tableau de pointeurs de mots

3. variables
- token: mot courant
- words: tableau final
- tmp: tampon securise pour realloc
- size: capacite tableau
- i: index

4. size = 8
- capacite initiale simple

5. words = malloc(size * sizeof(char *))
- reserve tableau de pointeurs

6. if words == NULL return NULL
- gestion echec allocation

7. token = strtok(line, " \t\n")
- premier mot

8. while (token != NULL)
- tant qu il y a un mot

9. words[i] = token; i++
- stocke mot

10. si i + 1 >= size
- agrandit tableau
- size *= 2
- tmp = realloc(...)
- si tmp == NULL -> free(words), return NULL
- sinon words = tmp

11. token = strtok(NULL, " \t\n")
- mot suivant

12. words[i] = NULL
- terminaison obligatoire du tableau

13. return words

Pourquoi ce code est ecrit comme ca:
- respecte la consigne strtok
- dynamique pour eviter une limite fixe fragile

Attention logique:
- strtok modifie line en remplaçant les separateurs par \0

Phrase orale prete:
Cette fonction convertit du texte brut en structure exploitable par un exec.

--------------------------------------------------

## 6) 3-fork_wait_execve_5.c

Role du fichier:
- lancer ls -l /tmp dans 5 enfants successifs

Lecture pas a pas:
1. includes process
- sys/wait.h pour wait
- unistd.h pour fork/execve

2. variables
- child_pid
- status
- i
- argv = {"/bin/ls", "-l", "/tmp", NULL}

3. for i=0 a 4
- boucle 5 executions

4. child_pid = fork()
- duplique processus

5. if child_pid == -1
- echec fork -> perror + return 1

6. if child_pid == 0
- enfant
- execve(argv[0], argv, NULL)
- si echec execve -> perror + return 1

7. else
- parent
- wait(&status)
- si echec wait -> perror + return 1

8. return 0

Pourquoi ce code est ecrit comme ca:
- wait dans la boucle = execution sequentielle stricte

Si on retire wait:
- les enfants partent potentiellement en parallele, non conforme demande

Phrase orale prete:
Le pere cree un enfant, l enfant se remplace par ls, le pere attend, puis recommence.

--------------------------------------------------

## 7) 4-super_simple_shell.c

Role du fichier:
- mini shell qui execute des chemins absolus sans argument

Lecture pas a pas:
1. define POSIX + includes I/O/process

2. extern char **environ
- pour transmettre l environnement a execve

3. variables
- line, len, nread
- child_pid, status
- argv[2]

4. init line=NULL, len=0

5. boucle infinie
- affiche prompt #cisfun$
- fflush
- getline
- stop si -1

6. nettoyage de ligne
- si dernier caractere est \n -> remplacer par \0

7. if line vide continue
- ignore entree vide

8. fork
- erreur -> perror, free(line), return 1

9. enfant
- argv[0] = line
- argv[1] = NULL
- execve(argv[0], argv, environ)
- si echec -> perror, return 1

10. parent
- wait(&status)

11. fin boucle
- free(line)
- return 0

Pourquoi ce code est ecrit comme ca:
- c est le squelette minimal d un shell
- parent reste resident
- enfant execute commande

Point man review:
- pas de parsing arguments ici, volontairement conforme consigne

Phrase orale prete:
Ce shell lit une commande, cree un enfant pour l executer, et le parent attend avant de proposer la suivante.

--------------------------------------------------

## 8) 5-which_path.c

Role du fichier:
- chercher un nom de fichier dans PATH

Lecture pas a pas (fonction print_found_path):
1. getenv("PATH")
- recupere PATH

2. strdup(path_env)
- copie necessaire avant strtok

3. dir = strtok(path_copy, ":")
- premier dossier

4. boucle sur chaque dossier
- calcule needed = strlen(dir)+1+strlen(filename)+1
- malloc(needed)
- snprintf(fullpath, needed, "%s/%s", dir, filename)
- stat(fullpath, &st)
- si trouve: printf(fullpath), free, return 0
- sinon free(fullpath) et dossier suivant

5. fin
- free(path_copy)
- return 1

Lecture pas a pas (main):
1. verifier ac < 2 -> afficher usage
2. boucle sur chaque argument utilisateur
3. appeler print_found_path
4. si retour non zero -> not found

Pourquoi ce code est ecrit comme ca:
- separation logique: recherche dans fonction, I/O utilisateur dans main

Phrase orale prete:
Je parcours chaque dossier de PATH, je construis dir/fichier, et je teste avec stat.

--------------------------------------------------

## 9) 6-printenv_environ.c

Role du fichier:
- afficher toutes les variables d environnement

Lecture pas a pas:
1. extern char **environ
2. i=0
3. while environ[i] != NULL
4. printf(environ[i])
5. i++
6. return 0

Pourquoi ce code est ecrit comme ca:
- exercice direct sur variable globale environ

Phrase orale prete:
J affiche chaque entree NOM=VALEUR jusqu a la sentinelle NULL.

--------------------------------------------------

## 10) 7-env_vs_environ.c

Role du fichier:
- comparer env (parametre main) et environ (globale)

Lecture pas a pas:
1. extern char **environ
2. main(..., char **env)
3. (void)ac et (void)av pour eviter warnings
4. printf des adresses avec %p
5. return 0

Pourquoi ce code est ecrit comme ca:
- preuve pratique de la relation env/environ

Phrase orale prete:
Je compare les adresses memoire pour verifier si env et environ pointent la meme zone.

--------------------------------------------------

## 11) 8-getenv_custom.c

Role du fichier:
- reimplementer getenv sans utiliser getenv

Lecture pas a pas:
1. include string.h
- strlen et strncmp

2. extern char **environ

3. signature _getenv(const char *name)

4. variables
- name_len
- env pointeur de parcours

5. validation
- si name NULL ou vide -> NULL

6. name_len = strlen(name)

7. env = environ

8. boucle while (*env != NULL)
- verifier prefixe exact:
  - strncmp(*env, name, name_len) == 0
  - et caractere suivant == '='
- si match retourner pointeur sur valeur:
  - &((*env)[name_len + 1])
- sinon env++

9. return NULL si non trouve

Pourquoi ce code est ecrit comme ca:
- test du '=' evite faux match de prefixe

Phrase orale prete:
Je parcours environ et je cherche exactement NOM=, puis je retourne l adresse de la valeur.

--------------------------------------------------

## 12) 9-path_print_dirs.c

Role du fichier:
- fonction qui affiche chaque dossier de PATH

Lecture pas a pas:
1. includes stdio/stdlib/string
2. signature void print_path_dirs(void)
3. lire PATH avec getenv
4. si PATH absent -> return
5. dupliquer PATH avec strdup
6. si echec alloc -> return
7. strtok par ':'
8. boucle printf dossier
9. free(path_copy)

Pourquoi ce code est ecrit comme ca:
- simple, conforme et sur (copie avant strtok)

Phrase orale prete:
Je lis PATH, je le decoupe par ':', et j affiche chaque dossier sur sa propre ligne.

--------------------------------------------------

## 13) 10-path_linked_list.c

Role du fichier:
- construire une liste chainee des dossiers PATH

Lecture pas a pas:
1. struct path_node
- dir: chaine dossier
- next: pointeur suivant

2. add_node_end
- alloue new_node
- duplique dir
- si head NULL -> devient tete
- sinon trouve dernier noeud et accroche
- return 0/1

3. free_list
- parcourt noeuds
- libere dir puis noeud

4. build_path_list
- lit PATH
- copie PATH
- init head NULL
- strtok(':')
- pour chaque dir: add_node_end
- si erreur: free(path_copy), free_list(head), return NULL
- fin: free(path_copy), return head

Pourquoi ce code est ecrit comme ca:
- responsibilities separees: ajout, liberation, construction

Phrase orale prete:
Je transforme la chaine PATH en structure liste pour manipuler facilement les dossiers ensuite.

--------------------------------------------------

## 14) 11-setenv_custom.c

Role du fichier:
- ajouter ou modifier une variable d environnement sans setenv

Lecture pas a pas:
1. define POSIX + includes
- stdio pour snprintf
- stdlib pour malloc/free
- string pour strlen/strncmp/strchr

2. extern char **environ

3. signature _setenv(name, value, overwrite)

4. variables
- i index parcours environ
- name_len longueur du nom
- entry_len longueur "name=value\0"
- entry chaine construite
- new_environ nouveau tableau de pointeurs

5. validation entree
- name NULL -> erreur
- value NULL -> erreur
- name vide -> erreur
- name contient '=' -> erreur

6. name_len = strlen(name)

7. recherche d une variable existante
- boucle for tant que environ[i] != NULL
- test exact du nom + '='

8. si variable existe
- if !overwrite -> return 0 (ne change rien)
- sinon:
  - calcul entry_len
  - malloc(entry_len)
  - snprintf(entry, ..., "%s=%s", name, value)
  - environ[i] = entry
  - return 0

9. si variable n existe pas
- calcul entry_len
- malloc(entry)
- snprintf entry
- malloc nouveau tableau (i+2)
  - +1 pour nouvelle variable
  - +1 pour NULL final
- copie des anciens pointeurs dans new_environ
- environ = new_environ
- environ[i] = entry
- environ[i+1] = NULL
- return 0

Pourquoi ce code est ecrit comme ca:
- reproduit semantique setenv (ajouter ou remplacer selon overwrite)

Attention a connaitre:
- cette version ne libere pas explicitement ancienne chaine remplacee
- acceptable pour exercice pedagogique, a mentionner honnetement

Phrase orale prete:
Je valide les entrees, je cherche la variable, puis soit je remplace selon overwrite, soit j agrandis l environnement pour ajouter une nouvelle entree.

--------------------------------------------------

## 15) 12-unsetenv_custom.c

Role du fichier:
- supprimer une variable de l environnement sans unsetenv

Lecture pas a pas:
1. define POSIX + include string
2. extern char **environ
3. signature _unsetenv(const char *name)

4. variables
- i index principal
- j index decalage
- name_len longueur du nom

5. validation
- name NULL -> erreur
- name vide -> erreur
- name contient '=' -> erreur

6. name_len = strlen(name)

7. boucle principale sur environ
- si entree correspond a name=
  - boucle interne j pour decalage a gauche
    - environ[j] = environ[j+1]
  - i-- pour reexaminer position courante

8. return 0

Pourquoi ce code est ecrit comme ca:
- suppression dans tableau en place = decalage

Phrase orale prete:
Quand je trouve la variable, je ferme le trou en decalant tout le tableau d une case vers la gauche.

--------------------------------------------------

## 16) Makefile

Role du fichier:
- compiler rapidement les programmes et verifier les fichiers fonctions

Lecture pas a pas:
1. CC et CFLAGS
- choix du compilateur et des drapeaux stricts

2. PROGRAMS
- cibles qui ont un main et produisent executables

3. FUNC_OBJECTS
- fichiers sans main compiles en .o

4. all: programs functions
- cible par defaut

5. regles de chaque executable
- exemple: ppid: 0-getppid.c
- commande compile vers binaire

6. regles .o des fonctions
- compile avec -c

7. clean
- supprime binaires et objets

8. re
- clean puis all

Pourquoi ce code est ecrit comme ca:
- evite commandes manuelles longues
- garantit compilation complete du depot

--------------------------------------------------

## 17) README.md

Role du fichier:
- expliquer la structure du depot et les commandes de build

Lecture pas a pas:
1. titre + description du projet
2. liste fichiers programmes
3. liste fichiers fonctions
4. section script
5. section build
6. section revision avec liens vers fiches

Pourquoi ce code est ecrit comme ca:
- onboarding rapide pour correcteur et etudiant

--------------------------------------------------

## 18) Comment expliquer la logique globale en 45 secondes

J ai commence par comprendre les processus et les arguments, ensuite la lecture utilisateur et le parsing. Apres cela, j ai implemente le coeur d un shell avec fork, execve et wait. Puis j ai ajoute la resolution de commande dans PATH et la manipulation d environnement avec des fonctions custom. Chaque fichier isole une competence precise pour garder un code lisible, testable et conforme a la consigne.

--------------------------------------------------

## 19) Questions pieges frequentes et reponses courtes

Pourquoi fork avant execve ?
- Parce que execve remplace le processus courant. Sans fork, le shell disparait.

Pourquoi wait ?
- Pour synchroniser le parent et eviter des processus zombies.

Pourquoi dupliquer PATH avant strtok ?
- strtok modifie la chaine, il faut proteger la source.

Pourquoi verifier '=' dans _getenv/_setenv/_unsetenv ?
- Pour matcher exactement le nom de variable.

Pourquoi tableaux termines par NULL ?
- C est le contrat de parcours C/POSIX pour chaines de pointeurs.

--------------------------------------------------

## 20) Mini checklist avant review

- Je peux expliquer chaque include de chaque fichier
- Je peux expliquer chaque variable et son type
- Je peux decrire le flux de control (boucles et conditions)
- Je peux justifier chaque appel systeme/libc
- Je peux dire ce qui se passe en cas d erreur
- Je peux expliquer pourquoi le parent shell reste vivant
- Je peux expliquer la gestion memoire utilisee
