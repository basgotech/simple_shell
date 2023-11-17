#include "consoleShell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *fill_memory(char *memoa, char byf, unsigned int am)
{
	unsigned int x;

	for (x = 0; x < am; x++)
		memoa[x] = byf;
	return (memoa);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void deallocate_memory(char **sts)
{
	char **asts = sts;

	if (!sts)
		return;
	while (*sts)
		free(*sts++);
	free(asts);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *reallocate_memory(void *ptr, unsigned int os, unsigned int nss)
{
	char *p;

	if (!ptr)
		return (malloc(nss));
	if (!nss)
		return (free(ptr), NULL);
	if (nss == os)
		return (ptr);

	p = malloc(nss);
	if (!p)
		return (NULL);

	os = os < nss ? os : nss;
	while (os--)
		p[os] = ((char *)ptr)[os];
	free(ptr);
	return (p);
}
