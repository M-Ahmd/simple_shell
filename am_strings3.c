#include "header.h"

/**
 * sstrncpy - just copies
 * @dst: the destination string
 * @src: the source string
 * @n: the number of characters
 * Return: the all string
 */
char *sstrncpy(char *dst, char *src, int n)
{
	int i;
	char *amr = dst;
	int j;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dst[i] = src[i];
		i++;
	}


	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dst[j] = '\0';
			j++;
		}
	}
	return (amr);
}

/**
 * sstrchr - locate the character
 * @str: the string
 * @ch: the character that you search for
 * Return: (str) a pointer area str
 */
char *sstrchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * sstrncat - concatenates strings
 * @dst: first string
 * @src: second string
 * @n: the number of bytes
 * Return: the concat string
 */
char *sstrncat(char *dst, char *src, int n)
{
	int i, j;
	char *am = dst;

	i = 0;
	while (dst[i] != '\0')
	{
		i++;
	}
	j = 0;

	while (src[j] != '\0' && j < n)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dst[i] = '\0';
	return (am);
}
