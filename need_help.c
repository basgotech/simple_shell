#include "header_files.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int fetchHelp(data_shell *datashell)
{

	if (datashell->args[1] == 0)
		supportGeneralHelp();
	else if (string_Comparator(datashell->args[1], "setenv") == 0)
		supportSetenvHelp();
	else if (string_Comparator(datashell->args[1], "env") == 0)
		supportEnvHelp();
	else if (string_Comparator(datashell->args[1], "unsetenv") == 0)
		supportGeneralHelp();
	else if (string_Comparator(datashell->args[1], "help") == 0)
		supportHelp();
	else if (string_Comparator(datashell->args[1], "exit") == 0)
		supportExitHelp();
	else if (string_Comparator(datashell->args[1], "cd") == 0)
		supportCdHelp();
	else if (string_Comparator(datashell->args[1], "alias") == 0)
		supportAliasHelp();
	else
		write(STDERR_FILENO, datashell->args[0],
		      str_Length(datashell->args[0]));

	datashell->status = 0;
	return (1);
}
