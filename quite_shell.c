#include "header_files.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int end_Shell(data_shell *data_shell)
{
	unsigned int status;
	int isnum;
	int len;
	int max_num;

	if (data_shell->args[1] != NULL)
	{
		status = parseToInt(data_shell->args[1]);
		isnum = is_Number(data_shell->args[1]);
		len = str_Length(data_shell->args[1]);
		max_num = status > (unsigned int)INT_MAX;
		if (!isnum || len > 10 || max_num)
		{
			fetchError(data_shell, 2);
			data_shell->status = 2;
			return (1);
		}
		data_shell->status = (status % 256);
	}
	return (0);
}
