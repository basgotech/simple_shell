#include "consoleShell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
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
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
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
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
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
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
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
