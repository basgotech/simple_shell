#include "header_files.h"

/**
 * read_line - reads the input string.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_Input_Line(int *endOfFileInput)
{
	char *dataIn = NULL;
	size_t sizeOfBuffer = 0;

	*endOfFileInput = getline(&dataIn, &sizeOfBuffer, stdin);

	return (dataIn);
}
