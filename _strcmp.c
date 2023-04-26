#include "shell.h"

/**
 * _strcmp - compare
 * @s1: pointer to string
 * @s2: pointer to string
 *
 * Description: compare two strings
 *
 * Return: char *
 */

int _strcmp(char *s1, char *s2)
{
	int len1 = _strlen(s1);
	int len2 = _strlen(s2);
	int i, sum1 = 0, sum2 = 0;

	for (i = 0; i <= len2 || i <= len1; i++)
	{

		if (i < len1)
			sum1 += s1[i];

		if (i < len2)
			sum2 += s2[i];
	}

	return (sum1 - sum2);
}
