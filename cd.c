#include "header_files.h"

/**
 * navigateParentDirectory - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */
void navigateParentDirectory(data_shell *data_shell)
{
	char workingDir[PATH_MAX];
	char *dirName, *activeDirectoryPath, *tokenizedCurrentPath;

	getcwd(workingDir, sizeof(workingDir));
	activeDirectoryPath = clone_String(workingDir);
	configure_Env("OLDPWD", activeDirectoryPath, data_shell);
	dirName = data_shell->args[1];
	if (string_Comparator(".", dirName) == 0)
	{
		configure_Env("PWD", activeDirectoryPath, data_shell);
		free(activeDirectoryPath);
		return;
	}
	if (string_Comparator("/", activeDirectoryPath) == 0)
	{
		free(activeDirectoryPath);
		return;
	}
	tokenizedCurrentPath = activeDirectoryPath;
	mirror_String(tokenizedCurrentPath);
	tokenizedCurrentPath = tokenize_String(tokenizedCurrentPath, "/");
	if (tokenizedCurrentPath != NULL)
	{
		tokenizedCurrentPath = tokenize_String(NULL, "\0");

		if (tokenizedCurrentPath != NULL)
			mirror_String(tokenizedCurrentPath);
	}
	if (tokenizedCurrentPath != NULL)
	{
		chdir(tokenizedCurrentPath);
		configure_Env("PWD", tokenizedCurrentPath, data_shell);
	}
	else
	{
		chdir("/");
		configure_Env("PWD", "/", data_shell);
	}
	data_shell->status = 0;
	free(activeDirectoryPath);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void navigate_To(data_shell *dataShell)
{
	char pwd[PATH_MAX];
	char *dir, *current_Path, *dirPath;

	getcwd(pwd, sizeof(pwd));

	dir = dataShell->args[1];
	if (chdir(dir) == -1)
	{
		fetchError(dataShell, 2);
		return;
	}

	current_Path = clone_String(pwd);
	configure_Env("OLDPWD", current_Path, dataShell);

	dirPath = clone_String(dir);
	configure_Env("PWD", dirPath, dataShell);

	free(current_Path);
	free(dirPath);

	dataShell->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void navigate_Back(data_shell *dataShell)
{
	char pwd[PATH_MAX];
	char *active_Dir, *prior_Path, *base_Path, *former_Path;

	getcwd(pwd, sizeof(pwd));
	base_Path = clone_String(pwd);

	prior_Path = get_Env_Value("OLDPWD", dataShell->_environ);

	if (prior_Path == NULL)
		former_Path = base_Path;
	else
		former_Path = clone_String(prior_Path);

	configure_Env("OLDPWD", base_Path, dataShell);

	if (chdir(former_Path) == -1)
		configure_Env("PWD", base_Path, dataShell);
	else
		configure_Env("PWD", former_Path, dataShell);

	active_Dir = get_Env_Value("PWD", dataShell->_environ);

	write(STDOUT_FILENO, active_Dir, str_Length(active_Dir));
	write(STDOUT_FILENO, "\n", 1);

	free(base_Path);
	if (prior_Path)
		free(former_Path);

	dataShell->status = 0;

	chdir(active_Dir);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void navigate_Home(data_shell *dataShell)
{
	char *working_Dir, *base_Dir;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	working_Dir = clone_String(pwd);

	base_Dir = get_Env_Value("HOME", dataShell->_environ);

	if (base_Dir == NULL)
	{
		configure_Env("OLDPWD", working_Dir, dataShell);
		free(working_Dir);
		return;
	}

	if (chdir(base_Dir) == -1)
	{
		fetchError(dataShell, 2);
		free(working_Dir);
		return;
	}

	configure_Env("OLDPWD", working_Dir, dataShell);
	configure_Env("PWD", base_Dir, dataShell);
	free(working_Dir);
	dataShell->status = 0;
}
