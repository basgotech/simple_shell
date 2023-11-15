#include "header_files.h"

/**
 * get_builtin - builtin that pass the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", environment },
		{ "exit", end_Shell },
		{ "setenv", _set_env },
		{ "unsetenv", _un_set_env },
		{ "cd", cd_changer },
		{ "help", fetchHelp },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (string_Comparator(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
