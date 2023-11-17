#include "consoleShell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void error_output(char *char_coll)
{
	int x = 0;

	if (!char_coll)
		return;
	while (char_coll[x] != '\0')
	{
		put_error_char(char_coll[x]);
		x++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_error_char(char chr)
{
	static int x;
	static char buff[WRITE_CHUNK_SIZE];

	if (chr == FLUSH_THRESHOLD || x >= WRITE_CHUNK_SIZE)
	{
		write(2, buff, x);
		x = 0;
	}
	if (chr != FLUSH_THRESHOLD)
		buff[x++] = chr;
	return (x);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_descriptor(char ch, int fd)
{
	static int x;
	static char buff[WRITE_CHUNK_SIZE];

	if (ch == FLUSH_THRESHOLD || x >= WRITE_CHUNK_SIZE)
	{
		write(fd, buff, x);
		x = 0;
	}
	if (ch != FLUSH_THRESHOLD)
		buff[x++] = ch;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int write_str_to_fd(char *char_coll, int fdis)
{
	int x = 0;

	if (!char_coll)
		return (0);
	while (*char_coll)
	{
		x += write_descriptor(*char_coll++, fdis);
	}
	return (x);
}
