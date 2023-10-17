#include "header.h"

/**
 * rm_inf - initializes
 * @inf: struct address
 */
void rm_inf(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * put_inf - initializes
 * @inf: struct address
 * @av: value vector
 */
void put_inf(info_t *inf, char **av)
{
	int i = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = am_strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		am_replace_alias(inf);
		am_replace_vars(inf);
	}
}

/**
 * freeStr_inf - frees struct
 * @inf: struct address
 * @all: true if freeing
 */
void freeStr_inf(info_t *inf, int all)
{
	_free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (inf->alias)
			am_free_list(&(inf->alias));
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->history)
			am_free_list(&(inf->history));
		if (inf->env)
			am_free_list(&(inf->env));
		_free(inf->environ);
			inf->environ = NULL;
		am_bfree((void **)inf->cmd_buf);
		if (inf->rfd > 2)
			close(inf->rfd);
		_putchar(BUF_FLUSH);
	}
}


