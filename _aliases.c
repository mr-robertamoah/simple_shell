#include "shell.h"

/**
 * replace_alias - replace
 * @name: string
 * @command: string
 * @info: string
 *
 * Description: add alias to the array
 *
 * Return: void
 */
int replace_alias(char *name, char *command, alias_info_t *info)
{
	int i = 0;

	if (!info || !(info->aliases))
		return (0);
	while (i < info->aliases_n)
	{
		if (_strcmp(info->aliases[i].name, name) == 0 && command)
		{
			info->aliases[i].command = _realloc(info->aliases[i].command,
				_strlen(info->aliases[i].command) + 1,
				_strlen(command) + 1
			);
			_strcpy(info->aliases[i].command, command);
			return (1);
		}
	}

	return (0);
}

/**
 * add_alias - add
 * @name: string
 * @command: string
 * @info: string
 *
 * Description: add alias to the array
 *
 * Return: void
 */
int add_alias(char *name, char *command, alias_info_t *info)
{
	int replaced = 0;

	if (!info)
		init_info(info);

	if (!(info->aliases))
	{
		info->aliases = malloc(sizeof(alias_t) * info->aliases_max);
		if (!(info->aliases))
			perror("Error: failed to allocate memory for aliases");
		return (0);
	}

	replaced = replace_alias(name, command, info);
	if (replaced)
		return (1);

	if (info->aliases_n == info->aliases_max)
	{
		info->aliases = _realloc(info->aliases, info->aliases_n,
			(info->aliases_max += info->aliases_max));
		if (!(info->aliases))
			perror("Error: failed to reallocate memory for aliases");
		return (0);
	}

	(info->aliases[info->aliases_n]).name = _strdup(name);
	(info->aliases[info->aliases_n]).command = _strdup(command);

	if ((info->aliases[info->aliases_n]).name == NULL ||
		(info->aliases[info->aliases_n]).command == NULL)
	{
		free_aliases(info);
		perror("Error: failed to allocate memory for alias name or command");
		return (0);
	}
	return (1);
}

/**
 * free_aliases - print
 * @info: alias_info_t
 *
 * Description: prints name and command pair of aliases
 *
 * Return: void
 */
void free_aliases(alias_info_t *info)
{
	/*int i = 0;*/

	if (!info)
		return;

/*	while (i < info->aliases_n)
	{
		if (!(info->aliases + i))
		{
			i++;
			continue;
		}
		if ((info->aliases[i]).name)
			free((info->aliases[i]).name);
		if ((info->aliases[i]).command)
			free((info->aliases[i]).command);

		i++;
	}
*/
	info->aliases_n = 0;
	info->aliases_max = 0;
	if (info->aliases)
		free(info->aliases);
	info->aliases = NULL;
	free(info);
	info = NULL;
}

/**
 * print_alias - print
 * @name: string
 * @info: string
 *
 * Description: prints name and command pair of alias
 *
 * Return: void
 */
int print_alias(char *name, alias_info_t *info)
{
	int i = 0, j, name_len, command_len;

	if (!info || !(info->aliases) || name == NULL)
		return (0);

	while (i < info->aliases_n)
	{
		if ((info->aliases[i]).name && 
			_strcmp((info->aliases[i]).name, name) == 0)
		{
			name_len = _strlen((info->aliases[i]).name);
			for (j = 0; j < name_len; j++)
				_putchar(((info->aliases[i]).name)[j]);

			_putchar('=');

			if (info->aliases[i].command)
			{
				command_len = _strlen((info->aliases[i]).command);
				for (j = 0; j < command_len; j++)
					_putchar(((info->aliases[i]).command)[j]);
			}	
			_putchar('\n');
			break;
		}
		i++;
	}
	return (1);
}

/**
 * print_aliases - print
 * @info: alias_info_t *
 *
 * Description: prints name and command pair of aliases
 *
 * Return: void
 */
int print_aliases(alias_info_t *info)
{
	int i = 0, j, name_len, command_len;

	if (!info || !(info->aliases))
		return (0);

	while (i < info->aliases_n)
	{
		if (info->aliases[i].name)
		{
			name_len = _strlen((info->aliases[i]).name);
			for (j = 0; j < name_len; j++)
				_putchar(((info->aliases[i]).name)[j]);

			_putchar('=');
			if (info->aliases[i].command)
			{
				command_len = _strlen((info->aliases[i]).command);
				for (j = 0; j < command_len; j++)
					_putchar(((info->aliases[i]).command)[j]);
			}
			_putchar('\n');
		}
		i++;
	}
	return (1);
}
