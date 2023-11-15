#include "header_files.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *clone_Data(char *name, char *val)
{
	char *fresh;
	int name_len, value_len, length;

	name_len = str_Length(name);
	value_len = str_Length(val);
	length = name_len + value_len + 2;
	fresh = malloc(sizeof(char) * (length));
	str_Copy(fresh, name);
	str_Merge(fresh, "=");
	str_Merge(fresh, val);
	str_Merge(fresh, "\0");

	return (fresh);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void configure_Env(char *name, char *val, data_shell *data_shell)
{
	int x;
	char *env_local, *iden_name;

	for (x = 0; data_shell->_environ[x]; x++)
	{
		env_local = clone_String(data_shell->_environ[x]);
		iden_name = tokenize_String(env_local, "=");
		if (string_Comparator(iden_name, name) == 0)
		{
			free(data_shell->_environ[x]);
			data_shell->_environ[x] = clone_Data(iden_name, val);
			free(env_local);
			return;
		}
		free(env_local);
	}

	data_shell->_environ = reallocateDPtr(data_shell->_environ, x, sizeof(char *) * (x + 2));
	data_shell->_environ[x] = clone_Data(name, val);
	data_shell->_environ[x + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _set_env(data_shell *data_shell)
{

	if (data_shell->args[1] == NULL || data_shell->args[2] == NULL)
	{
		fetchError(data_shell, -1);
		return (1);
	}

	configure_Env(data_shell->args[1], data_shell->args[2], data_shell);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _un_set_env(data_shell *data_shell)
{
	char **adjustEnvAllocation;
	char *env_mem, *iden_env;
	int x, y, z;

	if (data_shell->args[1] == NULL)
	{
		fetchError(data_shell, -1);
		return (1);
	}
	z = -1;
	for (x = 0; data_shell->_environ[x]; x++)
	{
		env_mem = clone_String(data_shell->_environ[x]);
		iden_env = tokenize_String(env_mem, "=");
		if (string_Comparator(iden_env, data_shell->args[1]) == 0)
		{
			z = x;
		}
		free(env_mem);
	}
	if (z == -1)
	{
		fetchError(data_shell, -1);
		return (1);
	}
	adjustEnvAllocation = malloc(sizeof(char *) * (x));
	for (x = y = 0; data_shell->_environ[x]; x++)
	{
		if (x != z)
		{
			adjustEnvAllocation[y] = data_shell->_environ[x];
			y++;
		}
	}
	adjustEnvAllocation[y] = NULL;
	free(data_shell->_environ[z]);
	free(data_shell->_environ);
	data_shell->_environ = adjustEnvAllocation;
	return (1);
}
