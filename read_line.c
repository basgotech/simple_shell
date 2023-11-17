#include "consoleShell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *data_t, char **buffer, size_t *get_len)
{
	ssize_t brr = 0;
	size_t get_lenpp = 0;

	if (!*get_len) 
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_ctrl_d);
#if USE_GETLINE
		brr = getline(buffer, &get_lenpp, stdin);
#else
		brr = _getline(data_t, buffer, &get_lenpp);
#endif
		if (brr > 0)
		{
			if ((*buffer)[brr - 1] == '\n')
			{
				(*buffer)[brr - 1] = '\0'; 
				brr--;
			}
			data_t->linecount_flag = 1;
			eliminate_comments(*buffer);
			construct_history_list(data_t, *buffer, data_t->histcount++);
			
			{
				*get_len = brr;
				data_t->cmd_buf = buffer;
			}
		}
	}
	return (brr);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t fetch_input(info_t *data_)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t x, y, get_len;
	ssize_t rr = 0;
	char **buffer_pa = &(data_->arg), *ptrr;

	_putchar(FLUSH_THRESHOLD);
	rr= input_buf(data_, &buffer, &get_len);
	if (rr == -1) /* EOF */
		return (-1);
	if (get_len)	/* we have commands left in the chain buffer */
	{
		y = x; /* init new iterator to current buf position */
		ptrr= buffer + x; /* get pointer for return */

		assure_verification(data_, buffer, &y, x, get_len);
		while (y< get_len) /* iterate to semicolon or end */
		{
			if (sequence_verification(data_, buffer, &y))
				break;
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= get_len) /* reached end of buffer? */
		{
			x = get_len = 0; /* reset position and length */
			data_->cmd_buf_type = CMD_NORMALIZED;
		}

		*buffer_pa = ptrr; /* pass back pointer to current command position */
		return (string_size(ptrr)); /* return length of current command */
	}

	*buffer_pa = buffer; /* else not a chain, pass back buffer from _getline() */
	return (rr); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *data_, char *buff, size_t *x)
{
	ssize_t rg = 0;

	if (*x)
		return (0);
	rg = read(data_->readfd, buff, READ_CHUNK_SIZE);
	if (rg >= 0)
		*x = rg;
	return (rg);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *data_, char **point, size_t *get_len)
{
	static char buff[READ_CHUNK_SIZE];
	static size_t x, lenn;
	size_t kk;
	ssize_t rr = 0, ss = 0;
	char *pp = NULL, *new_p = NULL, *ch;

	pp = *point;
	if (pp && get_len)
		ss = *get_len;
	if (x == lenn)
		x = lenn = 0;

	rr = read_buf(data_, buff, &lenn);
	if (rr == -1 || (rr == 0 && lenn == 0))
		return (-1);

	ch = search_for_char(buff + x, '\n');
	kk = ch ? 1 + (unsigned int)(ch - buff) : lenn;
	new_p = reallocate_memory(pp, ss, ss ? ss + kk : kk + 1);
	if (!new_p)
		return (pp ? free(pp), -1 : -1);

	if (ss)
		substring_conca(new_p, buff + x, kk - x);
	else
		str_sub_copy(new_p, buff + x, kk - x + 1);

	ss += kk - x;
	x = kk;
	pp= new_p;

	if (get_len)
		*get_len = ss;
	*point = pp;
	return (ss);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_ctrl_d(__attribute__((unused))int sig_num)
{
	display_string("\n");
	display_string("$ ");
	_putchar(FLUSH_THRESHOLD);
}
