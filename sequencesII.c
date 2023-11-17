#include "consoleShell.h"

/**
 * get_list_size - determines length of linked list.
 * @ptr_f: pointer to first node
 * Return: size of list
 */
size_t get_list_size(const list_t *ptr_f)
{
	size_t i = 0;

	while (ptr_f)
	{
		ptr_f = ptr_f->next;
		i++;
	}
	return (i);
}

/**
 * list_stringify - returns an array of strings of the list->str
 * @upp: pointer to first node
 * Return: array of strings
 */
char **list_stringify(list_t *upp)
{
	list_t *str_end = upp;
	size_t x = get_list_size(upp), y;
	char **strs;
	char *str;

	if (!upp || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; str_end; str_end = str_end->next, x++)
	{
		str = malloc(string_size(str_end->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = str_clone(str, str_end->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * show_list - prints all elements of a list_t linked list
 * @pfn: pointer to first node
 * Return: size of list
 */
size_t show_list(const list_t *pfn)
{
	size_t x = 0;

	while (pfn)
	{
		display_string(convert_numeric(pfn->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		display_string(pfn->str ? pfn->str : "(nil)");
		display_string("\n");
		pfn = pfn->next;
		x++;
	}
	return (x);
}

/**
 * node_prefix_match - returns node whose string starts with prefix
 * @end_str: pointer to list head
 * @firs_is: string to match
 * @ch: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_prefix_match(list_t *end_str, char *firs_is, char ch)
{
	char *p = NULL;

	while (end_str)
	{
		p = is_prefixed(end_str->str, firs_is);
		if (p && ((ch == -1) || (*p == ch)))
			return (end_str);
		end_str = end_str->next;
	}
	return (NULL);
}

/**
 * retrieve_node_index - gets the index of a node
 * @hh: pointer to list head
 * @str_end: pointer to the node
 * Return: index of node or -1
 */
ssize_t retrieve_node_index(list_t *hh, list_t *str_end)
{
	size_t x = 0;

	while (hh)
	{
		if (hh == str_end)
			return (x);
		hh = hh->next;
		x++;
	}
	return (-1);
}
