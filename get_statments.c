#include "header_files.h"

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void acquire_Line(char **acq_line, size_t *num, char *buf, size_t y)
{
	if (*acq_line == NULL)
	{
		if  (y > BUFSIZE)
			*num = y;

		else
			*num = BUFSIZE;
		*acq_line = buf;
	}
	else if (*num < y)
	{
		if (y > BUFSIZE)
			*num = y;
		else
			*num = BUFSIZE;
		*acq_line = buf;
	}
	else
	{
		str_Copy(*acq_line, buf);
		free(buf);
	}
}
/**
 * get_line - Read input from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t fetch_Line(char **fe_line, size_t *num, FILE *io)
{
	int y;
	static ssize_t dataIN;
	ssize_t r_val;
	char *buf;
	char x = 'z';

	if (dataIN == 0)
		fflush(io);
	else
		return (-1);
	dataIN = 0;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (buf == 0)
		return (-1);
	while (x != '\n')
	{
		y = read(STDIN_FILENO, &x, 1);
		if (y == -1 || (y == 0 && dataIN == 0))
		{
			free(buf);
			return (-1);
		}
		if (y == 0 && dataIN != 0)
		{
			dataIN++;
			break;
		}
		if (dataIN >= BUFSIZE)
			buf = reallocate_Memory(buf, dataIN, dataIN + 1);
		buf[dataIN] = x;
		dataIN++;
	}
	buf[dataIN] = '\0';
	acquire_Line(fe_line, num, buf, dataIN);
	r_val = dataIN;
	if (y != 0)
		dataIN = 0;
	return (r_val);
}
