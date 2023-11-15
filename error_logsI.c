#include "header_files.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *concatenateCd(data_shell *data_shell, char *msg, char *error, char *ver_str)
{
	char *forbiden_flag;

	str_Copy(error, data_shell->av[0]);
	str_Merge(error, ": ");
	str_Merge(error, ver_str);
	str_Merge(error, ": ");
	str_Merge(error, data_shell->args[0]);
	str_Merge(error, msg);
	if (data_shell->args[1][0] == '-')
	{
		forbiden_flag = malloc(3);
		forbiden_flag[0] = '-';
		forbiden_flag[1] = data_shell->args[1][1];
		forbiden_flag[2] = '\0';
		str_Merge(error, forbiden_flag);
		free(forbiden_flag);
	}
	else
	{
		str_Merge(error, data_shell->args[1]);
	}

	str_Merge(error, "\n");
	str_Merge(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *getAndHandleCdError(data_shell *data_shell)
{
	int len, length_iden;
	char *err, *verify_str, *show;

	verify_str = int_To_Str(data_shell->counter);
	if (data_shell->args[1][0] == '-')
	{
		show = ": Illegal option ";
		length_iden = 2;
	}
	else
	{
		show = ": can't cd to ";
		length_iden = str_Length(data_shell->args[1]);
	}

	len = str_Length(data_shell->av[0]) + str_Length(data_shell->args[0]);
	len += str_Length(verify_str) + str_Length(show) + length_iden + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(verify_str);
		return (NULL);
	}

	err = concatenateCd(data_shell, show, err, verify_str);

	free(verify_str);

	return (err);
}

/**
 * error_not_found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *missing_Error(data_shell *datashell)
{
	int len;
	char *err;
	char *str_err;

	str_err = int_To_Str(datashell->counter);
	len = str_Length(datashell->av[0]) + str_Length(str_err);
	len += str_Length(datashell->args[0]) + 16;
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
	str_Merge(err, ": not found\n");
	str_Merge(err, "\0");
	free(str_err);
	return (err);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *terminateShellOnError(data_shell *datashell)
{
	int len;
	char *err;
	char *str_err;

	str_err = int_To_Str(datashell->counter);
	len = str_Length(datashell->av[0]) + str_Length(str_err);
	len += str_Length(datashell->args[0]) + str_Length(datashell->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str_err);
		return (NULL);
	}
	str_Copy(err, datashell->av[0]);
	str_Merge(err, ": ");
	str_Merge(err, str_err);
	str_Merge(err, ": ");
	str_Merge(err, datashell->args[0]);
	str_Merge(err, ": Illegal number: ");
	str_Merge(err, datashell->args[1]);
	str_Merge(err, "\n\0");
	free(str_err);

	return (err);
}
