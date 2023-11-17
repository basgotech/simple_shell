#include "consoleShell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _custom_exit(info_t *data_env)
{
	int isitexit;

	if (data_env->argv[1])
	{
		isitexit = _safe_str_to_int(data_env->argv[1]);
		if (isitexit == -1)
		{
			data_env->status = 2;
			show_error_message(data_env, "Illegal number: ");
			error_output(data_env->argv[1]);
			put_error_char('\n');
			return (1);
		}
		data_env->err_num = _safe_str_to_int(data_env->argv[1]);
		return (-2);
	}
	data_env->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _custom_cd(info_t *data_)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		display_string("TODO: >>getcwd failure emsg here<<\n");
	if (!data_->argv[1])
	{
		dir = env_query(data_, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = env_query(data_, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_equals(data_->argv[1], "-") == 0)
	{
		if (!env_query(data_, "OLDPWD="))
		{
			display_string(s);
			_putchar('\n');
			return (1);
		}
		display_string(env_query(data_, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = env_query(data_, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data_->argv[1]);
	if (chdir_ret == -1)
	{
		show_error_message(data_, "can't cd to ");
		error_output(data_->argv[1]), put_error_char('\n');
	}
	else
	{
		_cus_setenv(data_, "OLDPWD", env_query(data_, "PWD="));
		_cus_setenv(data_, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _custom_help(info_t *data_)
{
	char **arg_array;

	arg_array = data_->argv;
	display_string("help call works. Function not yet implemented \n");
	if (0)
		display_string(*arg_array); /* temp att_unused workaround */
	return (0);
}
