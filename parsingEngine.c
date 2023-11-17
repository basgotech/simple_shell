#include "consoleShell.h"

/**
 * validate_cmd - determines if a file is an executable command.
 * @cont: the info struct.
 * @routt: path to the file
 * Return: 1 if true, 0 otherwise
 */
int validate_cmd(info_t *cont, char *routt)
{
	struct stat stt;

	(void)cont;
	if (!routt || stat(routt, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * cloneChars - duplicates characters
 * @route_str: the PATH string
 * @set: starting index
 * @unset: stopping index
 * Return: pointer to new buffer
 */
char *cloneChars(char *route_str, int set, int unset)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = set; i < unset; i++)
		if (route_str[i] != ':')
			buf[k++] = route_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * locate_dir - finds this cmd in the PATH string
 * @context: the info struct
 * @route_str: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *locate_dir(info_t *context, char *route_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!route_str)
		return (NULL);
	if ((string_size(cmd) > 2) && is_prefixed(cmd, "./"))
	{
		if (validate_cmd(context, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!route_str[i] || route_str[i] == ':')
		{
			path = cloneChars(route_str, curr_pos, i);
			if (!*path)
				join_strings(path, cmd);
			else
			{
				join_strings(path, "/");
				join_strings(path, cmd);
			}
			if (validate_cmd(context, path))
				return (path);
			if (!route_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
