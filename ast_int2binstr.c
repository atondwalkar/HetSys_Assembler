#include <stdio.h>
#include <stdlib.h>

void ast_int2binstr(int crt_int, int str_len, char *ret_str)
{
	int		i = 0, j = 0, temp;
	
   	for ( i = (str_len - 1) ; i >= 0 ; i-- )
	{
      temp = crt_int >> i;
 
      if ( temp & 1 )
         *(ret_str+j) = 49; /*The ASCII value of 1*/
      else
         *(ret_str+j) = 48;  /*The ASCII value of 0*/
      ++j;
   }
   *(ret_str+str_len) = '\0'; /*Making sure the string is ended with the \0 character*/
   return;
}
