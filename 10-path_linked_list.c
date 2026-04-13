#include <stdlib.h>
#include <string.h>

/**
 * struct path_node - linked list node for PATH directories
 * @dir: directory string
 * @next: pointer to next node
 */
struct path_node
{
    char *dir;
    struct path_node *next;
};

/**
 * add_node_end - appends a new node at the end of the list
 * @head: list head pointer
 * @dir: directory string
 *
 * Return: 0 on success, 1 on failure
 */
int add_node_end(struct path_node **head, const char *dir)
{
    struct path_node *new_node;
    struct path_node *tail;

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
    if (*head == NULL)
    {
        *head = new_node;
        return (0);
    }

    tail = *head;
    while (tail->next != NULL)
        tail = tail->next;
    tail->next = new_node;

    return (0);
}

/**
 * free_list - frees all nodes
 * @head: list head
 */
void free_list(struct path_node *head)
{
    struct path_node *tmp;

    while (head != NULL)
    {
        tmp = head->next;
        free(head->dir);
        free(head);
        head = tmp;
    }
}

/**
 * build_path_list - builds linked list from PATH variable
 *
 * Return: list head or NULL
 */
struct path_node *build_path_list(void)
{
    char *path_env;
    char *path_copy;
    char *dir;
    struct path_node *head;

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
            free(path_copy);
            free_list(head);
            return (NULL);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (head);
}
