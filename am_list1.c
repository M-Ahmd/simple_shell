#include "header.h"

/**
 * am_list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t am_list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * am_list_to_strings - ........................................
 * @head: .....................................................
 *
 * Return: ...................................................
 */
char **am_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = am_list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * am_print_list - ............................................
 * @h: ........................................................
 *
 * Return: ....................................................
 */
size_t am_print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(am_convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * am_node_starts_with - ..............................................
 * @node: .............................................................
 * @prefix: ...........................................................
 * @c: ................................................................
 *
 * Return: ............................................................
 */
list_t *am_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_to(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * am_get_node_index - .....................
 * @head: ..................................
 * @node: ..................................
 *
 * Return: ................................
 */
ssize_t am_get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

