#include "consoleShell.h"

/**
 * real_time_com - returns true
 * @data_: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int real_time_com(info_t *data_)
{
	return (isatty(STDIN_FILENO) && data_->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @ch: the char to check
 * @delm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char ch, char *delm)
{
	while (*delm)
		if (*delm++ == ch)
			return (1);
	return (0);
}

/**
 *checkalpha - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int checkalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string
 */

int _atoi(char *str)
{
	int x, si = 1, fl = 0, dis;
	unsigned int result = 0;

	for (x = 0;  str[x] != '\0' && fl != 2; x++)
	{
		if (str[x] == '-')
			si *= -1;

		if (str[x] >= '0' && str[x] <= '9')
		{
			fl = 1;
			result *= 10;
			result += (str[x] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (si == -1)
		dis = -result;
	else
		dis = result;

	return (dis);
}
