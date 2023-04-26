#include "shell.h"

/**
 * _strdup - create array
 * @str: string to make a copy of
 *
 * Description: create a copy of a string in
 * memory
 *
 * Return: pointer to char
 */

char *_strdup(const char *str)
{
	char *p;
	unsigned int i;
	unsigned int len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	len++;
	p = malloc(len * sizeof(char));

	if (!p)
		return (NULL);

	for (i = 0; i < len + 1; i++)
		*(p + i) = *(str + i);

	return (p);
}
