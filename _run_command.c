#include "shell.h"

#define MAX_ARV 10

/**
* handle_aliases - aliases
* @arv: pointer to char pointers (string)
* @info: pointer to char pointers (string)
*
* Description: handle aliases for adding and printing
*
* Return: int
*/
int handle_aliases(char **arv, alias_info_t *info)
{
	int i = 1, assign = 0;

	while (arv[i])
	{
		if (_strcmp(arv[i], "=") == 0 &&
			arv[i - 1] && _strlen(arv[i - 1]) > 1 &&
			arv[i + 1] && _strlen(arv[i + 1]) > 1
		)
		{
			add_alias(arv[i - 1], arv[i + 1], info);
			assign = 1;
		}
		i++;
	}

	if (assign)
		return (1);
	i = 1;
	while (arv[i])
	{
		if (arv[i] && _strlen(arv[i]) > 1)
		{
			print_alias(arv[i], info);
		}
		i++;
	}
	return (1);
}

/**
* _run - run
* @arv: pointer to char pointers (string)
* @argv: pointer to char pointers (string) from main
* @info: pointer to char pointers (string) from main
*
* Description: run the commands parsed
*
* Return: int
*/
int _run(char **arv, char **argv, alias_info_t *info)
{
	int status;

	if (_strcmp(arv[0], "alias") == 0)
	{
		if (arv[1] == NULL)
			return (print_aliases(info));
		return (handle_aliases(arv, info));
	}
	else if (is_built_in(arv[0]))
	{
		if (_strcmp(arv[0], "exit") == 0)
		{
			__exit(convert_to_error_status(arv[1]), arv, info);
		}
		else if (_strcmp(arv[0], "env") == 0)
			print_env();
		else if (_strcmp(arv[0], "pwd") == 0)
			get_cwd();
		else if (_strcmp(arv[0], "setenv") == 0)
			_setenv(arv[1], arv[2]);
		else if (_strcmp(arv[0], "unsetenv") == 0)
			_unsetenv(arv[1]);
		else if (_strcmp(arv[0], "cd") == 0)
			_cd(arv);
		else if (_strcmp(arv[0], "echo") == 0)
			_echo(arv);
		return (1);
	}
	else if (access(arv[0], X_OK) == 0)
		status = exec_cmd(arv, argv[0]);
	else
		status = run_based_on_path(arv, argv, info);
	return (status);
}

/**
* malloc_void - realloc
* @new_arv: pointer to char pointers (string)
* @info: pointer to char pointers (string)
*
* Return: void *
*/
char **malloc_void(char **new_arv, alias_info_t *info)
{
	if (new_arv)
		free_all(new_arv);

	new_arv = malloc(sizeof(char *) * MAX_ARV);
	if (!new_arv)
		memory_alloc_err(info);

	return (new_arv);
}

/**
* realloc_void - realloc
* @a_arv: pointer to char pointers (string)
* @arv_count: pointer to char pointers (string) from main
* @arv_max: integer pointer
* @info: integer pointer
*
* Return: void *
*/
void *realloc_void(void *a_arv, int arv_count, int *arv_max,
	alias_info_t *info)
{
	if (arv_count == *arv_max)
	{
		a_arv = _realloc(a_arv, arv_count, (*arv_max = *arv_max + MAX_ARV));
		if (!a_arv)
			memory_alloc_err(info);
	}

	return (a_arv);
}

/**
* run_command - run
* @arv: pointer to char pointers (string)
* @argv: pointer to char pointers (string) from main
* @info: pointer to char pointers (string) from main
*
* Description: run the commands parsed
*
* Return: void
*/
void run_command(char **arv, char **argv, alias_info_t *info)
{
	int i = 0, j = 0, status = 0, j_max = MAX_ARV;
	char **new_arv;

	new_arv = malloc(sizeof(char *) * MAX_ARV);
	if (!new_arv)
		memory_alloc_err(info);
	while (arv[i])
	{
		if (_strcmp(arv[i], ";") == 0 || _strcmp(arv[i], "||") == 0 ||
			_strcmp(arv[i], "&&") == 0)
		{
			new_arv[j] = NULL;
			status = _run(new_arv, argv, info);
			if (_strcmp(arv[i], "||") == 0 && status)
				return;
			if (_strcmp(arv[i], "&&") == 0 && !status)
				return;
			new_arv = malloc_void(new_arv, info);
			j = 0;
		}
		else
		{
			new_arv = realloc_void(new_arv, j, &j_max, info);
			new_arv[j++] = arv[i];
		}
		i++;
	}
	if (j)
	{
		new_arv[j] = NULL;
		_run(new_arv, argv, info);
	}
}
