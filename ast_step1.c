/*===========================================================================*/
/* The step1_syntax_check subroutine checks for the correct structure of the 
assembly source code file and for syntax errors at the beginning of each line 
of code */
/*===========================================================================*/
/* Includes stdio.lib and std.lib */
/*---------------------------------------------------------------------------*/
#include "ast_asm.h" 
#include <string.h>
/*---------------------------------------------------------------------------*/
void step1_syntax_check(in1_fname, out1_fname, out2_fname, out3_fname, crt_im)
/*---------------------------------------------------------------------------*/
/* Parameter types declarations. */
/*---------------------------------------------------------------------------*/
	FILE *in1_fname; FILE *out1_fname; FILE *out2_fname; FILE *out3_fname;
	const	char	*crt_im[31]; /*Current Instruction Mnemonic*/
	{
/*---------------------------------------------------------------------------*/
/* Local constants and variables declarations. */
/*---------------------------------------------------------------------------*/
	char	crt_line[81];
	char	crt_syllable[20], nxt_syllable[20], thr_syllable[20]; /*Temporary storage for the 
								syllables currently expected and analyzed*/
	int		asf_line_number = 0; /*assembly source file line number*/
	int		i, j, k, match;
	int 	task_counter = 0;
	int		intr_counter = 0;
	int 	mif_counter = 0;
	FILE	*task;
	char	task_names[10][20], mif_names[50][30];
	char	intr_names[10][20], intr_jumps[10][20];
	char	name[20];
	int		index=0;
	char	addr_A[20], addr_B[20], row_A[20], col_A[20], row_B[20], col_B[20], relu[20], row_skip[20], reg1[20];
/*---------------------------------------------------------------------------*/
/*#define astDEBUG - printf for debugging purposes*/
/*---------------------------------------------------------------------------*/
#define astDEBUG = 1;
/*---------------------------------------------------------------------------*/
/* Read the first line, which is expected to be a comment, i.e. should start with ; */	
/*---------------------------------------------------------------------------*/
	fgets(crt_line, 81, in1_fname);
#ifdef astDEBUG
	printf("\nParsing line %3u: %s", asf_line_number, crt_line);
#endif
	sscanf(crt_line, "%s", &crt_syllable);
	if (crt_syllable[0] == ';')
		{
#ifdef astDEBUG
		printf("   Line %3u is a comment ... OK!  Ignoring the rest of the line.", asf_line_number);
#endif
		}
	else
		{
#ifdef astDEBUG
		printf("\nExpecting line %3u to be a comment, i.e. the first character to be <;> ! \
		Ignoring the rest of the line.", asf_line_number);
#endif
		}
/*---------------------------------------------------------------------------*/
/* Read the next lines; expect more comments or the beginning of the directives segment */	
/*---------------------------------------------------------------------------*/
	i = 0;
	while ((strcmp(crt_syllable, ".directives;")) && (i != 20))
		{
		fgets(crt_line, 81, in1_fname);
		++asf_line_number;
#ifdef astDEBUG
		printf("\nParsing line %3u: %s", asf_line_number, crt_line);
#endif
		sscanf(crt_line, "%s", &crt_syllable);
		++i;
		if (crt_syllable[0] == ';')
			{
#ifdef astDEBUG
		printf("   This line seems to be a comment.  Ignoring the rest of the line.");
#endif
			}
		else if (!strcmp(crt_syllable, ".directives;"))
			{
#ifdef astDEBUG
		printf("   Reached the beginning of the .directives segment on line %3u.", asf_line_number);
#endif
			}
		else
			{
		printf("   Syntax Error in line %3u - expecting .directives;", asf_line_number);
			}
	} /*End of first while loop*/
/*---------------------------------------------------------------------------*/
/* Read the next lines; expect more comments, .equ directives or the end of the directives segment */
/*---------------------------------------------------------------------------*/
	i = 0;
	while ((strcmp(crt_syllable, ".enddirectives;")) && (i != 60))
		{
		fgets(crt_line, 81, in1_fname);
		++asf_line_number;
#ifdef astDEBUG
		printf("\nParsing line %3u: %s", asf_line_number, crt_line);
#endif
		sscanf(crt_line, "%s %s %s", &crt_syllable, &nxt_syllable, &thr_syllable);
		++i;
		if (crt_syllable[0] == ';')
			{
#ifdef astDEBUG
		printf("   This line seems to be a comment.  Ignoring the rest of the line.");
#endif
			}
		else if (!strcmp(crt_syllable, ".equ"))
			{
#ifdef astDEBUG
		printf("   The beginning of this line is OK!  Saving it in the dir.txt file.");
#endif
		fprintf(out1_fname, "%3u   %s", asf_line_number, crt_line);
			}
		else if (!strcmp(crt_syllable, ".task"))
			{
		fprintf(out1_fname, "%3u   %s", asf_line_number, crt_line);
		strncpy(task_names[task_counter], nxt_syllable, 20);
#ifdef astDEBUG
		printf("   The beginning of this line is OK!  Saving it in the dir.txt file. Will create task under name %s", task_names[task_counter]);
#endif

		//strcat(nxt_syllable, ".txt");
		//tasks[task_counter] = fopen(nxt_syllable, "r");
		task_counter++;
			}
			else if (!strcmp(crt_syllable, ".mif"))
			{
		fprintf(out1_fname, "%3u   %s", asf_line_number, crt_line);
		strncpy(mif_names[mif_counter], nxt_syllable, 20);
#ifdef astDEBUG
		printf("   The beginning of this line is OK!  Saving it in the dir.txt file. Will append a data file with %s", mif_names[mif_counter]);
#endif
			mif_counter++;
			}
			else if (!strcmp(crt_syllable, ".intr"))
			{
		fprintf(out1_fname, "%3u   %s", asf_line_number, crt_line);
		strncpy(intr_names[intr_counter], nxt_syllable, 20);
		strncpy(intr_jumps[intr_counter], thr_syllable, 20);
#ifdef astDEBUG
		printf("   The beginning of this line is OK!  Saving it in the dir.txt file. Will an interrupt %s", task_names[task_counter]);
#endif

		//strcat(nxt_syllable, ".txt");
		//tasks[task_counter] = fopen(nxt_syllable, "r");
		intr_counter++;
			}
		else if (!strcmp(crt_syllable, ".enddirectives;"))
			{
#ifdef astDEBUG
		printf("   Reached the end of the .directives segment on line %3u.", asf_line_number);
#endif
			}
		else
			{
		printf("   Syntax Error in line %3u - expecting .equ or ;", asf_line_number);
			}
	
	}/*End of second while loop*/
/*---------------------------------------------------------------------------*/
/* Read the next lines; expect more comments or the beginning of the .const segment */	
/*---------------------------------------------------------------------------*/
	i = 0;
	while ((strcmp(crt_syllable, ".constants;")) && (i != 20))
		{
		fgets(crt_line, 81, in1_fname);
		++asf_line_number;
#ifdef astDEBUG
		printf("\nParsing line %3u: %s", asf_line_number, crt_line);
#endif
		sscanf(crt_line, "%s", &crt_syllable);
		++i;
		if (crt_syllable[0] == ';')
			{
#ifdef astDEBUG
		printf("   This line seems to be a comment.  Ignoring the rest of the line.");
#endif
			}
		else if (!strcmp(crt_syllable, ".constants;"))
			{
#ifdef astDEBUG
		printf("   Reached the beginning of the .constants segment on line %3u.", asf_line_number);
#endif
			}
		else
			{
		printf("   Syntax Error in line %3u - expecting .constants;", asf_line_number);
			}
	}/*End of third while loop*/
/*---------------------------------------------------------------------------*/
/* Read the next lines; expect more comments, .word directives or the end of the .constants segment */
/*---------------------------------------------------------------------------*/
	i = 0;
	while ((strcmp(crt_syllable, ".endconstants;")) && (i != 20))
		{
		fgets(crt_line, 81, in1_fname);
		++asf_line_number;
#ifdef astDEBUG
		printf("\nParsing line %3u: %s", asf_line_number, crt_line);
#endif
		sscanf(crt_line, "%s", &crt_syllable);
		++i;
		if (crt_syllable[0] == ';')
			{
#ifdef astDEBUG
		printf("   This line seems to be a comment.  Ignoring the rest of the line.");
#endif
			}
		else if (!strcmp(crt_syllable, ".word"))
			{
#ifdef astDEBUG
		printf("   The beginning of this line is OK!  Saving it in the const.txt file.");
#endif
		fprintf(out2_fname, "%3u   %s", asf_line_number, crt_line);
			}
		else if (!strcmp(crt_syllable, ".endconstants;"))
			{
#ifdef astDEBUG
		printf("   Reached the end of the .constants segment on line %3u.", asf_line_number);
#endif
			}
		else
			{
		printf("   Syntax Error in line %3u - expecting .word or ;", asf_line_number);
			}
	
	}/*End of the fourth while loop*/
/*---------------------------------------------------------------------------*/
/* Read the next lines; expect more comments or the beginning of the .code segment */	
/*---------------------------------------------------------------------------*/
	i = 0;
	while ((strcmp(crt_syllable, ".code;")) && (i != 20))
		{
		fgets(crt_line, 81, in1_fname);
		++asf_line_number;
#ifdef astDEBUG
		printf("\nParsing line %3u: %s", asf_line_number, crt_line);
#endif
		sscanf(crt_line, "%s", &crt_syllable);
		++i;
		if (crt_syllable[0] == ';')
			{
#ifdef astDEBUG
		printf("   This line seems to be a comment.  Ignoring the rest of the line.");
#endif
			}
		else if (!strcmp(crt_syllable, ".code;"))
			{
#ifdef astDEBUG
		printf("   Reached the beginning of the .code segment on line %3u.", asf_line_number);
#endif
			}
		else
			{
		printf("   Syntax Error in line %3u - expecting .code;", asf_line_number);
			}
	}/*End of fifth while loop*/
/*---------------------------------------------------------------------------*/
/* Read the next lines; expect more comments, instruction mnemonics,
 or the end of the .code segment.  For debugging purposes limit this section to 100 lines. */
/*---------------------------------------------------------------------------*/
	i = 0;
/*---------------------------------------------------------------------------*/
/*While the .endcode keyboard has not been read AND 1000 lines of assembly
have not been read AND the EOF has not been reached, continue ...
/*---------------------------------------------------------------------------*/
	while ((strcmp(crt_syllable, ".endcode;")) && (i != 1000) && EOF)
		{
/*---------------------------------------------------------------------------*/
/*Read the next line - maximum 80 characters plus the EOF character.
/*---------------------------------------------------------------------------*/
		fgets(crt_line, 81, in1_fname);
		++asf_line_number;
#ifdef astDEBUG
		printf("\nParsing line %3u: %s", asf_line_number, crt_line);
#endif
		sscanf(crt_line, "%s %s", &crt_syllable, &nxt_syllable);
		++i; match = 0; j = 0;
/*---------------------------------------------------------------------------*/
/*Check to see if current syllable is a valid instruction mnemonic; if yes,
save the line in the code.txt file.*/
/*---------------------------------------------------------------------------*/
		while ( j < 31 ) 
			{
				if (strcmp(crt_syllable, crt_im[j]) == 0)
				{
#ifdef astDEBUG
	printf("   The beginning of this line is OK!  Saving it in the code.txt file.");
#endif
	fprintf(out3_fname, "%3u   %s", asf_line_number, crt_line);
	match = 1;
				}
			++j;
			}/*End of inner while loop*/
/*---------------------------------------------------------------------------*/
/*Check to see if the line starts with a label followed by a valid 
instruction mnemonic*/
/*---------------------------------------------------------------------------*/
		k = 0;
		if (crt_syllable[0] == '@')
			{
			while ( k < 31 ) 
				{
				if (strcmp(nxt_syllable, crt_im[k]) == 0)
					{
#ifdef astDEBUG
	printf("   The beginning of this line is OK!  Saving it in the code.txt file.");
#endif
	fprintf(out3_fname, "%3u   %s", asf_line_number, crt_line);
	match = 1;
					}
				++k;		
			}/*End of second inner while loop*/
		}/*End of if construct*/
/*---------------------------------------------------------------------------*/
/*Check to see if line is a comment - ignore it.
/*---------------------------------------------------------------------------*/
		if (crt_syllable[0] == ';')
			{
#ifdef astDEBUG
		printf("   This line seems to be a comment.  Ignoring the rest of the line.");
#endif
			}
		else if (!strcmp(crt_syllable, ".endcode;"))
			{
#ifdef astDEBUG
		printf("   Reached the end of the .code segment on line %3u.", asf_line_number);
#endif
			}
		else if (match != 1)
			{
		printf("   Syntax Error in line %3u - expecting instruction mnemonic, \
		<.label:>, <.endcode;>, or <;>", asf_line_number);
			}
			
			
/*---------------------------------------------------------------------------*/
/*Translate the tensor support matrix multiplication
/*---------------------------------------------------------------------------*/
		if (strcmp(crt_syllable, "tensorMult") == 0)
			{
#ifdef astDEBUG
		printf("   Unpacking Tensor System supported Matrix Multiplication");
#endif
			match = 1;

			sscanf(crt_line, "%s %s %s %s %s %s %s %s", &crt_syllable, &addr_A, &row_A, &col_A, &addr_B, &row_B, &col_B, &relu);

			//transfer A
			fprintf(out3_fname, "%3u   		CFGD 	R2, M[R0, 0x0];\n", asf_line_number); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R1, M[R0, %s];\n", asf_line_number, row_A); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R0, M[R0, %s];\n", asf_line_number, col_A); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R4, M[R0, %s];\n", asf_line_number, addr_A); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R3, M[R0, 0x1];\n", asf_line_number); asf_line_number++;
			
			fprintf(out3_fname, "%3u   		NOP	;\n", asf_line_number); asf_line_number++;
			
			//transfer B
			fprintf(out3_fname, "%3u   		CFGD 	R2, M[R0, 0x1];\n", asf_line_number); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R1, M[R0, %s];\n", asf_line_number, row_B); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R0, M[R0, %s];\n", asf_line_number, col_B); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R4, M[R0, %s];\n", asf_line_number, addr_B); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R3, M[R0, 0x1];\n", asf_line_number); asf_line_number++;
			
			fprintf(out3_fname, "%3u 		NOP	;\n", asf_line_number, task_names[index]); asf_line_number++;
			
			if(relu[0] == '1')
			{
				fprintf(out3_fname, "%3u		SMXU 	R0, R1;\n", asf_line_number); asf_line_number++;
			}
			else
			{
				fprintf(out3_fname, "%3u		SMXU 	R0, R0;\n", asf_line_number); asf_line_number++;
			}
			
		
		}
		
/*---------------------------------------------------------------------------*/
/*Translate the dma transfer
/*---------------------------------------------------------------------------*/
		if (strcmp(crt_syllable, "dmaTransfer") == 0)
			{
#ifdef astDEBUG
		printf("   Unpacking DMA initiated Matrix Transfer");
#endif
			match = 1;

			sscanf(crt_line, "%s %s %s %s %s %s %s", &crt_syllable, &nxt_syllable, &reg1, &addr_A, &row_A, &col_A, &row_skip);

			//determine fifo source/destination
			if(strcmp(nxt_syllable, "A") == 0)
			{
				fprintf(out3_fname, "%3u   		CFGD 	R2, M[R0, 0x0];\n", asf_line_number); asf_line_number++;
			}
			else if(strcmp(nxt_syllable, "B") == 0)
			{
				fprintf(out3_fname, "%3u   		CFGD 	R2, M[R0, 0x1];\n", asf_line_number); asf_line_number++;
			}
			else if(strcmp(nxt_syllable, "X") == 0)
			{
				fprintf(out3_fname, "%3u   		CFGD 	R2, M[R0, 0x2];\n", asf_line_number); asf_line_number++;
			}
			else if(strcmp(nxt_syllable, "Q") == 0)
			{
				fprintf(out3_fname, "%3u   		CFGD 	R2, M[R0, 0x3];\n", asf_line_number); asf_line_number++;
			}

			//configure rest of the registers
			fprintf(out3_fname, "%3u   		CFGD 	R1, M[R0, %s];\n", asf_line_number, row_A); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R0, M[R0, %s];\n", asf_line_number, col_A); asf_line_number++;
			
			if(strcmp(reg1, "R0") == 0)
			{
				fprintf(out3_fname, "%3u   		CFGD 	R4, M[R0, %s];\n", asf_line_number, addr_A); asf_line_number++;
			}
			else
			{
				fprintf(out3_fname, "%3u   		CFGD 	R4, M[%s, %s];\n",  asf_line_number, reg1, addr_A); asf_line_number++;
			}
			
			fprintf(out3_fname, "%3u   		CFGD 	R6, M[R0, %s];\n", asf_line_number, row_skip); asf_line_number++;
			fprintf(out3_fname, "%3u   		CFGD 	R3, M[R0, 0x1];\n", asf_line_number); asf_line_number++;
			fprintf(out3_fname, "%3u   		NOP	;\n", asf_line_number); asf_line_number++;
		
		}
		
		
		
			
			
	}/*End of sixth while loop*/
	



	
	
	
/*---------------------------------------------------------------------------*/
/*Append the code with the tasks included from the directives
/*---------------------------------------------------------------------------*/
	
	if(task_counter > 0)
	{		
		for(index=0; index<task_counter; index++)
		{
			strncpy(name, task_names[index], 20);
			strcat(name, ".txt");
			printf("   Opening file %s.", name);
			task = fopen(name, "r");
			
			fprintf(out3_fname, "%3u @%s		NOP	;\n", asf_line_number, task_names[index]);
			asf_line_number++;
			
			fgets(crt_line, 81, task);
			sscanf(crt_line, "%s", &crt_syllable);
			while(strcmp(crt_syllable, "EOT") != 0)
			{
				fprintf(out3_fname, "%3u   %s", asf_line_number, crt_line);
				//printf("Printing %s at %3u.\n", task_names[index], asf_line_number);
				fgets(crt_line, 81, task);
				sscanf(crt_line, "%s", &crt_syllable);
				asf_line_number++;
			}
	
			fprintf(out3_fname, "%3u			RET	;\n", asf_line_number); asf_line_number++;
			
			fclose(task);
		}
	}

	
/*---------------------------------------------------------------------------*/
/*Append the code with the interrupts
/*---------------------------------------------------------------------------*/
	
	for(index=0; index<intr_counter; index++)
	{		
		fprintf(out3_fname, "%3u 	interrupt	%s	%s;\n", asf_line_number, intr_names[index], intr_jumps[index]);
		asf_line_number++;
	}
	
	fprintf(out3_fname, "\n");
	
	
	
		
/*---------------------------------------------------------------------------*/
/*Creating Data file with links
/*---------------------------------------------------------------------------*/
	
	if(mif_counter > 0)
	{
		//crt_line = 0;
		asf_line_number = 0;
		int q;
		crt_line[0] = 0;
			
		FILE* data_file = fopen("nndata.mif", "w");
		FILE* mif;

		fprintf(data_file, "--Data Memory Initialization File \
		\n--Created by ast_ai_asm \
		\nWIDTH = 16; \
		\nDEPTH = 65536; \
		\nADDRESS_RADIX = HEX;	%% Can be HEX, BIN or DEC %% \
		\nDATA_RADIX = HEX;	%% Can be HEX, BIN or DEC %% \
		\n\nCONTENT BEGIN\n");
		
		fprintf(data_file, "[ 0 .. FFFF ] : 0000000000000000; %% Initialize full memory with 0 %% \n");	
		
		for(index=0; index<mif_counter; index++)
		{
			strncpy(name, mif_names[index], 30);
			strcat(name, ".mif");
			printf("   Opening file %s.\r\n", name);
			mif = fopen(name, "r");
			
			for(q=0; q<7; q++){ fgets(crt_line, 81, mif); }
			
			//fgets(crt_line, 81, task);
			//sscanf(crt_line, "%s", &crt_syllable);
			
			while(1)
			{
				fgets(crt_line, 81, mif);
				sscanf(crt_line, "%s %s %s", &crt_syllable, &nxt_syllable, &thr_syllable);
				if(strcmp(crt_syllable, "END;") == 0)
					break;
				fprintf(data_file, "%04x : %s\n", asf_line_number, thr_syllable);
				#ifdef astDEBUG
				printf("   Appending Data file with: %s\r\n", thr_syllable);
				#endif
				asf_line_number++;
			}

			fclose(mif);
		}
		
		fprintf(data_file, "END;");		
		
		fclose(data_file);
	}
	
	
	
	
	
	return;
}

