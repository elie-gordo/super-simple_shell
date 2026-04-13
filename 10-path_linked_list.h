#ifndef PATH_LINKED_LIST_H
#define PATH_LINKED_LIST_H

/*
 * Declarations for PATH linked-list helpers used in exercise 10.
 */

/**
 * struct path_node - node for PATH directories linked list
 * @dir: directory string
 * @next: next node
 */
struct path_node
{
	char *dir;
	struct path_node *next;
};

int add_node_end(struct path_node **head, const char *dir);
void free_list(struct path_node *head);
struct path_node *build_path_list(void);

#endif