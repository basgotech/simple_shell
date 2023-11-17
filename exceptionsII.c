#include "consoleShell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _safe_str_to_int(char *str_con)
{
	int x = 0;
	unsigned long int res = 0;

	if (*str_con == '+')
		str_con++;  /* TODO: why does this make main return 255? */
	for (x = 0;  str_con[x] != '\0'; x++)
	{
		if (str_con[x] >= '0' && str_con[x] <= '9')
		{
			res *= 10;
			res += (str_con[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void show_error_message(info_t *data_t, char *str_err_con)
{
	error_output(data_t->fname);
	error_output(": ");
	print_debug_info(data_t->line_count, STDERR_FILENO);
	error_output(": ");
	error_output(data_t->argv[0]);
	error_output(": ");
	error_output(str_err_con);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_debug_info(int grab, int fdis)
{
	int (*__putchar)(char) = _putchar;
	int x, incr = 0;
	unsigned int un, pwdd;

	if (fdis == STDERR_FILENO)
		__putchar = put_error_char;
	if (grab < 0)
	{
		un = -grab;
		__putchar('-');
		incr++;
	}
	else
		un = grab;
	pwdd = un;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (un / x)
		{
			__putchar('0' + pwdd / x);
			incr++;
		}
		pwdd %= x;
	}
	__putchar('0' + pwdd);
	incr++;

	return (incr);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_numeric(long int number, int roott, int isf)
{
	static char *seq;
	static char buf[50];
	char si = 0;
	char *point;
	unsigned long num = number;

	if (!(isf & TO_UNSIGNED) && number < 0)
	{
		num = -number;
		si = '-';

	}
	seq = isf & TO_LOW ? "0123456789abcdef" : "0123456789ABCDEF";
	point = &buf[49];
	*point = '\0';

	do	{
		*--point = seq[num % roott];
		num /= roott;
	} while (num != 0);

	if (si)
		*--point = si;
	return (point);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void eliminate_comments(char *buffer)
{
	int x;

	for (x= 0; buffer[x] != '\0'; x++)
		if (buffer[x] == '#' && (!x || buffer[x - 1] == ' '))
		{
			buffer[x] = '\0';
			break;
		}
}
