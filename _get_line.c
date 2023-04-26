#include "shell.h"

/**
* free_return - return
* @buffer: char pointer
*
* Description: free buffer and return with -1
*
* Return: int
*/
int free_return(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	return (-1);
}

/**
* get_line - get line
* @str: pointer to char pointer
* @n: size_t pointer
* @fd: integer
*
* Description: get the characters from the line
* in interactive mood
*
* Return: int
*/
int get_line(char **str, size_t *n, int fd)
{
	int old_cap = 0, capacity;
	char *buffer = NULL;
	size_t total = 0, nread = 0;

	if (!str || !n)
		return (-1);
	capacity = *n == 0 ? 1 : *n;
	buffer = malloc(sizeof(char) * capacity);
	if (!buffer)
		return (-1);
	while ((nread = read(fd, buffer + total, capacity - total)) > 0)
	{
		total += nread;
		if (total >= (size_t) capacity)
		{
			old_cap = capacity;
			capacity *= 2;
			buffer = _realloc(buffer, old_cap, capacity);
			if (!buffer)
				return (free_return(buffer));

			*str = buffer;
			*n = capacity;
		}
		if (buffer[total - 1] == '\n')
			break;
	}
	if ((nread == 0 && total == 0) || (int) nread == -1)
	{
		*n = 0;
		*str = NULL;
		return (free_return(buffer));
	}

	buffer[total] = '\0';
	return (total);
}
