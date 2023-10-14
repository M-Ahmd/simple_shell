#include "header.h"

/**
 * _strcpy - copies string
 * @dst: the destination
 * @src: the source
 *
 * Return: pointer destination
 */
char *_strcpy(char *dst, char *src)
{
	int i = 0;

	if (dst == src || src == 0)
		return (dst);


	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

/**
 * _strlen - returns length
 * @str: the string length
 *
 * Return: length value
 */
int _strlen(char *str)
{
	int j = 0;

	if (!str)
	{
	return (0);
	}
	while (*str++)
		j++;
	return (j);
}


/**
 * _putchar - writes character a to output
 * @a: The character that wanna print
 *
 * Return: On success (1).
 * On error, -1 is returned.
 */
int _putchar(char a)
{
	static char buff[BUFSIZ];
	static int i;

	if (a == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buff[i++] = a;
	return (1);
}

/**
 *_puts - prints string
 *@str: the string that wanna be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
