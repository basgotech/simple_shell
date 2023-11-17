#include "consoleShell.h"

/**
 * sequence_verification - test if current char
 * @data_t: the parameter struct
 * @buffer: the char buffer
 * @st: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int sequence_verification(info_t *data_t, char *buffer, size_t *st)
{
	size_t x = *st;

	if (buffer[x] == '|' && buffer[x + 1] == '|')
	{
		buffer[x] = 0;
		x++;
		data_t->cmd_buf_type = OR_GATE;
	}
	else if (buffer[x] == '&' && buffer[x + 1] == '&')
	{
		buffer[x] = 0;
		x++;
		data_t->cmd_buf_type = AND_GATE;
	}
	else if (buffer[x] == ';')
	{
		buffer[x] = 0;
		data_t->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*st = x;
	return (1);
}

/**
 * assure_verification - checks we should
 * @data_: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buf
 * @x: starting position in buf
 * @get_len: length of buf
 * Return: Void
 */
void assure_verification(info_t *data_, char *buffer, size_t *ptr, size_t x, size_t get_len)
{
	size_t y = *ptr;

	if (data_->cmd_buf_type == AND_GATE)
	{
		if (data_->status)
		{
			buffer[x] = 0;
			y = get_len;
		}
	}
	if (data_->cmd_buf_type == OR_GATE)
	{
		if (!data_->status)
		{
			buffer[x] = 0;
			y = get_len;
		}
	}

	*ptr = y;
}

/**
 * modify_alias - replaces an aliases
 * @data_: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int modify_alias(info_t *data_)
{
	int x;
	list_t *end_st;
	char *ptr;

	for (x = 0; x < 10; x++)
	{
		end_st = node_prefix_match(data_->alias, data_->argv[0], '=');
		if (!end_st)
			return (0);
		free(data_->argv[0]);
		ptr = search_for_char(end_st->str, '=');
		if (!ptr)
			return (0);
		ptr = string_duplicate(ptr + 1);
		if (!ptr)
			return (0);
		data_->argv[0] = ptr;
	}
	return (1);
}

/**
 * modify_vars - replaces vars in the tokenized string
 * @data_t: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int modify_vars(info_t *data_t)
{
	int x = 0;
	list_t *end_st;

	for (x = 0; data_t->argv[x]; x++)
	{
		if (data_t->argv[x][0] != '$' || !data_t->argv[x][1])
			continue;

		if (!string_equals(data_t->argv[x], "$?"))
		{
			modify_string(&(data_t->argv[x]),
				string_duplicate(convert_numeric(data_t->status, 10, 0)));
			continue;
		}
		if (!string_equals(data_t->argv[x], "$$"))
		{
			modify_string(&(data_t->argv[x]),
				string_duplicate(convert_numeric(getpid(), 10, 0)));
			continue;
		}
		end_st = node_prefix_match(data_t->env, &data_t->argv[x][1], '=');
		if (end_st)
		{
			modify_string(&(data_t->argv[x]),
				string_duplicate(search_for_char(end_st->str, '=') + 1));
			continue;
		}
		modify_string(&data_t->argv[x], string_duplicate(""));

	}
	return (0);
}

/**
 * modify_string - replaces string
 * @tosub: address of old string
 * @modif: new string
 * Return: 1 if replaced, 0 otherwise
 */
int modify_string(char **tosub, char *modif)
{
	free(*tosub);
	*tosub = modif;
	return (1);
}
