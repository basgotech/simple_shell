#include "header_files.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *uncaptioned(char *get)
{
	int y, until;

	until = 0;
	for (y = 0; get[y]; y++)
	{
		if (get[y] == '#')
		{
			if (y == 0)
			{
				free(get);
				return (NULL);
			}

			if (get[y - 1] == ' ' || get[y - 1] == '\t' || get[y- 1] == ';')
				until = y;
		}
	}

	if (until != 0)
	{
		get = reallocate_Memory(get, y, until + 1);
		get[until] = '\0';
	}

	return (get);
}

/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_iteration(data_shell *data_shell)
{
	int iteration, endOfFileInput;
	char *dataIn;

	iteration = 1;
	while (iteration == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		dataIn = read_Input_Line(&endOfFileInput);
		if (endOfFileInput != -1)
		{
			dataIn = uncaptioned(dataIn);
			if (dataIn == NULL)
				continue;

			if (validate_Syntax_Error(data_shell, dataIn) == 1)
			{
				data_shell->status = 2;
				free(dataIn);
				continue;
			}
			dataIn = changedVar(dataIn, data_shell);
			iteration = separatedCom(data_shell, dataIn);
			data_shell->counter += 1;
			free(dataIn);
		}
		else
		{
			iteration = 0;
			free(dataIn);
		}
	}
}
