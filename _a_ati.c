#include "header.h"

/**
 * inter - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int inter(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->rfd <= 2);
}

/**
 * s_dlm - checks if character is a delimeter
 * @ch: the char to check
 * @dlm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int s_dlm(char ch, char *dlm)
{
	while (*dlm)
		if (*dlm++ == ch)
			return (1);
	return (0);
}

/**
 *_alpha - checks for alphabetic character
 *@in: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _alpha(int in)
{
	if ((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_ati - string to an integer
 *@str: the string
 *Return: 0 if no numbers in string
 */

int _ati(char *str)
{
	int i, sign = 1, flag = 0;
	int output;
	unsigned int res = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
	{
			sign *= -1;
	}

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
