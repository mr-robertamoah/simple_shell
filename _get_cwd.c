#include "shell.h"

/**
* get_cwd - print
*
* Description: print the current working directory
*
* Return: void
*/
void get_cwd(void)
{
	char pwd[BUF];

	getcwd(pwd, sizeof(pwd));

	_puts(pwd);
}
