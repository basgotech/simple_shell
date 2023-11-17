#include "consoleShell.h"

/**
 * reset_info - initializes info_t struct
 * @data_: struct address
 */
void reset_info(info_t *data_)
{
	data_->arg = NULL;
	data_->argv = NULL;
	data_->path = NULL;
	data_->argc = 0;
}

/**
 * initialize_info - initializes info_t struct
 * @data_: struct address
 * @argvv: argument vector
 */
void initialize_info(info_t *data_, char **argvv)
{
	int x = 0;

	data_->fname = argvv[0];
	if (data_->arg)
	{
		data_->argv = tokenize_str(data_->arg, " \t");
		if (!data_->argv)
		{

			data_->argv = malloc(sizeof(char *) * 2);
			if (data_->argv)
			{
				data_->argv[0] = string_duplicate(data_->arg);
				data_->argv[1] = NULL;
			}
		}
		for (x = 0; data_->argv && data_->argv[x]; x++)
			;
		data_->argc = x;

		modify_alias(data_);
		modify_vars(data_);
	}
}

/**
 * deallocate_info - frees info_t struct fields
 * @data_: struct address
 * @all: true if freeing all fields
 */
void deallocate_info(info_t *data_, int all)
{
	deallocate_memory(data_->argv);
	data_->argv = NULL;
	data_->path = NULL;
	if (all)
	{
		if (!data_->cmd_buf)
			free(data_->arg);
		if (data_->env)
			deallocate_list(&(data_->env));
		if (data_->history)
			deallocate_list(&(data_->history));
		if (data_->alias)
			deallocate_list(&(data_->alias));
		deallocate_memory(data_->environ);
			data_->environ = NULL;
		release_blocks((void **)data_->cmd_buf);
		if (data_->readfd > 2)
			close(data_->readfd);
		_putchar(FLUSH_THRESHOLD);
	}
}
