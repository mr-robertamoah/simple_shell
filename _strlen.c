#include <stdio.h>

/**
 * _strlen - length of string
 * @s: the pointer of the string
 *
 * Description: gets the length of a string
 *
 * Return: int
 */

int _strlen(const char *s)
{
	int i = 0;

	if (s == NULL)
		return (i);

	while (s[i] != '\0')
		i++;

	return (i);
}
