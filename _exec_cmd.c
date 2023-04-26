#include "shell.h"

/**
* exec_cmd - execute
* @arv: pointer to char pointers (string)
* @pathname: pointer to chars
*
* Description: execute command using child process
*
* Return: int
*/
int exec_cmd(char **arv, char *pathname)
{
	pid_t c_id;
	int status;

	c_id = fork();
	if (c_id == -1)
	{
		perror(pathname);
		return (0);
	}
	else if (c_id == 0)
	{
		execve(arv[0], arv, environ);

		perror(pathname);

		exit(1);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			return (0);
		}

		return (1);
	}
}
