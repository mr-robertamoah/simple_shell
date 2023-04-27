#include "shell.h"

/**
* _setenv - set env
* @name: name of variable
* @value: value of variable
*
* Description: this is to set or modify the value of
* an environment variable
*
* Return: void
*/
void _setenv(const char *name, const char *value)
{
	int n_len, v_len, len, env_len, counter, env_modified;
	char *env, *env_string, **env_ptr;

	if ((name == NULL || name[0] == '\0') && set_error(EINVAL, NULL))
		return;
	n_len = _strlen(name), v_len = _strlen(value), len = n_len + v_len + 2;
	env = (char *) malloc(sizeof(char) * len);
	if (env == NULL && set_error(ENOMEM, NULL))
		return;

	_strcpy(env, name);
	env[n_len] = '=';
	_strcpy(env + n_len + 1, value);
	env_string = (char *) malloc(n_len + 2);
	if (env_string == NULL && set_error(ENOMEM, env))
		return;

	_strcpy(env_string, name);
	_strcat(env_string, "=");
	env_len = _strlen(env_string);
	env_modified = 0;
	for (env_ptr = environ, counter = 0; *env_ptr != NULL; env_ptr++, counter++)
		if (_strncmp(*env_ptr, env_string, env_len) == 0)
		{
			*env_ptr = env;
			env_modified = 1;
			free(env_string);
			break;
		}
	counter++;
	if (env_modified != 0)
		return;

	environ[counter] = NULL;
	environ[counter - 1] = malloc(sizeof(char) * len);
	if (environ[counter - 1] == NULL && set_error(ENOMEM, env))
		return;
	_strcpy(environ[counter - 1], env);
}
