#include "header_files.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *str_Merge(char *destination, const char *origin)
{
	int y, z;

	for (y = 0; destination[y] != '\0'; y++)
		;

	for (z = 0; origin[z] != '\0'; z++)
	{
		destination[y] = origin[z];
		y++;
	}

	destination[y] = '\0';
	return (destination);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *str_Copy(char *destination, char *origin)
{

	size_t x;

	for (x = 0; origin[x] != '\0'; x++)
	{
		destination[x] = origin[x];
	}
	destination[x] = '\0';

	return (destination);
}
/**
 * _mystrcmp - Compares two strings character by character.
 * @s1: Pointer to the first string to compare.
 * @s2:  Pointer to the second string to compare.
 * Return: Always 0.
 */
int string_Comparator(char *string1, char *string2)
{
	int i;

	for (i = 0; string1[i] == string2[i] && string1[i]; i++)
		;

	if (string1[i] > string2[i])
		return (1);
	if (string1[i] < string2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *locate_Char(char *string, char ch)
{
	unsigned int y = 0;

	for (; *(string + y) != '\0'; y++)
		if (*(string + y) == ch)
			return (string + y);
	if (*(string + y) == ch)
		return (string + y);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int string_Span(char *string, char *processInput)
{
	int i, j, bool;

	for (i = 0; *(string + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(processInput + j) != '\0'; j++)
		{
			if (*(string + i) == *(processInput + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
