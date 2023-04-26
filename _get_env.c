#include "shell.h"

/**
 * get_env - gets the value of an environ variable
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(char *name)
{
	int i = 0, len;
	char *p;

	len = _strlen(name);
	p = malloc(sizeof(char) * (len + 2));
	if (p == NULL)
		return (NULL);
	_strcpy(p, name);
	len++;
	p = _strcat(p, "=");
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], p, len) == 0)
		{
			free(p);
			return (environ[i] + len + 1);
		}
		i++;
	}

	free(p);
	return (NULL);
}
