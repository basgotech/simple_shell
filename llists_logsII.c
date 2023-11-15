#include "header_files.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
reg_var *insert_Variable_Node(reg_var **head, int sc_var, char *in_Var, int varLcl)
{
	reg_var *fresh, *PlaceHolder;

	fresh = malloc(sizeof(reg_var));
	if (fresh == NULL)
		return (NULL);

	fresh->len_var = sc_var;
	fresh->val = in_Var;
	fresh->len_val = varLcl;

	fresh->next = NULL;
	PlaceHolder = *head;

	if (PlaceHolder == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (PlaceHolder->next != NULL)
			PlaceHolder = PlaceHolder->next;
		PlaceHolder->next = fresh;
	}

	return (*head);
}

/**
 * free_rvar_list - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void relase_Variable_list(reg_var **head)
{
	reg_var *placeHolder;
	reg_var *current;

	if (head != NULL)
	{
		current = *head;
		while ((placeHolder = current) != NULL)
		{
			current = current->next;
			free(placeHolder);
		}
		*head = NULL;
	}
}
