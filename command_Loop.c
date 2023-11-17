#include "consoleShell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hShell(info_t *details, char **arg_v)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		reset_info(details);
		if (real_time_com(details))
			display_string("$ ");
		put_error_char(FLUSH_THRESHOLD);
		r = fetch_input(details);
		if (r != -1)
		{
			initialize_info(details, arg_v);
			builtin_ret = search_builtin(details);
			if (builtin_ret == -1)
				search_command(details);
		}
		else if (real_time_com(details))
			_putchar('\n');
		deallocate_info(details, 0);
	}
	save_history(details);
	deallocate_info(details, 1);
	if (!real_time_com(details) && details->status)
		exit(details->status);
	if (builtin_ret == -2)
	{
		if (details->err_num == -1)
			exit(details->status);
		exit(details->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int search_builtin(info_t *data_t)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _custom_exit},
		{"env", retrieve_custom_env},
		{"help", _custom_help},
		{"cd", _custom_cd},
		{"alias", _custom_alias},
		{"history", _custom_history},
		{"setenv", configure_custom_env},
		{"unsetenv", clear_custom_env},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (string_equals(data_t->argv[0], builtintbl[x].type) == 0)
		{
			data_t->line_count++;
			built_in_ret = builtintbl[x].func(data_t);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void search_command(info_t *data_t)
{
	char *path = NULL;
	int i, k;

	data_t->path = data_t->argv[0];
	if (data_t->linecount_flag == 1)
	{
		data_t->line_count++;
		data_t->linecount_flag = 0;
	}
	for (i = 0, k = 0; data_t->arg[i]; i++)
		if (!is_delim(data_t->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = locate_dir(data_t, env_query(data_t, "PATH="), data_t->argv[0]);
	if (path)
	{
		data_t->path = path;
		launchCmd(data_t);
	}
	else
	{
		if ((real_time_com(data_t) || env_query(data_t, "PATH=")
			|| data_t->argv[0][0] == '/') && validate_cmd(data_t, data_t->argv[0]))
			launchCmd(data_t);
		else if (*(data_t->arg) != '\n')
		{
			data_t->status = 127;
			show_error_message(data_t, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void launchCmd(info_t *data_t)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data_t->path, data_t->argv, get_env_data(data_t)) == -1)
		{
			deallocate_info(data_t, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data_t->status));
		if (WIFEXITED(data_t->status))
		{
			data_t->status = WEXITSTATUS(data_t->status);
			if (data_t->status == 126)
				show_error_message(data_t, "Permission denied\n");
		}
	}
}
