/*===========================================================================*/
/* The step2_assembly subroutine checks for the correct structure and syntax
of every line of the assembly source code file and assembles the machine code 
in the *.mif output file.
(c) Dorin Patru September 2022 */
/*===========================================================================*/

#include "ast_asm.h" /* Contains stdio.lib and std.lib */
#include <string.h>
void step2_assembly(int1_fname, int2_fname, \
				int3_fname, out1_fname, crt_im, crt_opcode, \
				crt_ri, crt_rifv, crt_rj, crt_rjfv, crt_mri)
/*---------------------------------------------------------------------------*/
/* Parameter types declarations. */
/*---------------------------------------------------------------------------*/
FILE *int1_fname; FILE *int2_fname; FILE *int3_fname; FILE	*out1_fname;
	const char *crt_im[27]; const char *crt_opcode[27]; \
	const char *crt_ri[16]; const char *crt_rifv[16]; const char *crt_rj[16]; \
	const char *crt_rjfv[16]; const char *crt_mri[16];
	{
/*---------------------------------------------------------------------------*/
/* Local declarations:
/*---------------------------------------------------------------------------*/
	FILE	*prev_line;
	char	crt_line[81], crt_iw0[17], crt_char[6], crt_iw1_string[18];
	char	*endptr;
	int		crt_val, test, crt_mif_addrs = 0, crt_jca = 0, crt_iw1 = 0, crt_jao = 0;
/*---------------------------------------------------------------------------*/
/*Temporary storage for the syllables currently expected and analyzed*/
/*---------------------------------------------------------------------------*/
	char	first_syllable[20], second_syllable[20], \
			third_syllable[20], fourth_syllable[20], fifth_syllable[20]; 
	int		Aeff = 0, code_line_number = 0, asf_line_number = 0;
	int	i=0, j=0, k=0, match1 = 0, match2 = 0, match3 = 0, match4 = 0;
#define astDEBUG = 1;
#define ErrorMnemonic	printf("\nError: Unexpected mnemonic in line %3u", asf_line_number);
#define ErrorRifield	printf("\nError: Unexpected Ri field in line %3u", asf_line_number);
#define ErrorRjfieldConst	printf("\nError: Unexpected Rj field constant in line %3u", asf_line_number);
#define ErrorRjfield	printf("\nError: Unexpected Rj field in line %3u", asf_line_number);
#define ErrorJCAfield	printf("\nError: Unexpected JCA field in line %3u", asf_line_number);
#define Errormrifield	printf("\nError: Unexpected mri field in line %3u", asf_line_number);
#define ErrorCondField	printf("\nError: Unexpected Jump Condition field in line %3u", asf_line_number);
/*---------------------------------------------------------------------------*/
/*The "symbol table" for the JUMP and CALL addresses*/
/*---------------------------------------------------------------------------*/
	struct {char jca_label[20]; int jca_num;} jca[10];	
	struct {char jf_label[20]; fpos_t jf_pos; int jf_line;} jf[10];
	int jf_index = 0;		
/*---------------------------------------------------------------------------*/
/* Print the header of the ast.mif file */
/*---------------------------------------------------------------------------*/
	fprintf(out1_fname, "--Program Memory Initialization File \
	\n--Created by ast_dcs_asm \
	\nWIDTH = 14; \
	\nDEPTH = 1024; \
	\nADDRESS_RADIX = HEX;	%% Can be HEX, BIN or DEC %% \
	\nDATA_RADIX = BIN;	%% Can be HEX, BIN or DEC %% \
	\n\nCONTENT BEGIN\n \
	\n--A> : <-OC-><Ri><Rj>\n");
/*---------------------------------------------------------------------------*/
/* Read the code.txt file and assemble into *.mif*/
/*---------------------------------------------------------------------------*/
	while (crt_line[0] != '\n')
		{
/*---------------------------------------------------------------------------*/
/* Read the entire NEXT line from code.txt
/*---------------------------------------------------------------------------*/
		fgets(crt_line, 81, int1_fname); ++code_line_number;
		if (crt_line[0] == '\n') { printf("\nDone assembly!"); break; }
/*---------------------------------------------------------------------------*/
/* Debugging message:
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		test = strlen(crt_line); printf("\nThe length is:= %3u", test);
		printf("\n\nParsing code line %3u:\n %s\n", code_line_number, crt_line);
#endif
/*---------------------------------------------------------------------------*/
/* Initialize syllables to the N/A string
/*---------------------------------------------------------------------------*/
		strcpy(first_syllable, "N/A"); strcpy(second_syllable, "N/A");
		strcpy(third_syllable, "N/A"); strcpy(fourth_syllable, "N/A");
		strcpy(fifth_syllable, "N/A");
/*---------------------------------------------------------------------------*/
/* Split the current line into parts, i.e. SYLLABLES (Words)
/*---------------------------------------------------------------------------*/
		sscanf(crt_line, "%3u %s %s %s %s %s", &asf_line_number, &first_syllable, \
		&second_syllable, &third_syllable, &fourth_syllable, &fifth_syllable);
#ifdef astDEBUG
		printf("\n asf_line_number is := %3u", asf_line_number);
		printf("\n \t first_syllable is := %s", first_syllable);
		printf("\n \t \t second_syllable is := %s", second_syllable);
		printf("\n \t \t \t third_syllable is := %s", third_syllable);
		printf("\n \t \t \t \t fourth_syllable is := %s", fourth_syllable);
		printf("\n \t \t \t \t \t fifth_syllable is := %s\n", fifth_syllable);
#endif
	match1 = 0;	match2 = 0; match3 = 0;	match4 = 0;	//++i;
/*===========================================================================
JUMP Label Check and Update
===========================================================================*/
	if (first_syllable[0] == '@')
		{
			strcat(first_syllable, ";");
/*---------------------------------------------------------------------------*/
/* Store the current label and associated mif file address
/*---------------------------------------------------------------------------*/
			strcpy(jca[crt_iw1].jca_label, first_syllable);
			jca[crt_iw1].jca_num = crt_mif_addrs;
			++crt_iw1;
/*---------------------------------------------------------------------------*/
/* Shift syllables to account for the label
/*---------------------------------------------------------------------------*/
	
			fpos_t ret_pos;
			int loop_index = 0;
			for(; loop_index < jf_index; loop_index++)
			{
				if (strcmp(first_syllable, jf[k].jf_label) == 0);
				{
					//crt_jao = (crt_mif_addrs) - jf[k].jf_line;
					//ast_int2binstr(crt_jao, 14, crt_char);
					ast_int2binstr(crt_mif_addrs, 14, crt_char);
					
					fgetpos(out1_fname, &ret_pos);
					fsetpos(out1_fname, &(jf[k].jf_pos));
					
					fprintf(out1_fname, "%04x : %s; %% %s %%", \
					jf[k].jf_line, crt_char, first_syllable);//jf[k].jf_label);
					
					fsetpos(out1_fname, &ret_pos);
					
					//break;
				}	
			}			
			
			
			strcpy(first_syllable, second_syllable);
			strcpy(second_syllable, third_syllable);
			strcpy(third_syllable, fourth_syllable);
			strcpy(fourth_syllable, fifth_syllable);
		}
/*===========================================================================
Assemble 2-Operand instructions: ADD, SUB, AND, OR
===========================================================================*/
	i = 2;
	while(i != 19)	{
		if (strcmp(first_syllable, crt_im[i]) == 0)
/*---------------------------------------------------------------------------*/
/* If the mnemonic matches concatenate the OpCode field to the IW.
/*---------------------------------------------------------------------------*/
		{ strcpy(crt_iw0, crt_opcode[i]); match1 = 1; k = 0;
/*---------------------------------------------------------------------------*/
/* Determine Ri and concatenate to the IW, else exit with an error.
/*---------------------------------------------------------------------------*/
			while (k < 27 && match2 == 0)	{
				if (strcmp(second_syllable, crt_ri[k]) == 0)
				{ strcat(crt_iw0, crt_rifv[k]); match2 = 1; } ++k; } k = 0;
			if (match2 == 0) { ErrorRifield; break; } 
/*---------------------------------------------------------------------------*/
/* Determine Rj and concatenate to the IW, else exit with an error.
/*---------------------------------------------------------------------------*/
			while (k < 27 && match3 == 0) {
				if (strcmp(third_syllable, crt_rj[k]) == 0)
				{ strcat(crt_iw0, crt_rjfv[k]);	match3 = 1; } ++k; }
			if (match3 == 0) { ErrorRjfield; break; }
/*---------------------------------------------------------------------------*/
/* Printf for debugging purposes.
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		printf("%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
#endif
/*---------------------------------------------------------------------------*/
/* FPrintf the IW to the *.mif file.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, "%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
			++crt_mif_addrs;	}	
/*---------------------------------------------------------------------------*/
/* Manipulate i to skip over other OpCodes
/*---------------------------------------------------------------------------*/
	if (i == 3) { i = 5; } else if ( i == 6) { i = 10;} else if(i == 11){ i = 14;}
	else { ++i; }	}
/*===========================================================================
Assemble 1-Operand instructions: ADDC, SUBC, SRA, RRC, SMXU
===========================================================================*/
	i = 7;
	while(i != 29)	{		
	if (strcmp(first_syllable, crt_im[i]) == 0)
/*---------------------------------------------------------------------------*/
/* If the mnemonic matches concatenate the OpCode field to the IW.
/*---------------------------------------------------------------------------*/
		{ strcpy(crt_iw0, crt_opcode[i]); match1 = 1; k = 0; 
/*---------------------------------------------------------------------------*/
/* Determine Ri and concatenate to the IW, else exit with an error.
/*---------------------------------------------------------------------------*/
			while (k < 27 && match2 == 0)
			{ if (strcmp(second_syllable, crt_ri[k]) == 0)
				{ strcat(crt_iw0, crt_rifv[k]); match2 = 1; } ++k; }
			if (match2 == 0) { ErrorRifield; } k = 0;
/*---------------------------------------------------------------------------*/
/* Determine the value of K and concatenate to IW: read in ASCII characters,
 convert to long integer with strtol, then convert int to binary string for 
 the *mif file, and concatenate to IW; else exit with an error.
/*---------------------------------------------------------------------------*/
			crt_val = strtol(third_syllable, &endptr, 16);
			if (crt_val > 15) { ErrorRjfieldConst; break; } k = 0;
			ast_int2binstr(crt_val, 4, crt_char); 
			strcat(crt_iw0, crt_char); 
/*---------------------------------------------------------------------------*/
/* Printf for debugging purposes.
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		printf("%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
#endif
/*---------------------------------------------------------------------------*/
/* FPrintf the IW to the *.mif file.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, "%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
		++crt_mif_addrs;	}
/*---------------------------------------------------------------------------*/
/* Manipulate i to skip over other OpCodes
/*---------------------------------------------------------------------------*/
	if (i == 8) { i = 12; } else if (i == 13){i = 19;} else if (i == 24){i = 28;}
	else { ++i; }	}
/*===========================================================================
Assemble LD and ST, CFGD
===========================================================================*/
	i = 0;
	while(i != 28)	{ 
	if (strcmp(first_syllable, crt_im[i]) == 0)
/*---------------------------------------------------------------------------*/
/* If the mnemonic matches concatenate the OpCode field to the IW.
/*---------------------------------------------------------------------------*/
		{ strcpy(crt_iw0, crt_opcode[i]); match1 = 1; k = 0;
/*---------------------------------------------------------------------------*/
/* Determine Ri and concatenate to the IW, else exit with an error.
/*---------------------------------------------------------------------------*/
			while (k < 16 && match3 == 0)
			{ if (strcmp(third_syllable, crt_mri[k]) == 0)
				{ strcat(crt_iw0, crt_rifv[k]); match3 = 1;	break; } ++k; }
			if (match3 == 0) { Errormrifield; break; } k = 0;
/*---------------------------------------------------------------------------*/
/* Determine Rj and concatenate to the IW, else exit with an error.
/*---------------------------------------------------------------------------*/
			while (k < 16 && match2 == 0)
			{ if (strcmp(second_syllable, crt_ri[k]) == 0)
				{ strcat(crt_iw0, crt_rifv[k]); match2 = 1; } ++k; }
			if (match2 == 0) { ErrorRifield; break; } k = 0;
/*---------------------------------------------------------------------------*/
/* Printf for debugging purposes.
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		printf("%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
#endif
/*---------------------------------------------------------------------------*/
/* FPrintf the IW to the *.mif file.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, "%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
		++crt_mif_addrs;
/*---------------------------------------------------------------------------*/
/* Determine the value of the address offset and insert into *.mif file.
/*---------------------------------------------------------------------------*/
			k = 0;
			crt_val = strtol(fourth_syllable, &endptr, 16);
			ast_int2binstr(crt_val, 14, crt_char);
/*---------------------------------------------------------------------------*/
/* Printf for debugging purposes.
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		printf("%04x : %s; %% %s %% \n", \
	crt_mif_addrs, crt_char, fourth_syllable);
#endif
/*---------------------------------------------------------------------------*/
/* FPrintf the IW to the *.mif file.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, "%04x : %s; %% %s %% \n", \
	crt_mif_addrs, crt_char, fourth_syllable);
			++crt_mif_addrs;	} 
			
			if (i == 1) { i = 27; } 
	else { ++i; } 	}
/*===========================================================================
Assemble JMP U - unconditional, 
		C1 - if C=1, N1 - if N=1, V1 - if V=1, Z1 - if Z=1
		C0 - if C=0, N0 - if N=0, V0 - if V=0, Z0 - if Z=0
===========================================================================*/
		i = 4;
		while(i != 27)	{
		if (strcmp(first_syllable, crt_im[i]) == 0)
/*---------------------------------------------------------------------------*/
/* If the mnemonic matches concatenate the OpCode field to the IW.
/*---------------------------------------------------------------------------*/
		{ strcpy(crt_iw0, crt_opcode[i]); match1 = 1; k = 0;
/*---------------------------------------------------------------------------*/
/* Determine the kind of JUMP and complete the IW.
/*---------------------------------------------------------------------------*/
		if(i == 4)
		{
			if 		(second_syllable[0] == 'U') 
						{ strcat(crt_iw0, "00000000"); match2 = 1;}
			else if (second_syllable[0] == 'C' && second_syllable[1] == '1') 
						{ strcat(crt_iw0, "00001000"); match2 = 1;}
			else if (second_syllable[0] == 'N' && second_syllable[1] == '1') 
						{ strcat(crt_iw0, "00000100"); match2 = 1;}
			else if (second_syllable[0] == 'V' && second_syllable[1] == '1') 
						{ strcat(crt_iw0, "00000010"); match2 = 1;}
			else if (second_syllable[0] == 'Z' && second_syllable[1] == '1') 
						{ strcat(crt_iw0, "00000001"); match2 = 1;}
			else if (second_syllable[0] == 'C' && second_syllable[1] == '0') 
						{ strcat(crt_iw0, "00000111"); match2 = 1;}
			else if (second_syllable[0] == 'N' && second_syllable[1] == '0') 
						{ strcat(crt_iw0, "00001011"); match2 = 1;}
			else if (second_syllable[0] == 'V' && second_syllable[1] == '0') 
						{ strcat(crt_iw0, "00001101"); match2 = 1;}
			else if (second_syllable[0] == 'Z' && second_syllable[1] == '0') 
						{ strcat(crt_iw0, "00001110"); match2 = 1;}
			else	{ ErrorCondField; break; }
		}	
		else if(i == 25)
		{
			strcat(crt_iw0, "00000000");
		}
		else if(i == 26)
		{
			strcat(crt_iw0, "00000000");
			
		}
			
/*---------------------------------------------------------------------------*/
/* Printf for debugging purposes.
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		printf("%04x : %s; %% %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable);
#endif
/*---------------------------------------------------------------------------*/
/* FPrintf the IW to the *.mif file.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, "%04x : %s; %% %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable);
		++crt_mif_addrs;
		
		if(i == 26){ break; }
/*---------------------------------------------------------------------------*/
/* Deteremine the jump address ABSOLUTE
/*---------------------------------------------------------------------------*/
	if (third_syllable[0] != '@') { ErrorJCAfield; break; }
		while (k < 10)
		{ if (strcmp(third_syllable, jca[k].jca_label) == 0)
			{ 
			//crt_jao = jca[k].jca_num - (crt_mif_addrs);
			//ast_int2binstr(crt_jao, 14, crt_char); 
			ast_int2binstr(jca[k].jca_num, 14, crt_char); 
			
			match3 = 1; break; 
			} ++k;	
		}
		if (match3 == 0) { 
		
			fgetpos(out1_fname, &(jf[jf_index].jf_pos));
			/*int str_index = 0;
			for(; str_index < 20; str_index++ ) 
			{
				jf[jf_index].jf_label[str_index] = jca[k].jca_label[str_index];
			}*/
			strcpy(jf[jf_index].jf_label, jca[k].jca_label);
			jf[jf_index].jf_line = crt_mif_addrs;
			jf_index++;
		
			printf("\n this is a forward jump \n"); 
			//strcpy(crt_char, jca[k].jca_label); 
			ast_int2binstr(crt_mif_addrs, 14, crt_char); 
			}
/*---------------------------------------------------------------------------*/
/* Printf for debugging purposes.
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		printf("%04x : %s; %% %s %% \n", \
	crt_mif_addrs, crt_char, third_syllable);
#endif
/*---------------------------------------------------------------------------*/
/* FPrintf the IW to the *.mif file.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, "%04x : %s; %% %s %% \n", \
	crt_mif_addrs, crt_char, third_syllable);
		++crt_mif_addrs;
/* Implement here the JUMP forward */
		}
		
		if (i == 4) { i = 25; } 
	else { ++i; }	}
/*===========================================================================
Assemble NOT
===========================================================================*/
	i = 9;
	if (strcmp(first_syllable, crt_im[i]) == 0)
/*---------------------------------------------------------------------------*/
/* If the mnemonic matches concatenate the OpCode field to the IW.
/*---------------------------------------------------------------------------*/
		{ strcpy(crt_iw0, crt_opcode[i]); match1 = 1; k = 0; 
/*---------------------------------------------------------------------------*/
/* Determine Ri and concatenate to the IW, else exit with an error.
/*---------------------------------------------------------------------------*/
			while (k < 30 && match2 == 0)
			{if (strcmp(second_syllable, crt_rj[k]) == 0) /* Use crt_rj for comparison because of the ; */
				{ strcat(crt_iw0, crt_rifv[k]); match2 = 1; } ++k; }
			if (match2 == 0) { ErrorRifield; } k = 0;
/*---------------------------------------------------------------------------*/
/* Concatenate to IW[5:0] zeros
/*---------------------------------------------------------------------------*/
			crt_val = 0;
			ast_int2binstr(crt_val, 4, crt_char); 
			strcat(crt_iw0, crt_char); 
/*---------------------------------------------------------------------------*/
/* Printf for debugging purposes.
/*---------------------------------------------------------------------------*/
#ifdef astDEBUG
		printf("%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
#endif
/*---------------------------------------------------------------------------*/
/* FPrintf the IW to the *.mif file.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, "%04x : %s; %% %s %s %s %% \n", \
	crt_mif_addrs, crt_iw0, first_syllable, second_syllable, third_syllable);
		++crt_mif_addrs;	}
		
	
/*===========================================================================
Assemble NOP
===========================================================================*/	
	
	i = 29;
	if (strcmp(first_syllable, crt_im[i]) == 0)
	
		{ strcpy(crt_iw0, crt_opcode[i]); match1 = 1; k = 0;
		
		strcat(crt_iw0, "00000000");
		
		fprintf(out1_fname, "%04x : %s; %% %s %% \n", \
		crt_mif_addrs, crt_iw0, first_syllable);
		++crt_mif_addrs;	}
		
		
		
		
		

		
	
			if (match1 == 0) { ErrorMnemonic; break; }	
		}	
/*---------------------------------------------------------------------------*/
/* Initialize the remaining locations in the *.mif file to 0.
/*---------------------------------------------------------------------------*/
		fprintf(out1_fname, \
"[ %04x .. 3FF ] : 00000000; %% Fill the remaining locations with 0 %% \n END; \n", crt_mif_addrs);	
	return;
}	

