#include "consoleShell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_output(av[0]);
				error_output(": 0: Can't open ");
				error_output(av[1]);
				put_error_char('\n');
				put_error_char(FLUSH_THRESHOLD);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	setup_env_list(info);
	get_history(info);
	hShell(info, av);
	return (EXIT_SUCCESS);
}
