#include "header_files.h"


/**
 * is_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int verify_Current_Location(char *path, int *x)
{
	if (path[*x] == ':')
		return (1);

	while (path[*x] != ':' && path[*x])
	{
		*x += 1;
	}

	if (path[*x])
		*x += 1;

	return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *which_Executable(char *cmd, char **env)
{
	char *route, *ptr_route, *token_route, *directory;
	int length_dir, length_cmd, x;
	struct stat status;

	route = get_Env_Value("PATH", env);
	if (route)
	{
		ptr_route = clone_String(route);
		length_cmd = str_Length(cmd);
		token_route = tokenize_String(ptr_route, ":");
		x = 0;
		while (token_route != NULL)
		{
			if (verify_Current_Location(route, &x))
				if (stat(cmd, &status) == 0)
					return (cmd);
			length_dir = str_Length(token_route);
			directory = malloc(length_dir + length_cmd + 2);
			str_Copy(directory, token_route);
			str_Merge(directory, "/");
			str_Merge(directory, cmd);
			str_Merge(directory, "\0");
			if (stat(directory, &status) == 0)
			{
				free(ptr_route);
				return (directory);
			}
			free(directory);
			token_route = tokenize_String(NULL, ":");
		}
		free(ptr_route);
		if (stat(cmd, &status) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &status) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_Runnable(data_shell *data_shell)
{
	struct stat status;
	int x;
	char *dataIn;

	dataIn = data_shell->args[0];
	for (x = 0; dataIn[x]; x++)
	{
		if (dataIn[x] == '.')
		{
			if (dataIn[x + 1] == '.')
				return (0);
			if (dataIn[x + 1] == '/')
				continue;
			else
				break;
		}
		else if (dataIn[x] == '/' && x != 0)
		{
			if (dataIn[x + 1] == '.')
				continue;
			x++;
			break;
		}
		else
			break;
	}
	if (x == 0)
		return (0);

	if (stat(dataIn + x, &status) == 0)
	{
		return (x);
	}
	fetchError(data_shell, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int validate_cmd_Error(char *directory, data_shell *data_shell)
{
	if (directory == NULL)
	{
		fetchError(data_shell, 127);
		return (1);
	}

	if (string_Comparator(data_shell->args[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			fetchError(data_shell, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(data_shell->args[0], X_OK) == -1)
		{
			fetchError(data_shell, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int invoke_Command(data_shell *data_shell)
{
	pid_t p;
	pid_t pp;
	int condition;
	int run;
	char *directory;
	(void) pp;

	run = is_Runnable(data_shell);
	if (run == -1)
		return (1);
	if (run == 0)
	{
		directory = which_Executable(data_shell->args[0], data_shell->_environ);
		if (validate_cmd_Error(directory, data_shell) == 1)
			return (1);
	}

	p = fork();
	if (p == 0)
	{
		if (run == 0)
			directory = which_Executable(data_shell->args[0], data_shell->_environ);
		else
			directory = data_shell->args[0];
		execve(directory + run, data_shell->args, data_shell->_environ);
	}
	else if (p < 0)
	{
		perror(data_shell->av[0]);
		return (1);
	}
	else
	{
		do {
			pp = waitpid(p, &condition, WUNTRACED);
		} while (!WIFEXITED(condition) && !WIFSIGNALED(condition));
	}

	data_shell->status = condition / 256;
	return (1);
}
