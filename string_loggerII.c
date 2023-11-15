#include "header_files.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *clone_String(const char *string)
{
	char *newInstance;
	size_t length;

	length = str_Length(string);
	newInstance = malloc(sizeof(char) * (length + 1));
	if (newInstance == NULL)
		return (NULL);
	memory_Copy(newInstance, string, length + 1);
	return (newInstance);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int str_Length(const char *string)
{
	int length;

	for (length = 0; string[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int char_Compare(char string[], const char *divider)
{
	unsigned int x, y, z;

	for (x = 0, z= 0; string[x]; x++)
	{
		for (y = 0; divider[y]; y++)
		{
			if (string[x] == divider[y])
			{
				z++;
				break;
			}
		}
	}
	if (x == z)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *tokenize_String(char string[], const char *divider)
{
	static char *broken_Down, *str_Termination;
	char *string_Start;
	unsigned int z, isTrue;

	if (string != NULL)
	{
		if (char_Compare(string, divider))
			return (NULL);
		broken_Down = string; /*Store first address*/
		z = str_Length(string);
		str_Termination = &string[z]; /*Store last address*/
	}
	string_Start = broken_Down;
	if (string_Start == str_Termination) /*Reaching the end*/
		return (NULL);

	for (isTrue = 0; *broken_Down; broken_Down++)
	{
		/*Breaking loop finding the next token*/
		if (broken_Down != string_Start)
			if (*broken_Down && *(broken_Down - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (z = 0; divider[z]; z++)
		{
			if (*broken_Down == divider[z])
			{
				*broken_Down = '\0';
				if (broken_Down == string_Start)
					string_Start++;
				break;
			}
		}
		if (isTrue == 0 && *broken_Down) /*Str != Delim*/
			isTrue = 1;
	}
	if (isTrue == 0) /*Str == Delim*/
		return (NULL);
	return (string_Start);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int is_Number(const char *string)
{
	unsigned int y;

	for (y = 0; string[y]; y++)
	{
		if (string[y] < 48 || string[y] > 57)
			return (0);
	}
	return (1);
}
