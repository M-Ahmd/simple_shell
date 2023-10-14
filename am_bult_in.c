#include "header.h"

/**
 * _shell_exit - exits the shell
 * @inf: Structure contain potential value.
 *  Return: exits and status
 */
int _shell_exit(info_t *inf)
{
	int excheck;

	if (inf->argv[1])
	{
		excheck = am_erratoi(inf->argv[1]);
		if (excheck == -1)
		{
			inf->status = 2;
			am_print_error(inf, "error number: ");
			am_eputs(inf->argv[1]);
			am_eputchar('\n');
			return (1);
		}
		inf->err_num = am_erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _this_is_cd - change the current directory
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _this_is_cd(info_t *inf)
{
	char *s, *dr, buffer[1024];
	int chret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>cwd fail EMSG here<<\n");
	if (!inf->argv[1])
	{
		dr = get_val_env(inf, "HOME=");
		if (!dr)
		{
			chret = chdir((dr = get_val_env(inf, "PWD=")) ? dr : "/");
		}
		else
		{
			chret = chdir(dr);
		}
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!get_val_env(inf, "OLDPW="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_val_env(inf, "OLDPW=")), _putchar('\n');
		chret = chdir((dr = get_val_env(inf, "OLDPW=")) ? dr : "/");
	}
	else
		chret = chdir(inf->argv[1]);
	if (chret == -1)
	{
		am_print_error(inf, "can't change dir to ");
		am_eputs(inf->argv[1]), am_eputchar('\n');
	}
	else
	{
		_rell_setenv(inf, "OLDPW", get_val_env(inf, "PWD="));
		_rell_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _shell_help - changes the current directory
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _shell_help(info_t *inf)
{
	char **rarray;

	_puts("help call works. function not implemented yet\n");
	rarray = inf->argv;
	if (0)
	{
		_puts(*rarray);
	}
	return (0);
}

