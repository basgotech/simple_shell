#include "consoleShell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *str_clone(char *target, char *origin)
{
	int x = 0;

	if (target == origin || origin == 0)
		return (target);
	while (origin[x])
	{
		target[x] = origin[x];
		x++;
	}
	target[x] = 0;
	return (target);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_duplicate(const char *char_seq)
{
	int len = 0;
	char *fetch;

	if (char_seq == NULL)
		return (NULL);
	while (*char_seq++)
		len++;
	fetch = malloc(sizeof(char) * (len + 1));
	if (!fetch)
		return (NULL);
	for (len++; len--;)
		fetch[len] = *--char_seq;
	return (fetch);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void display_string(char *char_seq)
{
	int x = 0;

	if (!char_seq)
		return;
	while (char_seq[x] != '\0')
	{
		_putchar(char_seq[x]);
		x++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int x;
	static char buf[WRITE_CHUNK_SIZE];

	if (ch == FLUSH_THRESHOLD || x >= WRITE_CHUNK_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (ch != FLUSH_THRESHOLD)
		buf[x++] = ch;
	return (1);
}
