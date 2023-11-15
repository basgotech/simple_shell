#include "header_files.h"

/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *char_Exchange(char *dataIn, int isTrue)
{
	int y;

	if (isTrue == 0)
	{
		for (y = 0; dataIn[y]; y++)
		{
			if (dataIn[y] == '|')
			{
				if (dataIn[y + 1] != '|')
					dataIn[y] = 16;
				else
					y++;
			}

			if (dataIn[y] == '&')
			{
				if (dataIn[y + 1] != '&')
					dataIn[y] = 12;
				else
					y++;
			}
		}
	}
	else
	{
		for (y = 0; dataIn[y]; y++)
		{
			dataIn[y] = (dataIn[y] == 16 ? '|' : dataIn[y]);
			dataIn[y] = (dataIn[y] == 12 ? '&' : dataIn[y]);
		}
	}
	return (dataIn);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void insert_Nodes(separated_Items **head_sl, line_Collection **head_ll, char *dataIn)
{
	int y;
	char *sequence;

	dataIn = char_Exchange(dataIn, 0);

	for (y = 0; dataIn[y]; y++)
	{
		if (dataIn[y] == ';')
			add_Separation_At_End(head_sl, dataIn[y]);

		if (dataIn[y] == '|' || dataIn[y] == '&')
		{
			add_Separation_At_End(head_sl, dataIn[y]);
			y++;
		}
	}

	sequence = tokenize_String(dataIn, ";|&");
	do {
		sequence = char_Exchange(sequence, 1);
		insert_Line_End_Node(head_ll, sequence);
		sequence = tokenize_String(NULL, ";|&");
	} while (sequence != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void moveForward(separated_Items **list_sl, line_Collection **list_ll, data_shell *datashell)
{
	int separatingLoop;
	separated_Items *sp_i;
	line_Collection *lc;

	separatingLoop = 1;
	sp_i = *list_sl;
	lc = *list_ll;

	while (sp_i != NULL && separatingLoop)
	{
		if (datashell->status == 0)
		{
			if (sp_i->separator == '&' || sp_i->separator == ';')
				separatingLoop = 0;
			if (sp_i->separator == '|')
				lc = lc->next, sp_i = sp_i->next;
		}
		else
		{
			if (sp_i->separator == '|' || sp_i->separator == ';')
				separatingLoop = 0;
			if (sp_i->separator == '&')
				lc = lc->next, sp_i = sp_i->next;
		}
		if (sp_i != NULL && !separatingLoop)
			sp_i = sp_i->next;
	}

	*list_sl = sp_i;
	*list_ll = lc;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int separatedCom(data_shell *datashell, char *dataIn)
{

	separated_Items *head_si, *list_si;
	line_Collection *head_lc, *list_lc;
	int itration;

	head_si = NULL;
	head_lc = NULL;

	insert_Nodes(&head_si, &head_lc, dataIn);

	head_si = list_si;
	list_lc = head_lc;

	while (list_lc != NULL)
	{
		datashell->input = list_lc->line;
		datashell->args = divideLine(datashell->input);
		itration = run_Line(datashell);
		free(datashell->args);

		if (itration == 0)
			break;

		moveForward(&list_si, &list_lc, datashell);

		if (list_lc != NULL)
			list_lc = list_lc->next;
	}

	release_Separated_List(&head_si);
	release_Line_List(&head_lc);

	if (itration == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **divideLine(char *dataIn)
{
	size_t buf_size;
	size_t y;
	char **tok_col;
	char *tok;

	buf_size = TOK_BUFSIZE;
	tok_col = malloc(sizeof(char *) * (buf_size));
	if (tok_col == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tok = tokenize_String(dataIn, TOK_DELIM);
	tok_col[0] = tok;

	for (y = 1; tok != NULL; y++)
	{
		if (y == buf_size)
		{
			buf_size += TOK_BUFSIZE;
			tok_col = reallocateDPtr(tok_col, y, sizeof(char *) * buf_size);
			if (tok_col == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tok = tokenize_String(NULL, TOK_DELIM);
		tok_col[y] = tok;
	}

	return (tok_col);
}
