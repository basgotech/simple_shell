#include "consoleShell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
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
	else if (buffer[x] == ';') /* found end of this command */
	{
		buffer[x] = 0; /* replace semicolon with null */
		data_t->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*st = x;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
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
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
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
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
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
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int modify_string(char **tosub, char *modif)
{
	free(*tosub);
	*tosub = modif;
	return (1);
}
