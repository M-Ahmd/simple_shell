#include "header.h"

/**
 * am_hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int am_hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		rm_inf(info);
		if (inter(info))
			_puts("$ ");
		_putchar(BUF_FLUSH);
		r = am_get_inp(info);
		if (r != -1)
		{
			put_inf(info, av);
			builtin_ret = am_find_builtin(info);
			if (builtin_ret == -1)
				am_find_cmd(info);
		}
		else if (inter(info))
			_putchar('\n');
		freeStr_inf(info, 0);
	}
	am_write_history(info);
	freeStr_inf(info, 1);
	if (!inter(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * am_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int am_find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shell_exit},
		{"env", _prt_env},
		{"help", _shell_help},
		{"history", _this_is_hist},
		{"setenv", _rm_setv},
		{"unsetenv", _init_setv},
		{"cd", _this_is_cd},
		{"alias", _my_ali_str},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * am_find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void am_find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!s_dlm(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = am_find_path(info, get_val_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		am_fork_cmd(info);
	}
	else
	{
		if ((inter(info) || get_val_env(info, "PATH=")
			|| info->argv[0][0] == '/') && am_is_cmd(info, info->argv[0]))
			am_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			am_print_error(info, "not found\n");
		}
	}
}

/**
 * am_fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void am_fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env_str(info)) == -1)
		{
			freeStr_inf(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				am_print_error(info, "Permission denied\n");
		}
	}
}
