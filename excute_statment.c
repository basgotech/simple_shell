#include "header_files.h"

/**
 * exec_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int run_Line(data_shell *datashell)
{
	int (*builtin)(data_shell *datash);

	if (datashell->args[0] == NULL)
		return (1);

	builtin = get_builtin(datashell->args[0]);

	if (builtin != NULL)
		return (builtin(datashell));

	return (invoke_Command(datashell));
}
