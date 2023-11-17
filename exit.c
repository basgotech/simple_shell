#include "consoleShell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *str_sub_copy(char *target, char *origin, int n)
{
	int x, y;
	char *tr = target;

	x = 0;
	while (origin[x] != '\0' && x < n - 1)
	{
		target[x] = origin[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			target[y] = '\0';
			y++;
		}
	}
	return (tr);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *substring_conca(char *target, char *origin, int amoun)
{
	int x, y;
	char *targ = target;

	x = 0;
	y = 0;
	while (target[x] != '\0')
		x++;
	while (origin[y] != '\0' && y < amoun)
	{
		target[x] = origin[y];
		x++;
		y++;
	}
	if (y < amoun)
		target[x] = '\0';
	return (targ);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *search_for_char(char *string, char ch)
{
	do {
		if (*string == ch)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
