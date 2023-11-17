#include "consoleShell.h"

/**
 * history_file_query - gets the history file of shell
 * @data_: parameter struct
 * Return: allocated string containg history file
 */

char *history_file_query(info_t *data_)
{
	char *d_buf, *directory;

	directory = env_query(data_, "HOME=");
	if (!directory)
		return (NULL);
	d_buf = malloc(sizeof(char) * (string_size(directory) + string_size(LOG_FILE) + 2));
	if (!d_buf)
		return (NULL);
	d_buf[0] = 0;
	str_clone(d_buf, directory);
	join_strings(d_buf, "/");
	join_strings(d_buf, LOG_FILE);
	return (d_buf);
}

/**
 * save_history - creates a file
 * @data_: the parameter struct
 * Return: 1 on success, else -1
 */
int save_history(info_t *data_)
{
	ssize_t file_dis;
	char *fname = history_file_query(data_);
	list_t *estation = NULL;

	if (!fname)
		return (-1);

	file_dis = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (file_dis == -1)
		return (-1);
	for (estation = data_->history; estation; estation = estation->next)
	{
		write_str_to_fd(estation->str, file_dis);
		write_descriptor('\n', file_dis);
	}
	write_descriptor(FLUSH_THRESHOLD, file_dis);
	close(file_dis);
	return (1);
}

/**
 * get_history - reads history from file shell
 * @data_: the parameter struct
 * Return: count on success, 0 otherwise
 */
int get_history(info_t *data_)
{
	int x, end = 0, get_len = 0;
	ssize_t f_dis, dis_len, f_size = 0;
	struct stat xy;
	char *buffer = NULL, *fname = history_file_query(data_);

	if (!fname)
		return (0);

	f_dis = open(fname, O_RDONLY);
	free(fname);
	if (f_dis == -1)
		return (0);
	if (!fstat(f_dis, &xy))
		f_size = xy.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	dis_len = read(f_dis, buffer, f_size);
	buffer[f_size] = 0;
	if (dis_len <= 0)
		return (free(buffer), 0);
	close(f_dis);
	for (x = 0; x < f_size; x++)
		if (buffer[x] == '\n')
		{
			buffer[x] = 0;
			construct_history_list(data_, buffer + end, get_len++);
			end = x + 1;
		}
	if (end != x)
		construct_history_list(data_, buffer + end, get_len++);
	free(buffer);
	data_->histcount = get_len;
	while (data_->histcount-- >= MAX_LOG)
		erase_node_at_position(&(data_->history), 0);
	modify_history_order(data_);
	return (data_->histcount);
}

/**
 * construct_history_list - adds entry to a history
 * @data_: Structure containing in
 * @buffer: buffer
 * @get_len: the history linecount, histcount
 *
 * Return: Always 0
 */
int construct_history_list(info_t *data_, char *buffer, int get_len)
{
	list_t *end_st = NULL;

	if (data_->history)
		end_st = data_->history;
	generate_node_end(&end_st, buffer, get_len);

	if (!data_->history)
		data_->history = end_st;
	return (0);
}

/**
 * modify_history_order - renumbers the history
 * @data_t: Structure containing
 * Return: the new histcount
 */
int modify_history_order(info_t *data_t)
{
	list_t *end_st = data_t->history;
	int x = 0;

	while (end_st)
	{
		end_st->num = x++;
		end_st = end_st->next;
	}
	return (data_t->histcount = x);
}
