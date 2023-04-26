#include "shell.h"

/**
* set_error - set error
* @err: value of variable
* @env: char pointer
*
* Description: this is to set or modify the value of
* an environment variable
*
* Return: int
*/
int set_error(int err, char *env)
{
	if (env)
		free(env);

	errno = err;

	return (1);
}

/**
* _unsetenv - unset env
* @name: name of variable
*
* Description: this is to unset an environment variable
*
* Return: void
*/
void _unsetenv(char *name)
{
	char *env_string, **env_ptr;
	int env_len, env_i, counter;

	env_string = (char *) malloc(_strlen(name) + 2);
	if (env_string == NULL && set_error(ENOMEM, NULL))
		return;

	_strcpy(env_string, name);
	_strcat(env_string, "=");
	env_len = _strlen(env_string);
	env_i = -1, counter = 0;
	for (env_ptr = environ; *env_ptr != NULL; env_ptr++, counter++)
		if (_strncmp(*env_ptr, env_string, env_len) == 0)
		{
			env_i = counter;
			free(env_string);
		}
	counter++;
	while (env_i > -1 && env_i != counter - 1)
	{
		if (environ[env_i + 1] != NULL)
		{
			environ[env_i] = (char *) malloc(
				sizeof(char) * (_strlen(environ[env_i + 1]) + 1));
			if (environ[env_i] == NULL && set_error(ENOMEM, NULL))
				return;

			_strcpy(environ[env_i], environ[env_i + 1]);
		}
		else
		{
			environ[env_i] = NULL;
			free(environ[env_i + 1]);
			break;
		}
		env_i++;
	}
}
