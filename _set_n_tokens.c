#include "shell.h"

/**
* set_n_tokens - tokens
* @n_tokens: pointer to number of tokens
* @r_char: pointer to chars
* @delim: pointer to chars
*
* Description: set the number of tokens
*
* Return: void
*/
void set_n_tokens(int *n_tokens, char *r_char, char *delim)
{
	char *token_char = NULL, *r_char_copy;

	if (!delim)
		delim = DELIM;

	r_char_copy = malloc(sizeof(char) * (1 + _strlen(r_char)));
	if (r_char_copy == NULL)
		memory_alloc_err(NULL);

	_strcpy(r_char_copy, r_char);
	token_char = _strtok(r_char_copy, delim);
	for (*n_tokens = 0; token_char != NULL; (*n_tokens)++)
	{
		free(token_char);
		token_char = _strtok(NULL, delim);
	}
	free(r_char_copy);
	free(token_char);
}
