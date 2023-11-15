#include "header_files.h"

/*
 *cd_changer- Changes the current directory in the data shell.
 *@dshell: Pointer to the data shell structure.
 *@return: Returns an integer indicating the success 
 *or failure of the directory change.
 */
int cd_changer(data_shell *dshell)
{
	char *directory_to;
	int placeI, placeII, isspaced;
	directory_to = dshell->args[1];
	if (directory_to != NULL)
	{
		placeI = string_Comparator("$HOME", directory_to);
		placeII = string_Comparator("~", directory_to);
		isspaced = string_Comparator("--", directory_to);
	}
	if (directory_to == NULL || !isspaced || !placeI || !placeII )
	{
		navigate_Home(dshell);
		return (1);
	}
	if (string_Comparator("-", directory_to) == 0)
	{
		navigate_Back(dshell);
		return (1);
	}
	if (string_Comparator(".", directory_to) == 0 || string_Comparator("..", directory_to) == 0)
	{
		navigateParentDirectory(dshell);
		return (1);
	}
	navigate_To(dshell);
	return (1);
}
