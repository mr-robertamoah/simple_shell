#include "shell.h"

/**
* print_env - print
*
* Description: print the content of the global
* environ variable
*
* Return: void
*/
void print_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_puts(environ[i]);
	}
}
