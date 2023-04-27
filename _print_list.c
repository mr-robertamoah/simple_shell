#include "shell.h"

/**
 * print_list - print list
 * @h: struct list_s
 *
 * Description: print the elements of list_t and
 * return the number of nodes
 *
 * Return: size_t
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		if (h->str)
		/*	printf("[%u] %s\n", h->num, h->str);*/
/*		else*/
/*			printf("[0] (nil)\n");*/

		h = h->next;
		i++;
	}

	return (i);
}
