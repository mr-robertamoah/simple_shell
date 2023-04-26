#include "shell.h"

/**
* is_built_in - is built-in
* @str: char pointer (string)
*
* Description: determine if a command is built-in or not
*
* Return: int
*/
int is_built_in(char *str)
{
	char *built_ins[] = {
		"cd", "pwd", "exit", "env", "echo",
		"setenv", "unsetenv", NULL
	};
	int i = 0;

	if (str == NULL)
		return (0);

	while (built_ins[i] != NULL)
	{
		if (_strcmp(built_ins[i++], str) == 0)
			return (1);
	}

	return (0);
}
