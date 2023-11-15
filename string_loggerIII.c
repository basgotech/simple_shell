#include "header_files.h"

/**
 * mirrorString - reverses a string.
 * @string: Pointer to the string to be reversed.
 * Return: no return.
 */
void mirror_String(char *string)
{
	int counter = 0, y, z;
	char *input, placeholder;

	while (counter >= 0)
	{
		if (string[counter] == '\0')
			break;
		counter++;
	}
	input = string;

	for (y = 0; y < (counter - 1); y++)
	{
		for (z = y + 1; z > 0; z--)
		{
			placeholder = *(input + z);
			*(input + z) = *(input + (z - 1));
			*(input + (z - 1)) = placeholder;
		}
	}
}
