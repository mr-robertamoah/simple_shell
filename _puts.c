#include "shell.h"

/**
 * _puts - prints string
 * @str: the pointer of the string
 *
 * Description: prints the string
 *
 * Return: void
 */

void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);

		i++;
	}
	_putchar('\n');
}
