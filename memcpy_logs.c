#include "header_files.h"

/**
 * _memcpy - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void memory_Copy(void *ptrInstance, const void *pointer, unsigned int size)
{
	char *char_ptr = (char *)pointer;
	char *char_newptr = (char *)ptrInstance;
	unsigned int y;

	for (y = 0; y < size; y++)
		char_newptr[y] = char_ptr[y];
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *reallocate_Memory(void *ptr, unsigned int os, unsigned int ns)
{
	void *freshptr;

	if (ptr == NULL)
		return (malloc(ns));

	if (ns == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ns == os)
		return (ptr);

	freshptr = malloc(ns);
	if (freshptr == NULL)
		return (NULL);

	if (ns < os)
		memory_Copy(freshptr, ptr, ns);
	else
		memory_Copy(freshptr, ptr, os);

	free(ptr);
	return (freshptr);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **reallocateDPtr(char **ptr, unsigned int os, unsigned int ns)
{
	char **freshptr;
	unsigned int y;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * ns));

	if (ns == os)
		return (ptr);

	freshptr = malloc(sizeof(char *) * ns);
	if (freshptr == NULL)
		return (NULL);

	for (y = 0; y < os; y++)
		freshptr[y] = ptr[y];

	free(ptr);

	return (freshptr);
}
