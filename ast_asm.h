#include <stdio.h>
#include <stdlib.h>

/*===========================================================================*/
/* IF astDEBUG != 0, code segments between #if astDEBUG and #endif will be
compiled.  If astDEBUG == 0 ==> not.  Useful to eliminate printf's used for 
debugging purposes in the final release version.*/
/*===========================================================================*/
/*===========================================================================*/
/* The ast_get_fname gets the assembly source file (asf) name, opens it,
checks if it exists, and returns the pointer to it. */
/*===========================================================================*/
FILE *ast_get_fname();
/*===========================================================================*/
/* The step1_syntax_check subroutine checks for the correct structure of the 
assembly source code file and for syntax errors at the beginning of each line 
of code */
/*===========================================================================*/
void step1_syntax_check(FILE *in1_fname, FILE *out1_fname, FILE *out2_fname, \
			FILE *out3_fname, const char *crt_im[30]);
/*===========================================================================*/
/* The step2_assembly subroutine assembles each instrcution into the machine 
language instruction word format */
/*===========================================================================*/
void step2_assembly(FILE *int1_fname, FILE *int2_fname, \
				FILE *int3_fname, FILE *out1_fname, const char *crt_im[30], \
				const char *crt_opcode[30], \
				const char *crt_ri[16], const char *crt_rifv[16], \
				const char *crt_rj[16], const char *crt_rjfv[16], \
				const char *crt_mri[16]);
void ast_int2binstr(int crt_int, int str_len, char *ret_str);


