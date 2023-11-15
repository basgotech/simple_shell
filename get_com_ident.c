#include "header_files.h"

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void getsigint(int si)
{
	(void)si;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
