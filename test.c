#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

extern char **environ;
#define delim " \n"

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
		printf("%s\n", environ[i]);
}

/**
* memory_alloc_err - error
*
* Description: print an error associated to memory allocation
* failure
*
* Return: void
*/
void memory_alloc_err(void)
{
	perror("tsh: memory allocation failed");
	exit(1);
}

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
	char *built_ins[] = {"cd", "echo", "exit", "env", NULL};
	int i = 0;

	while (built_ins[i] != NULL)
	{
		if (strcmp(built_ins[i++], str) == 0)
			return (1);
	}

	return (0);
}

/**
* __exit - exit
*
* Description: logout and exit
*
* Return: void
*/
void __exit(void)
{
	printf("\nlogout\n");
	exit(1);
}

/**
* exec_cmd - execute
* @arv: pointer to char pointers (string)
* @pathname: pointer to chars
*
* Description: execute command using child process
*
* Return: void
*/
void exec_cmd(char **arv, char *pathname)
{
	pid_t c_id;

	c_id = fork();
	if (c_id == -1)
	{
		perror(pathname);
		exit(1);
	}
	else if (c_id == 0)
	{
		execve(arv[0], arv, environ);

		perror(pathname);
	}
	else
	{
		wait(&c_id);
	}
}

/**
* run_based_on_path - run
* @arv: pointer to char pointers (string)
* @argv: pointer to char pointers (string) from main
*
* Description: run the commands parsed based on finding
* the command in a directory in a PATH
*
* Return: void
*/
void run_based_on_path(char **arv, char **argv)
{
	char *path, *path_copy, *dir, *cmd_dir;
	int found = 0;

	path = getenv("PATH");
	path_copy = malloc(sizeof(char) * (1 + strlen(path)));
	if (path_copy == NULL)
		memory_alloc_err();

	strcpy(path_copy, path);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		cmd_dir = malloc((strlen(dir) + strlen(arv[0]) + 2) * sizeof(char));
		sprintf(cmd_dir, "%s/%s", dir, arv[0]);
		if (access(cmd_dir, X_OK) == 0)
		{
			arv[0] = malloc(sizeof(char) * (strlen(cmd_dir) + 1));
			strcpy(arv[0], cmd_dir);
			found = 1;
			free(cmd_dir);
			break;
		}
		dir = strtok(NULL, ":");
		free(cmd_dir);
	}
	free(path_copy);
	if (!found)
	{
		if (isatty(STDIN_FILENO))
			dprintf(STDERR_FILENO, "%s: command not found\n", arv[0]);
		else
		{
			dprintf(STDERR_FILENO, "%s: 1: %s: not found\n", argv[0], arv[0]);
			exit(1);
		}
	}
	else
		exec_cmd(arv, argv[0]);
}

/**
* run_command - run
* @arv: pointer to char pointers (string)
* @argv: pointer to char pointers (string) from main
*
* Description: run the commands parsed
*
* Return: void
*/
void run_command(char **arv, char **argv)
{
	if (is_built_in(arv[0]))
	{
		if (strcmp(arv[0], "exit") == 0)
			__exit();
		else if (strcmp(arv[0], "env") == 0)
			print_env();
	}
	else if (access(arv[0], X_OK) == 0)
	{
		exec_cmd(arv, argv[0]);
	}
	else
	{
		run_based_on_path(arv, argv);
	}
}

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
	while (str && str[i] != NULL)
		free(str[i++]);

	free(str);
}

/**
* set_n_tokens - tokens
* @n_tokens: pointer to number of tokens
* @r_char: pointer to chars
*
* Description: set the number of tokens
*
* Return: void
*/
void set_n_tokens(int *n_tokens, char *r_char)
{
	char *token_char = NULL, *r_char_copy;

	r_char_copy = malloc(sizeof(char) * (1 + strlen(r_char)));
	if (r_char_copy == NULL)
		memory_alloc_err();

	strcpy(r_char_copy, r_char);
	token_char = strtok(r_char_copy, delim);
	for (*n_tokens = 0; token_char != NULL; (*n_tokens)++)
		token_char = strtok(NULL, delim);
	free(r_char_copy);
}

/**
* set_tokens - tokens
* @arv: pointer to pointer to char pointers (string)
* @r_char: pointer to chars
*
* Description: set the tokens (commands, options, arguments) on
* the array
*
* Return: void
*/
void set_tokens(char ***arv, char *r_char)
{
	char *token_char = NULL, *r_char_copy;
	int i = 0;

	r_char_copy = malloc(sizeof(char) * (1 + strlen(r_char)));
	if (r_char_copy == NULL)
		memory_alloc_err();

	strcpy(r_char_copy, r_char);
	token_char = strtok(r_char_copy, delim);
	for (; token_char != NULL; i++)
	{
		(*arv)[i] = malloc(sizeof(char) * (strlen(token_char) + 1));
		strcpy((*arv)[i], token_char);
		token_char = strtok(NULL, delim);
	}
	(*arv)[i] = token_char;
	free(r_char_copy);
}

/**
* run_normally - run with arguments
* @ac: number of arguments
* @argv: pointer to pointer to char pointers (string)
*
* Description: run the shell with arguments and not interactively
*
* Return: void
*/
void run_normally(int ac, char **argv)
{
	char **arv;
	int i = 1;

	arv = malloc(sizeof(char *) * (ac + 1));
	for (; i < ac; i++)
		arv[i - 1] = argv[i];

	arv[i - 1] = NULL;
	run_command(arv, argv);
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
int main(int ac, char **argv)
{
	char *r_char = NULL, **arv;
	size_t r_n = 0;
	ssize_t n_char;
	int n_tokens = 0, i, is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		fflush(stdout);
		if (is_interactive)
			printf("$ ");

		n_char = getline(&r_char, &r_n, stdin);
		if (n_char == -1)
			__exit();

		set_n_tokens(&n_tokens, r_char);

		arv = malloc(sizeof(char *) * (n_tokens + 1));
		set_tokens(&arv, r_char);
		run_command(arv, argv);

		free_all(arv);
		r_char = NULL;
		r_n = 0;

		if (!is_interactive)
			exit(1);
	}

	return (0);
}
