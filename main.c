#include "shell.h"

/**
* memory_alloc_err - error
* @info: alias_info_t *
*
* Description: print an error associated to memory allocation
* failure
*
* Return: void
*/
void memory_alloc_err(alias_info_t *info)
{
	free_aliases(info);
	perror("tsh: memory allocation failed");
	exit(EXIT_FAILURE);
}

/**
* __exit - exit
* @status: integer used to exit
* @arv: pointer to char pointers
* @info: pointer to char pointers
*
* Description: logout and exit
*
* Return: void
*/
void __exit(int status, char **arv, alias_info_t *info)
{
	free_aliases(info);
	if (arv)
	{
		free_all(arv);
		free(arv);
	}

	_exit(status);
}

/**
* init_info - init
* @info: alias_info_t *
*
* Description: initialize alias_info_t *
*
* Return: void
*/
void init_info(alias_info_t *info)
{
	if (!info)
	{
		info = malloc(sizeof(alias_info_t *));
		if (!info)
			memory_alloc_err(NULL);
	}

	info->aliases_n = 0;
	info->aliases_max = MAX_ALIASES;
	info->aliases = malloc(sizeof(alias_t *));
}

/**
 * main - simple shell
 * @ac: number of arguments
 * @argv: array of string arguments
 *
 * Description: a program to mimic the functionality
 * of /bin/sh
 *
 * Return: Always 0.
 */
int main(int __attribute__((unused)) ac, char **argv)
{
	char *r_char = NULL, **arv = NULL;
	size_t r_n = 0;
	ssize_t n_char = 0;
	int n_tokens = 0, is_interactive;
	alias_info_t *info = NULL;

	init_info(info);
	is_interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (is_interactive)
			write(1, "$ ", 2);
		n_char = get_line(&r_char, &r_n, STDIN_FILENO);
		if (n_char == -1)
		{
			free(r_char);
			_putchar('\n');
			__exit(1, NULL, NULL);
		}
		strip_comments(&r_char);
		set_n_tokens(&n_tokens, r_char);
		arv = malloc(sizeof(char *) * (n_tokens + 1));
		set_tokens(&arv, r_char);
		run_command(arv, argv, info);
		if (arv)
		{
			free_all(arv);
			free(arv);
		}
		if (info)
			free_aliases(info);
		if (r_char)
			free(r_char);
		r_n = 0;
		if (!is_interactive)
			__exit(1, NULL, info);
	}
	return (0);
}
