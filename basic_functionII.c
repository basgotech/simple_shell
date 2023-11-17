#include "consoleShell.h"

/**
 * _custom_history - displays the history.
 * @data_: Structure containing potenti
 *  Return: Always 0
 */
int _custom_history(info_t *data_)
{
	show_string_list(data_->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @data_: parameter struct
 * @seq_char: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *data_, char *seq_char)
{
	char *x, y;
	int fetch;

	x = search_for_char(seq_char, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	fetch = erase_node_at_position(&(data_->alias),
		retrieve_node_index(data_->alias, node_prefix_match(data_->alias, seq_char, -1)));
	*x = y;
	return (fetch);
}

/**
 * set_alias - sets alias to string
 * @data_: parameter struct
 * @seq_char: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *data_, char *seq_char)
{
	char *x;

	x = search_for_char(seq_char, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(data_, seq_char));

	unset_alias(data_, seq_char);
	return (generate_node_end(&(data_->alias), seq_char, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @end_st: the alias node
 * Return: Always 0 on success
 */
int print_alias(list_t *end_st)
{
	char *x = NULL, *a = NULL;

	if (end_st)
	{
		x = search_for_char(end_st->str, '=');
		for (a = end_st->str; a <= x; a++)
			_putchar(*a);
		_putchar('\'');
		display_string(x + 1);
		display_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * _custom_alias - mimics the alias
 * @data_: Structure containing potential
 *  Return: Always 0
 */
int _custom_alias(info_t *data_)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (data_->argc == 1)
	{
		node = data_->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data_->argv[i]; i++)
	{
		p = search_for_char(data_->argv[i], '=');
		if (p)
			set_alias(data_, data_->argv[i]);
		else
			print_alias(node_prefix_match(data_->alias, data_->argv[i], '='));
	}

	return (0);
}
