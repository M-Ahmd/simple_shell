#include "header.h"

/**
 * _prt_env - print current enviro
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
int _prt_env(info_t *inf)
{
	print_ali_str(inf->env);
	return (0);
}

/**
 * get_val_env - gets the value of variable
 * @inf: Structure potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *get_val_env(info_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *p;

	while (node)
	{
		p = start_to(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _init_setv - Initialize environment var
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _init_setv(info_t *inf)
{
	if (inf->argc != 3)
	{
		am_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_rell_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _rm_setv - Remove environ variable
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _rm_setv(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		am_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_another_setv(inf, inf->argv[i]);

	return (0);
}

/**
 * pop_env_linklist - populates environ linked list
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
int pop_env_linklist(info_t *inf)
{
	list_t *node = NULL;
	ssize_t i;

	for (i = 0; environ[i]; i++)
	{
		am_add_node_end(&node, environ[i], 0);
	}
	inf->env = node;
	return (0);
}
