#include "shell.h"

/**
* _strtok - free
* @str: char pointers (string)
* @delim: char pointers serving as delimiters
*
* Description: get string before delimiters, return string
* and reposition pointer to after string
*
* Return: void
*/
char *_strtok(char *str, char *delim)
{
	static char *p_str;
	char *new_str;
	int i = 0, j, last_i = 0, found_delim = 0, set_str = 0;

	if (delim == NULL)
		return (str);

	if (str)
		p_str = str;
	else if (!p_str || _strlen(p_str) == 0 ||
			(p_str[0] == '\0' || p_str[0] == EOF))
		return (NULL);

	new_str = malloc(sizeof(char) * (_strlen(p_str) + 1));
	if (new_str == NULL)
		return (NULL);

	while (p_str[i] != '\0' && p_str[i] != EOF)
	{
		for (j = 0; delim[j] != '\0'; j++)
			if (p_str[i] == delim[j])
			{
				found_delim = 1;
				i++;
				continue;
			}

		if (found_delim && set_str)
			break;
		found_delim = 0;
		new_str[last_i++] = p_str[i++];
		set_str = 1;
	}
	if (last_i == 0)
		return (NULL);
	new_str[last_i] = '\0';
	p_str = str = p_str + i;
	return (new_str);
}
