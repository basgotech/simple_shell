#include "header_files.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void verifyEnv(reg_var **head, char *input, data_shell *d)
{
	int entry, c, x, val;
	char **env;

	env = d->_environ;
	for (entry = 0; env[entry]; entry++)
	{
		for (x = 1, c = 0; env[entry][c]; c++)
		{
			if (env[entry][c] == '=')
			{
				val = str_Length(env[entry] + c + 1);
				insert_Variable_Node(head, x, env[entry] + c + 1, val);
				return;
			}

			if (input[x] == env[entry][c])
				x++;
			else
				break;
		}
	}

	for (x = 0; input[x]; x++)
	{
		if (input[x] == ' ' || input[x] == '\t' || input[x] == ';' || input[x] == '\n')
			break;
	}

	insert_Variable_Node(head, x, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int validateVar(reg_var **head, char *dataIn, char *s, data_shell *data_shell)
{
	int y, en, pid_l;

	en = str_Length(s);
	pid_l = str_Length(data_shell->pid);

	for (y = 0; dataIn[y]; y++)
	{
		if (dataIn[y] == '$')
		{
			if (dataIn[y + 1] == '?')
				insert_Variable_Node(head, 2, s, en), y++;
			else if (dataIn[y + 1] == '$')
				insert_Variable_Node(head, 2, data_shell->pid, pid_l), y++;
			else if (dataIn[y + 1] == '\n')
				insert_Variable_Node(head, 0, NULL, 0);
			else if (dataIn[y + 1] == '\0')
				insert_Variable_Node(head, 0, NULL, 0);
			else if (dataIn[y + 1] == ' ')
				insert_Variable_Node(head, 0, NULL, 0);
			else if (dataIn[y + 1] == '\t')
				insert_Variable_Node(head, 0, NULL, 0);
			else if (dataIn[y + 1] == ';')
				insert_Variable_Node(head, 0, NULL, 0);
			else
				verifyEnv(head, dataIn + y, data_shell);
		}
	}

	return (y);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *substituted_Input(reg_var **head, char *dataIn, char *new_dataIn, int len)
{
	reg_var *index;
	int x, y, z;

	index = *head;
	for (y = x = 0; x < len; x++)
	{
		if (dataIn[y] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_dataIn[x] = dataIn[y];
				y++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (z = 0; z < index->len_var; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0; z < index->len_val; z++)
				{
					new_dataIn[x] = index->val[z];
					x++;
				}
				y += (index->len_var);
				x--;
			}
			index = index->next;
		}
		else
		{
			new_dataIn[x] = dataIn[y];
			y++;
		}
	}

	return (new_dataIn);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *changedVar(char *dataIn, data_shell *datashell)
{
	reg_var *h, *index;
	char *condition, *new_datain;
	int oln, nl;

	condition = int_To_Str(datashell->status);
	h = NULL;

	oln = validateVar(&h, dataIn, condition, datashell);

	if (h == NULL)
	{
		free(condition);
		return (dataIn);
	}

	index = h;
	nl = 0;

	while (index != NULL)
	{
		nl += (index->len_val - index->len_var);
		index = index->next;
	}

	nl += oln;

	new_datain = malloc(sizeof(char) * (nl + 1));
	new_datain[nl] = '\0';

	new_datain = substituted_Input(&h, dataIn, new_datain, nl);

	free(dataIn);
	free(condition);
	relase_Variable_list(&h);

	return (new_datain);
}
