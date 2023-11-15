#include "header_files.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int recurring_Char(char *dataIn, int y)
{
	if (*(dataIn - 1) == *dataIn)
		return (recurring_Char(dataIn - 1, y + 1));

	return (y);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int Separator_Error(char *dataIn, int y, char end)
{
	int total;

	total = 0;
	if (*dataIn == '\0')
		return (0);

	if (*dataIn == ' ' || *dataIn == '\t')
		return (Separator_Error(dataIn + 1, y + 1, end));

	if (*dataIn == ';')
		if (end == '|' || end == '&' || end == ';')
			return (y);

	if (*dataIn == '|')
	{
		if (end == ';' || end == '&')
			return (y);

		if (end == '|')
		{
			total = recurring_Char(dataIn, 0);
			if (total == 0 || total > 1)
				return (y);
		}
	}

	if (*dataIn == '&')
	{
		if (end == ';' || end == '|')
			return (y);

		if (end == '&')
		{
			total = recurring_Char(dataIn, 0);
			if (total == 0 || total > 1)
				return (y);
		}
	}

	return (Separator_Error(dataIn + 1, y + 1, *dataIn));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int primary_Char(char *dataIn, int *y)
{

	for (*y = 0; dataIn[*y]; *y += 1)
	{
		if (dataIn[*y] == ' ' || dataIn[*y] == '\t')
			continue;

		if (dataIn[*y] == ';' || dataIn[*y] == '|' || dataIn[*y] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void show_Syntax_error(data_shell *datashell, char *dataIn, int y, int istrue)
{
	char *disrr1, *diserr2, *diserr3, *get_error, *total;
	int length;

	if (dataIn[y] == ';')
	{
		if (istrue == 0)
			disrr1 = (dataIn[y + 1] == ';' ? ";;" : ";");
		else
			disrr1 = (dataIn[y - 1] == ';' ? ";;" : ";");
	}

	if (dataIn[y] == '|')
		disrr1 = (dataIn[y + 1] == '|' ? "||" : "|");

	if (dataIn[y] == '&')
		disrr1 = (dataIn[y + 1] == '&' ? "&&" : "&");

	diserr2 = ": Syntax error: \"";
	diserr3 = "\" unexpected\n";
	total = int_To_Str(datashell->counter);
	length = str_Length(datashell->av[0]) + str_Length(total);
	length += str_Length(disrr1) + str_Length(diserr2) + str_Length(diserr3) + 2;

	get_error = malloc(sizeof(char) * (length + 1));
	if (get_error == 0)
	{
		free(total);
		return;
	}
	str_Copy(get_error, datashell->av[0]);
	str_Merge(get_error, ": ");
	str_Merge(get_error, total);
	str_Merge(get_error, diserr2);
	str_Merge(get_error, disrr1);
	str_Merge(get_error, diserr3);
	str_Merge(get_error, "\0");

	write(STDERR_FILENO, get_error, length);
	free(get_error);
	free(total);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int validate_Syntax_Error(data_shell *datash, char *input)
{
	int start = 0;
	int ch = 0;
	int y = 0;

	ch = primary_Char(input, &start);
	if (ch == -1)
	{
		show_Syntax_error(datash, input, start, 0);
		return (1);
	}

	y = Separator_Error(input + start, 0, *(input + start));
	if (y != 0)
	{
		show_Syntax_error(datash, input, start + y, 1);
		return (1);
	}

	return (0);
}
