#include "consoleShell.h"

/**
 * **tokenize_str - splits a string into words.
 * @strr: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **tokenize_str(char *strr, char *del)
{
	int i, j, k, m, numw = 0;
	char **s;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; strr[i] != '\0'; i++)
		if (!is_delim(strr[i], del) && (is_delim(strr[i + 1], del) || !strr[i + 1]))
			numw++;

	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numw; j++)
	{
		while (is_delim(strr[i], del))
			i++;
		k = 0;
		while (!is_delim(strr[i + k], del) && strr[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = strr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **tokenize_strad - splits a string into words
 * @str_col: the input string
 * @dd: the delimeter
 * Return: a pointer to ary
 */
char **tokenize_strad(char *str_col, char dd)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str_col == NULL || str_col[0] == 0)
		return (NULL);
	for (i = 0; str_col[i] != '\0'; i++)
		if ((str_col[i] != dd && str_col[i + 1] == dd) ||
		    (str_col[i] != dd && !str_col[i + 1]) || str_col[i + 1] == dd)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str_col[i] == dd&& str_col[i] != dd)
			i++;
		k = 0;
		while (str_col[i + k] != dd && str_col[i + k] && str_col[i + k] != dd)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str_col[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
