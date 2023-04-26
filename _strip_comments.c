#include "shell.h"

/**
 * strip_comments - strip
 * @str: pointer of the string
 *
 * Description: strip the comments part of a string off
 *
 * Return: void
 */
void strip_comments(char **str)
{
	int i = 0;

	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '#')
		{
			(*str)[i] = '\0';
			break;
		}
		i++;
	}
}
