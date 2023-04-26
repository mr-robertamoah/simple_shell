#include "shell.h"

/**
* free_all - free
* @str: pointer to char pointers (string)
*
* Description: free up all the strings as well as the pointer
*
* Return: void
*/
void free_all(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
		free(str[i++]);

	/*free(str);*/
}
