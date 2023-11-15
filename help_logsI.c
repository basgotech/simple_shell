#include "header_files.h"

/**
 * aux_help_env - Help information for the builtin env
 * Return: no return
 */
void supportEnvHelp(void)
{
	char *assist = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, assist, str_Length(assist));

}
/**
 * aux_help_setenv - Help information for the builtin setenv
 * Return: no return
 */
void supportSetenvHelp(void)
{
	char *assist = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "int replace)\n\t";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, assist, str_Length(assist));
}
/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void supportUnsetenvHelp(void)
{
	char *assist = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, assist, str_Length(assist));
}


/**
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */
void supportGeneralHelp(void)
{
	char *assist = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "unsetenv [variable]\n";
	write(STDOUT_FILENO, assist, str_Length(assist));
}
/**
 * aux_help_exit - Help information fot the builint exit
 * Return: no return
 */
void supportExitHelp(void)
{
	char *assist = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, assist, str_Length(assist));
	assist = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, assist, str_Length(assist));
}
