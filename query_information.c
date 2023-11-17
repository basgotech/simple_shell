#include "consoleShell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void reset_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void initialize_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = tokenize_str(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		modify_alias(info);
		modify_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void deallocate_info(info_t *info, int all)
{
	deallocate_memory(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			deallocate_list(&(info->env));
		if (info->history)
			deallocate_list(&(info->history));
		if (info->alias)
			deallocate_list(&(info->alias));
		deallocate_memory(info->environ);
			info->environ = NULL;
		release_blocks((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(FLUSH_THRESHOLD);
	}
}
