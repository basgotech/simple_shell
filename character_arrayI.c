#include "consoleShell.h"

/**
 * string_size - returns the length of a string
 * @str_check: the string whose length to check
 * Return: integer length of string.
 */
int string_size(char *str_check)
{
	int x = 0;

	if (!str_check)
		return (0);

	while (*str_check++)
		x++;
	return (x);
}

/**
 * string_equals - performs lexicogarphic comp
 * @str1: the first strang
 * @str2: the second strang
 * Return: negative if s1 < s2, positive
 */
int string_equals(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * is_prefixed - checks if needle starts with haystack
 * @ispre: string to search
 * @key: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *is_prefixed(const char *ispre, const char *key)
{
	while (*key)
		if (*key++ != *ispre++)
			return (NULL);
	return ((char *)ispre);
}

/**
 * join_strings - concatenates two strings
 * @dist: the destination buffer
 * @from: the source buffer
 * Return: pointer to destination buffer
 */
char *join_strings(char *dist, char *from)
{
	char *ret = dist;

	while (*dist)
		dist++;
	while (*from)
		*dist++ = *from++;
	*dist = *from;
	return (ret);
}
