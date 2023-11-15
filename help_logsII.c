#include "header_files.h"

/**
 * aux_help - Help information for the builtin help.
 * Return: no return
 */
void supportHelp(void)
{
	char *assist = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, assist, str_Length(assist));
}
/**
 * aux_help_alias - Help information for the builtin 																Qalias.
 * Return: no return
 */
void supportAliasHelp(void)
{
	char *assist = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, assist, str_Length(assist));
}
/**
 * aux_help_cd - Help information for the builtin alias.
 * Return: no return
 */
void supportCdHelp(void)
{
	char *assist = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, assist, str_Length(assist));
}
