#include <stdio.h>
#include <stdlib.h>
/* My include header file */
#include "ast_asm.h"

/* ASSEMBLER FOR HET SYS */
/* ASHISH TONDWALKAR */


/*===========================================================================*/
/* Run this program using the command (prompt) console */
/* Below is the main function */
/* This "skeleton assembler" was developed with Dev-C++5.11 */
/* (c) Dorin Patru - September 2022 */
/*===========================================================================*/
int main(int argc, char *argv[]) {
/*---------------------------------------------------------------------------*/
/*open assembly source file, intermediate directives file, intermediate 
constants file, intermediate code file, and output *.mif file */
/*---------------------------------------------------------------------------*/
	FILE	*fopen(), *in_ass, *int_dir, *int_const, *int_code, *out_mif;
	char 	ass_fname[13];
/*---------------------------------------------------------------------------*/
/*Contains the instruction mnemonic array of strings declaration and definition.*/
/*---------------------------------------------------------------------------*/
#include "ast_const.h" 
/*---------------------------------------------------------------------------*/
/*Get the name of the assembly source file and open it for read.*/
/*---------------------------------------------------------------------------*/
	in_ass = ast_get_fname(); 
/*---------------------------------------------------------------------------*/
/*Open the other intermmediate files.*/
/*---------------------------------------------------------------------------*/
	int_dir = fopen("dir.txt", "w");
	int_const = fopen("const.txt", "w");
	int_code = fopen("code.txt", "w");
/*---------------------------------------------------------------------------*/
/*Call the subroutine that performs the checks for the correct structure of the 
assembly source code file and for syntax errors at the beginning of each line 
of code.*/
/*---------------------------------------------------------------------------*/
	printf("\n\nStep1: Structural and Preliminary Syntactical Check:\n");
	step1_syntax_check(in_ass, int_dir, int_const, int_code, im);
/*---------------------------------------------------------------------------*/
/*First good news ;-)*/
/*---------------------------------------------------------------------------*/
	printf("\n\nStep1: Structural and Preliminary Syntactical Check\n \
		==> Concluded successfully. <==");
	printf("\n\nThe files are now being closed.");
/*---------------------------------------------------------------------------*/
/*To be safe, close all files here.*/
/*---------------------------------------------------------------------------*/
	fclose(in_ass); fclose(int_dir); fclose(int_const); fclose(int_code);
/*---------------------------------------------------------------------------*/
/*Reopen intermmediate files and output mif file:*/
/*---------------------------------------------------------------------------*/
	printf("\n\nThe files are now being opened.");
	out_mif = fopen("mnist_program.mif", "w"); int_dir = fopen("dir.txt", "r");
	int_const = fopen("const.txt", "r"); int_code = fopen("code.txt", "r");
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
	printf("\n\nStep2: Assembly:\n");
	step2_assembly(int_code, int_dir, int_const, out_mif, im, OpCode, \
					Ri, RiFieldValue, Rj, RjFieldValue, mri);	
/*---------------------------------------------------------------------------*/
/* Second good news ;-)*/
/*---------------------------------------------------------------------------*/
	printf("\n\nStep2: Assembly\n \
		==> Concluded successfully. <==");
	printf("\n\nThe files are now being closed.");
	printf("\n\nReady to Test on astRISC! 8)");
/*---------------------------------------------------------------------------*/
/*Close ALL files.*/
/*---------------------------------------------------------------------------*/
	fclose(out_mif); fclose(int_dir); fclose(int_const); fclose(int_code);
/*---------------------------------------------------------------------------*/
/*Done.*/
/*---------------------------------------------------------------------------*/
	return 0;
}


