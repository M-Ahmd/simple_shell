#include "header.h"

/**
 * get_env_str - returns the string array copy
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
char **get_env_str(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = am_list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _another_setv - Remove env variable
 * @inf: Structure containing potential arguments.
 * @var: the string env
 * Return: 1 on delete, 0 otherwise
 */
int _another_setv(info_t *inf, char *var)
{
	list_t *node = inf->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = start_to(node->str, var);
		if (p && *p == '=')
		{
			inf->env_changed = am_delete_node_at_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _rell_setenv - Initialize a new variable,
 * @inf: Structure containing potential arguments.
 * @var: the string var
 * @val: the string value
 *  Return: Always 0
 */
int _rell_setenv(info_t *inf, char *var, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = inf->env;
	while (node)
	{
		p = start_to(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	am_add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}


