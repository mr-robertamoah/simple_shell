#include "shell.h"

/**
 * _realloc - allocate
 * @ptr: pointer to memory
 * @old_size: integer
 * @new_size: integer
 *
 * Description: allocate memory based on b
 *
 * Return: void *
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int i, min = old_size < new_size ? old_size : new_size;

	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	else if (old_size == new_size)
	{
		return (ptr);
	}
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	p = malloc(new_size * sizeof(char));

	if (p == NULL)
		return (NULL);

	for (i = 0; i < min; i++)
		*(p + i) = *(((char *) ptr) + i);

	free(ptr);
	return ((void *) p);
}
