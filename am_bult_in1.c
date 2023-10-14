#include "header.h"

/**
 * _this_is_hist- displays the history list
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _this_is_hist(info_t *inf)
{
	am_print_list(inf->history);
	return (0);
}

/**
 * uns_ali_str - sets alias string
 * @inf: value struct
 * @strg: the string alias
 *
 * Return: Always 0 if success,else 0.
 */
int uns_ali_str(info_t *inf, char *strg)
{
	int retur;
	char *a, c;

	a = sstrchr(strg, '=');
	if (!a)
		return (1);
	c = *a;
	*a = 0;
	retur = am_delete_node_at_index(&(inf->alias),
			am_get_node_index(inf->alias, am_node_starts_with(inf->alias, strg, -1)));
	*a = c;
	return (retur);
}

/**
 * s_ali_str - sets alias to string
 * @inf: value struct
 * @str: the string alias
 *
 * Return: Always 0 if success, else 1.
 */
int s_ali_str(info_t *inf, char *str)
{
	char *c;

	c = sstrchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (uns_ali_str(inf, str));

	uns_ali_str(inf, str);
	return (am_add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_ali_str - prints the alias string
 * @node: the node
 *
 * Return: Always 0 if success, else 1
 */
int print_ali_str(list_t *node)
{
	char *p = NULL;
	char *a = NULL;

	if (node)
	{
		p = sstrchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_ali_str - alias builtin
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _my_ali_str(info_t *inf)
{
	list_t *node = NULL;
	int i = 0;
	char *p = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_ali_str(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; inf->argv[i]; i++)
	{
		p = sstrchr(inf->argv[i], '=');
		if (p)
			s_ali_str(inf, inf->argv[i]);
		else
			print_ali_str(am_node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}


