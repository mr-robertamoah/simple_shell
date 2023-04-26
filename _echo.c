#include "shell.h"

/**
 * _echo - echo
 * @arv: the pointer of the strings
 *
 * Description: prints all variables
 *
 * Return: void
 */
void _echo(char **arv)
{
	int i = 0, replace = 0;
	char str[20];

	if (!arv[1])
	{
		_putchar('\n');
		return;
	}

	if (_strcmp(arv[1], "$?") == 0)
	{
		i = 0;
		replace = 1;
	}
	else if (_strcmp(arv[1], "$$") == 0)
	{
		i = getpid();
		replace = 1;
	}

	if (replace)
	{
		convert_to_string(i, str);
		arv[1] = _realloc(arv[1], _strlen(arv[1]) + 1, _strlen(str) + 1);
		_strcpy(arv[1], str);
	}

	_puts(arv[1]);
}
