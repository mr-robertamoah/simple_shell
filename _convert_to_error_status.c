#include "shell.h"

/**
* long_int_to_string - convert
* @num: long integer
* @str: string
*
* Description: convert number to string
*
* Return: void
*/
void long_int_to_string(long int num, char *str)
{
	int i = 0, j;

	if (num < 0)
	{
		*str++ = '-';
		num = -num;
		i = 1;
	}
	do {
		str[i++] = '0' + num % 10;
		num /= 10;
	} while (num);
	str[i] = '\0';
	if (*str == '-')
		++str;

	for (j = 0; j < i / 2; ++j)
	{
		char tmp = str[j];

		str[j] = str[i - j - 1];
		str[i - j - 1] = tmp;
	}
}

/**
* convert_to_string - convert
* @num: long integer
* @str: string
*
* Description: convert string to number
*
* Return: void
*/
void convert_to_string(long int num, char *str)
{

	long_int_to_string(num, str);
}

/**
* convert_to_error_status - convert
* @str: char pointer
*
* Description: convert string to number
*
* Return: int
*/
int convert_to_error_status(char *str)
{
	int i = 0, num = 0;

	if (str == NULL)
		return (1);

	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);

		num = (num * 10) + (str[i] - '0');
		i++;
	}

	return (num);
}
