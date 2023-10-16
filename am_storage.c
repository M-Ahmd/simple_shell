#include "header.h"

/**
 **_memset - fills memory
 *@c: the pointer to the memory
 *@b: the byte to fill *c
 *@n: the amount of bytes
 *Return: (c) a pointer memmory
 */
char *_memset(char *c, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		c[i] = b;
	return (c);
}

/**
 * rep_string - replaces string
 * @ol: old string
 * @nw: new string
 *
 * Return: 1 if replaced, 0 if not repelacd
 */
int rep_string(char *nw, char **ol)
{
	free(*ol);
	*ol = nw;
	return (1);
}


/**
 * _realloc - book a block of memory
 * @ptr: pointer to previous block
 * @old: size of old block
 * @neww: size of new block
 *
 * Return: pointer to namelen.
 */
void *_realloc(void *ptr, unsigned int old, unsigned int neww)
{
	char *j;

	if (!ptr)
		return (malloc(neww));
	if (!neww)
                return (free(ptr), NULL);
	if (neww == old)
		return (ptr);

	j = malloc(neww);
	if (!j)
		return (NULL);

	old = old < neww ? old : neww;
	while (old--)
		j[old] = ((char *)ptr)[old];
	free(ptr);
	return (j);
}

/**
 * _free - frees a string
 * @cc: string
 */
void _free(char **cc)
{
	char **a = cc;

	if (!cc)
		return;
	while (*cc)
		free(*cc++);
	free(a);
}
