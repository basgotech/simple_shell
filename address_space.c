#include "consoleShell.h"

/**
 * release_blocks - frees a pointer and NULLs the address
 * @ad_ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int release_blocks(void **ad_ptr)
{
	if (ad_ptr && *ad_ptr)
	{
		free(*ad_ptr);
		*ad_ptr = NULL;
		return (1);
	}
	return (0);
}
