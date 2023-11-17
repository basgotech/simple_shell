#include "consoleShell.h"

/**
 * get_env_data - returns the string.
 * @data_t: Structure containing potential
 * Return: Always 0.
 */
char **get_env_data(info_t *data_t)
{
	if (!data_t->environ || data_t->env_changed)
	{
		data_t->environ = list_stringify(data_t->env);
		data_t->env_changed = 0;
	}

	return (data_t->environ);
}

/**
 * _cus_unsetenv - Remove an environment variable
 * @data_t: Structure containing potential arguments.
 * @var_inf: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _cus_unsetenv(info_t *data_t, char *var_inf)
{
	list_t *end_st = data_t->env;
	size_t i = 0;
	char *p;

	if (!end_st || !var_inf)
		return (0);

	while (end_st)
	{
		p = is_prefixed(end_st->str, var_inf);
		if (p && *p == '=')
		{
			data_t->env_changed = erase_node_at_position(&(data_t->env), i);
			i = 0;
			end_st = data_t->env;
			continue;
		}
		end_st = end_st->next;
		i++;
	}
	return (data_t->env_changed);
}

/**
 * _cus_setenv - Initialize a new enviro
 * @data_t: Structure containing potenti
 * @var_inf: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _cus_setenv(info_t *data_t, char *var_inf, char *val)
{
	char *buffer_ = NULL;
	list_t *end_st;
	char *ptr;

	if (!var_inf || !val)
		return (0);

	buffer_ = malloc(string_size(var_inf) + string_size(val) + 2);
	if (!buffer_)
		return (1);
	str_clone(buffer_, var_inf);
	join_strings(buffer_, "=");
	join_strings(buffer_, val);
	end_st = data_t->env;
	while (end_st)
	{
		ptr = is_prefixed(end_st->str, var_inf);
		if (ptr && *ptr == '=')
		{
			free(end_st->str);
			end_st->str = buffer_;
			data_t->env_changed = 1;
			return (0);
		}
		end_st = end_st->next;
	}
	generate_node_end(&(data_t->env), buffer_, 0);
	free(buffer_);
	data_t->env_changed = 1;
	return (0);
}
