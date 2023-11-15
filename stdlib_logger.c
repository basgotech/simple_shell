#include "header_files.h"

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_length(int x)
{
	unsigned int x1;
	int length = 1;

	if (x < 0)
	{
		length++;
		x1 = x * -1;
	}
	else
	{
		x1 = x;
	}
	while (x1 > 9)
	{
		length++;
		x1 = x1 / 10;
	}

	return (length);
}
/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *int_To_Str(int x)
{
	unsigned int x1;
	int length = get_length(x);
	char *dataCache;

	dataCache = malloc(sizeof(char) * (length + 1));
	if (dataCache == 0)
		return (NULL);

	*(dataCache + length) = '\0';

	if (x < 0)
	{
		x1 = x * -1;
		dataCache[0] = '-';
	}
	else
	{
		x1 = x;
	}

	length--;
	do {
		*(dataCache + length) = (x1 % 10) + '0';
		x1 = x1 / 10;
		length--;
	}
	while (x1 > 0)
		;
	return (dataCache);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int parseToInt(char *string)
{
	unsigned int total = 0, dimension = 0, w = 0, x = 1, y = 1, z;

	while (*(string + total) != '\0')
	{
		if (dimension > 0 && (*(string + total) < '0' || *(string + total) > '9'))
			break;

		if (*(string + total) == '-')
			x *= -1;

		if ((*(string + total) >= '0') && (*(string + total) <= '9'))
		{
			if (dimension > 0)
				y *= 10;
			dimension++;
		}
		total++;
	}

	for (z = total - dimension; z < total; z++)
	{
		w = w + ((*(string + z) - 48) * y);
		y /= 10;
	}
	return (w * x);
}
