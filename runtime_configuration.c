#include "consoleShell.h"

/**
 * retrieve_custom_env - prints the current environment.
 * @data_: Structure containing potential
 * Return: Always 0
 */
int retrieve_custom_env(info_t *data_)
{
	show_string_list(data_->env);
	return (0);
}

/**
 * env_query - gets the value of an environ variable
 * @data_: Structure containing potential arguments. Used to maintain
 * @nm: env var name
 * Return: the value
 */
char *env_query(info_t *data_, const char *nm)
{
	list_t *end_str = data_->env;
	char *ptr;

	while (end_str)
	{
		ptr = is_prefixed(end_str->str, nm);
		if (ptr && *ptr)
			return (ptr);
		end_str = end_str->next;
	}
	return (NULL);
}

/**
 * configure_custom_env - Initialize a new
 * @data_: Structure containing potential
 *  Return: Always 0
 */
int configure_custom_env(info_t *data_)
{
	if (data_->argc != 3)
	{
		error_output("Incorrect number of arguements\n");
		return (1);
	}
	if (_cus_setenv(data_, data_->argv[1], data_->argv[2]))
		return (0);
	return (1);
}

/**
 * clear_custom_env - Remove an environment variable
 * @data_: Structure containing potential
 *  Return: Always 0
 */
int clear_custom_env(info_t *data_)
{
	int x;

	if (data_->argc == 1)
	{
		error_output("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= data_->argc; x++)
		_cus_unsetenv(data_, data_->argv[x]);

	return (0);
}

/**
 * setup_env_list - populates env linked list
 * @data_: Structure containing potential
 * Return: Always 0
 */
int setup_env_list(info_t *data_)
{
	list_t *str_end = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		generate_node_end(&str_end, environ[x], 0);
	data_->env = str_end;
	return (0);
}
