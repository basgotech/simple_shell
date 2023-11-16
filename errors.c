#include "consoleShell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void error_output(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		put_error_char(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_error_char(char c)
{
	static int i;
	static char buf[WRITE_CHUNK_SIZE];

	if (c == FLUSH_THRESHOLD || i >= WRITE_CHUNK_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_THRESHOLD)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_descriptor(char c, int fd)
{
	static int i;
	static char buf[WRITE_CHUNK_SIZE];

	if (c == FLUSH_THRESHOLD || i >= WRITE_CHUNK_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_THRESHOLD)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int write_str_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_descriptor(*str++, fd);
	}
	return (i);
}
