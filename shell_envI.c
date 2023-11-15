#include "header_files.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *get_Env_Value(const char *name, char **env)
{
	char *pointer_env;
	int x, mov;

	/* Initialize ptr_env value */
	pointer_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (x = 0; env[x]; x++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(env[x], name);
		if (mov)
		{
			pointer_env = env[x];
			break;
		}
	}

	return (pointer_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int environment(data_shell *data_shell)
{
	int x, y;

	for (x = 0; data_shell->_environ[x]; x++)
	{

		for (y = 0; data_shell->_environ[x][y]; y++)
			;

		write(STDOUT_FILENO, data_shell->_environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_shell->status = 0;

	return (1);
}
