#include "consoleShell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _custom_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _safe_str_to_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			show_error_message(info, "Illegal number: ");
			error_output(info->argv[1]);
			put_error_char('\n');
			return (1);
		}
		info->err_num = _safe_str_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _custom_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		display_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = env_query(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = env_query(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_equals(info->argv[1], "-") == 0)
	{
		if (!env_query(info, "OLDPWD="))
		{
			display_string(s);
			_putchar('\n');
			return (1);
		}
		display_string(env_query(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = env_query(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		show_error_message(info, "can't cd to ");
		error_output(info->argv[1]), put_error_char('\n');
	}
	else
	{
		_cus_setenv(info, "OLDPWD", env_query(info, "PWD="));
		_cus_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _custom_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	display_string("help call works. Function not yet implemented \n");
	if (0)
		display_string(*arg_array); /* temp att_unused workaround */
	return (0);
}
