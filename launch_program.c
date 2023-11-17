#include "consoleShell.h"

/**
 * main - entry point.
 * @argc: arg count
 * @argv: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t data_c[] = { INFO_INIT };
	int fdis = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdis)
		: "r" (fdis));

	if (argc == 2)
	{
		fdis = open(argv[1], O_RDONLY);
		if (fdis == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_output(argv[0]);
				error_output(": 0: Can't open ");
				error_output(argv[1]);
				put_error_char('\n');
				put_error_char(FLUSH_THRESHOLD);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data_c->readfd = fdis;
	}
	setup_env_list(data_c);
	get_history(data_c);
	hShell(data_c, argv);
	return (EXIT_SUCCESS);
}
