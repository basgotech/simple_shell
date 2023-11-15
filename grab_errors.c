#include "header_files.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int fetchError(data_shell *datashell, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = envIssue(datashell);
		break;
	case 126:
		err = pathIssue126(datashell);
		break;
	case 127:
		err = missing_Error(datashell);
		break;
	case 2:
		if (string_Comparator("exit", datashell->args[0]) == 0)
			err = terminateShellOnError(datashell);
		else if (string_Comparator("cd", datashell->args[0]) == 0)
			err = getAndHandleCdError(datashell);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, str_Length(err));
		free(err);
	}

	datashell->status = eval;
	return (eval);
}
