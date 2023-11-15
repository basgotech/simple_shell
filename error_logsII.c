#include "header_files.h"

/**
 * error_env - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */
char *envIssue(data_shell *datashell)
{
	int len;
	char *err;
	char *str_err;
	char *show_msg;

	str_err = int_To_Str(datashell->counter);
	show_msg = ": Unable to add/remove from environment\n";
	len = str_Length(datashell->av[0]) + str_Length(str_err);
	len += str_Length(datashell->args[0]) + str_Length(show_msg) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str_err);
		return (NULL);
	}

	str_Copy(err, datashell->av[0]);
	str_Merge(err, ": ");
	str_Merge(err, str_err);
	str_Merge(err, ": ");
	str_Merge(err, datashell->args[0]);
	str_Merge(err, show_msg);
	str_Merge(err, "\0");
	free(str_err);

	return (err);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *pathIssue126(data_shell *datashell)
{
	int length;
	char *str_err;
	char *err;

	str_err = int_To_Str(datashell->counter);
	length = str_Length(datashell->av[0]) + str_Length(str_err);
	length += str_Length(datashell->args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(str_err);
		return (NULL);
	}
	str_Copy(err, datashell->av[0]);
	str_Merge(err, ": ");
	str_Merge(err, str_err);
	str_Merge(err, ": ");
	str_Merge(err, datashell->args[0]);
	str_Merge(err, ": Permission denied\n");
	str_Merge(err, "\0");
	free(str_err);
	return (err);
}
