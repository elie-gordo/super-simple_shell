#include <stdlib.h>
#include <string.h>
#include "10-path_linked_list.h"

/**
 * add_node_end - ajoute un nouveau noeud en fin de liste
 * @head: pointeur vers la tete de liste
 * @dir: chaine du dossier
 *
 * Return: 0 en cas de succes, 1 en cas d'echec
 */
int add_node_end(struct path_node **head, const char *dir)
{
	struct path_node *new_node;
	struct path_node *tail;

	/* Allocate node and duplicate payload string. */
	new_node = malloc(sizeof(struct path_node));
	if (new_node == NULL)
		return (1);
	new_node->dir = strdup(dir);
	if (new_node->dir == NULL)
	{
		free(new_node);
		return (1);
	}
	new_node->next = NULL;
	/* Empty list case: new node becomes head. */
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	/* Non-empty list: walk to tail and chain new node. */
	tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = new_node;
	return (0);
}

/**
 * free_list - libere tous les noeuds de la liste
 * @head: tete de liste
 */
void free_list(struct path_node *head)
{
	struct path_node *tmp;

	/* Free payload then node, moving forward safely. */
	while (head != NULL)
	{
		tmp = head->next;
		free(head->dir);
		free(head);
		head = tmp;
	}
}

/**
 * build_path_list - construit une liste chainee a partir de PATH
 *
 * Return: tete de liste ou NULL
 */
struct path_node *build_path_list(void)
{
	char *path_env;
	char *path_copy;
	char *dir;
	struct path_node *head;

	/* Retrieve PATH and create a writable copy for tokenization. */
	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);
	head = NULL;
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		if (add_node_end(&head, dir) != 0)
		{
			/* Clean everything on allocation failure. */
			free(path_copy);
			free_list(head);
			return (NULL);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (head);
}
