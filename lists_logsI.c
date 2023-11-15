#include "header_files.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
separated_Items *add_Separation_At_End(separated_Items **head, char sep)
{
	separated_Items *fresh, *placeholder;

	fresh = malloc(sizeof(separated_Items));
	if (fresh == NULL)
		return (NULL);

	fresh->separator = sep;
	fresh->next = NULL;
	placeholder = *head;

	if (placeholder == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (placeholder->next != NULL)
			placeholder = placeholder->next;
		placeholder->next = fresh;
	}

	return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void release_Separated_List(separated_Items **head)
{
	separated_Items *placeholder;
	separated_Items *current;

	if (head != NULL)
	{
		current = *head;
		while ((placeholder = current) != NULL)
		{
			current = current->next;
			free(placeholder);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_Collection *insert_Line_End_Node(line_Collection **head, char *line)
{
	line_Collection *fresh, *placeholder;

	fresh = malloc(sizeof(line_Collection));
	if (fresh == NULL)
		return (NULL);

	fresh->line = line;
	fresh->next = NULL;
	placeholder = *head;

	if (placeholder == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (placeholder->next != NULL)
			placeholder = placeholder->next;
		placeholder->next = fresh;
	}

	return (*head);
}

/**
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void release_Line_List(line_Collection **head)
{
	line_Collection *placeholder;
	line_Collection *current;

	if (head != NULL)
	{
		current = *head;
		while ((placeholder = current) != NULL)
		{
			current = current->next;
			free(placeholder);
		}
		*head = NULL;
	}
}
