/*===========================================================================*/
/* The ast_get_fname gets the assembly source file (asf) name, opens it,
checks if it exists, and returns the pointer to it. */
/*===========================================================================*/

#include "ast_asm.h" /* Contains stdio.lib and std.lib */

FILE *ast_get_fname()
	{
	FILE	*fopen(), *in_fname;
	char	fname[13];
	printf("\nEnter the assembly source file name: ");
	gets(fname);	
	in_fname = fopen(fname, "r");	/*open the assembly source file 
										and check if it exists*/	
	if (in_fname == NULL)
	{
		printf("\nThe assembly source file does not exist or cannot be opened.");
		printf("\nPlease make sure that the file exists and is located in the current directory.");
	}
	else
	{
		printf("\nThe assembly source file has been successfully opened for reading.\n");
	}
	return (in_fname);
}
