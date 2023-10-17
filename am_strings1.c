#include "header.h"

/**
 * _strdup - duplicates a string
 * @str: the string duplicate
 *
 * Return: pointer to duplicated
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *rett;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	rett = malloc(sizeof(char) * (len + 1));
	if (!rett)
		return (NULL);
	for (len++; len--;)
	{
		rett[len] = *--str;
	}
	return (rett);
}

/**
 * _strcat - just two strings
 * @dst: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcat(char *dst, char *src)
{
	char *rett = dst;

	while (*dst)
	{
	dst++;
	}
	while (*src)
	{
	*dst++ = *src++;
	}
	*dst = *src;
	return (rett);
}

/**
 * start_to - checks needle to starts haystack
 * @haystack: search string
 * @needle: find substring
 *
 * Return: address of next char or NULL
 */
char *start_to(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}


/**
 * _strcmp - comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative str1 < str2, positive str1 > str2, zero str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
		return (*str1 < *str2 ? -1 : 1);
}
