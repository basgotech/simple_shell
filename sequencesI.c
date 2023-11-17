#include "consoleShell.h"

/**
 * generate_node - adds a node to the start of the list
 * @upp: address of pointer to head node
 * @str_col: str field of node
 * @numberr: node index used by history
 * Return: size of list
 */
list_t *generate_node(list_t **upp, const char *str_col, int numberr)
{
	list_t *n_upp;

	if (!upp)
		return (NULL);
	n_upp = malloc(sizeof(list_t));
	if (!n_upp)
		return (NULL);
	fill_memory((void *)n_upp, 0, sizeof(list_t));
	n_upp->num = numberr;
	if (str_col)
	{
		n_upp->str = string_duplicate(str_col);
		if (!n_upp->str)
		{
			free(n_upp);
			return (NULL);
		}
	}
	n_upp->next = *upp;
	*upp = n_upp;
	return (n_upp);
}

/**
 * generate_node_end - adds a node to the end of the list
 * @upp: address of pointer to head node
 * @str_col: str field of node
 * @numberr: node index used by history
 *
 * Return: size of list
 */
list_t *generate_node_end(list_t **upp, const char *str_col, int numberr)
{
	list_t *nupp, *str_end;

	if (!upp)
		return (NULL);

	str_end = *upp;
	nupp = malloc(sizeof(list_t));
	if (!nupp)
		return (NULL);
	fill_memory((void *)nupp, 0, sizeof(list_t));
	nupp->num = numberr;
	if (str_col)
	{
		nupp->str = string_duplicate(str_col);
		if (!nupp->str)
		{
			free(nupp);
			return (NULL);
		}
	}
	if (str_end)
	{
		while (str_end->next)
			str_end = str_end->next;
		str_end->next = nupp;
	}
	else
		*upp = nupp;
	return (nupp);
}

/**
 * show_string_list - prints only the str element
 * @asd: pointer to first node
 * Return: size of list
 */
size_t show_string_list(const list_t *asd)
{
	size_t x = 0;

	while (asd)
	{
		display_string(asd->str ? asd->str : "(nil)");
		display_string("\n");
		asd = asd->next;
		x++;
	}
	return (x);
}

/**
 * erase_node_at_position - deletes node at given index
 * @upp: address of pointer to first node
 * @in: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int erase_node_at_position(list_t **upp, unsigned int in)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!upp || !*upp)
		return (0);

	if (!in)
	{
		node = *upp;
		*upp = (*upp)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *upp;
	while (node)
	{
		if (i == in)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * deallocate_list - frees all nodes of a list
 * @upp_pt: address of pointer to head node
 * Return: void
 */
void deallocate_list(list_t **upp_pt)
{
	list_t *node, *next_node, *head;

	if (!upp_pt || !*upp_pt)
		return;
	head = *upp_pt;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*upp_pt = NULL;
}
