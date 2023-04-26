#include "shell.h"

/**
 * _strcpy - copies string
 * @src: the pointer of the string
 * @dest: the pointer of the destination buffer
 *
 * Description: copies one string into a buffer location
 *
 * Return: char *
 */

char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	if (src[i] == '\0')
	{
		dest[i] = '\0';

		return (dest);
	}

	while (src[i] != '\0')
	{
		*(dest + i) = src[i];

		i++;
	}

	dest[i] = src[i];

	return (dest);
}
