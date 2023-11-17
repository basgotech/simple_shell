#include "consoleShell.h"

/**
 **fill_memory - fills memory with a constant byte.
 *@memoa: the pointer to the memory area
 *@byf: the byte to fill *s with
 *@am: the amount of bytes to be filled
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
 * deallocate_memory - frees a string of strings
 * @sts: string of strings
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
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @os: byte size of previous block
 * @nss: byte size of new block
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
