#include "shell.h"

/**
 * add_node_end - add
 * @head: pointer to first listint_t node
 * @str: string
 * @n: int n of new struct
 *
 * Description: add element to the end of
 * the lists
 *
 * Return: size_t
 */
list_t *add_node_end(list_t **head, const char *str, int n)
{
	list_t *newnode;
	list_t *tmp;
	int len = 0;

	newnode = malloc(sizeof(list_t));
	if (head == NULL || newnode == NULL)
		return (NULL);

	newnode->num = n;
	while (str[len] != '\0')
		len++;

	newnode->str = malloc(sizeof(char) * (len + 1));
	if (newnode->str == NULL)
		return (NULL);
	newnode->str = _strdup(str);
	newnode->next = NULL;

	if (*head == NULL)
	{
		*head = newnode;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;

		tmp->next = newnode;
	}

	return (newnode);
}
