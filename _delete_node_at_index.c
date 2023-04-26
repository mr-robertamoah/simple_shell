#include "shell.h"

/**
 * delete_node_at_index - delete
 * @head: pointer to first listint_t node
 * @index: index to delete
 *
 * Description: delete a node at an index
 *
 * Return: int
 */
int delete_node_at_index(
	list_t **head, unsigned int index
)
{
	list_t *tmp, *another_tmp = NULL;
	unsigned int i = -1;

	tmp = *head;
	while (tmp != NULL)
	{
		i++;
		if (!tmp && i == 0 && i == index)
		{
			free(*head);
			return (1);
		}
		if (tmp && i == 0 && i == index)
		{
			*head = tmp->next;
			free(tmp);
			return (1);
		}
		if (i + 1 == index)
		{
			another_tmp = tmp->next;
			if (tmp->next)
				tmp->next = another_tmp->next;
			free(another_tmp);
			return (1);
		}
		if (tmp == NULL)
			return (-1);
		tmp = tmp->next;
	}

	return (-1);
}
