#include "shell.h"

/**
* print_error - print
* @arv: pointer to char pointers (string)
* @argv: pointer to char pointers (string) from main
*
* Description: print error based on whether or not it
* is interactive mode
*
* Return: void
*/
void print_error(char **arv, char **argv)
{
	if (isatty(STDIN_FILENO))
	{
		_eputs(arv[0]);
		_eputs(": command not found\n");
		_eputchar(BUF_FLUSH);
		return;
	}

	_eputs(argv[0]);
	_eputs(": 1: ");
	_eputs(arv[0]);
	_eputs(": not found\n");
	_eputchar(BUF_FLUSH);
	exit(127);
}

/**
* run_based_on_path - run
* @arv: pointer to char pointers (string)
* @argv: pointer to char pointers (string) from main
* @info: pointer to char pointers (string) from main
*
* Description: run the commands parsed based on finding
* the command in a directory in a PATH
*
* Return: int
*/
int run_based_on_path(char **arv, char **argv, alias_info_t *info)
{
	char *path, *path_copy, *dir, *cmd_dir = NULL;
	int found = 0;

	path = get_env("PATH");
	path_copy = malloc(sizeof(char) * (1 + _strlen(path)));
	if (path_copy == NULL)
		memory_alloc_err(info);

	_strcpy(path_copy, path);
	dir = _strtok(path_copy, ":");
	while (dir != NULL)
	{
		free(cmd_dir);
		cmd_dir = malloc((_strlen(dir) + _strlen(arv[0]) + 2) * sizeof(char));
		_strcpy(cmd_dir, dir);
		_strcat(cmd_dir, "/");
		_strcat(cmd_dir, arv[0]);
		if (access(cmd_dir, X_OK) == 0)
		{
			arv[0] = malloc(sizeof(char) * (_strlen(cmd_dir) + 1));
			_strcpy(arv[0], cmd_dir);
			found = 1;
			break;
		}
		free(dir);
		dir = _strtok(NULL, ":");
	}
	free(path_copy);
	free(dir);
	free(cmd_dir);
	if (found)
		return (exec_cmd(arv, argv[0]));

	print_error(arv, argv);
	return (0);
}
