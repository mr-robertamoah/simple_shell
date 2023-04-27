#include "shell.h"

/**
* set_tokens - tokens
* @arv: pointer to pointer to char pointers (string)
* @r_char: pointer to chars
* @delim: pointer to chars
*
* Description: set the tokens (commands, options, arguments) on
* the array
*
* Return: void
*/
void set_tokens(char ***arv, char *r_char, char *delim)
{
	char *token_char = NULL, *r_char_copy;
	int i = 0;

	if (!delim)
		delim = DELIM;

	r_char_copy = malloc(sizeof(char) * (1 + _strlen(r_char)));
	if (r_char_copy == NULL)
		memory_alloc_err(NULL);

	_strcpy(r_char_copy, r_char);
	token_char = _strtok(r_char_copy, DELIM);
	for (; token_char != NULL; i++)
	{
		(*arv)[i] = malloc(sizeof(char) * (_strlen(token_char) + 1));
		_strcpy((*arv)[i], token_char);
		free(token_char);
		token_char = _strtok(NULL, DELIM);
	}
	(*arv)[i] = token_char;
	free(r_char_copy);
	free(token_char);
}
