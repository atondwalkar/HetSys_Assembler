/*===========================================================================*/
/*Contains arrays of strings declarations and definitions.*/
/*===========================================================================*/
/*The instruction mnemonic array of strings declaration*/
/*---------------------------------------------------------------------------*/
	const	char	*im[31];
/*---------------------------------------------------------------------------*/
/*The instruction mnemonic array of strings assignments*/
/*---------------------------------------------------------------------------*/
	im[0] = "LD";	im[1] = "ST"; 	im[2] = "CPY";	im[3] = "SWAP";
	im[4] = "JMP";	im[5] = "ADD"; 	im[6] = "SUB";	im[7] = "ADDC";
	im[8] = "SUBC";	im[9] = "NOT";	im[10] = "AND";	im[11] = "OR";	
	im[12] = "SRA";	im[13] = "SRL"; im[14] = "VADD"; im[15] = "VSUB"; //im[14] = "IN";	im[15] = "OUT"; 
	im[16] = "MUL";	im[17] = "DIV";	im[18] = "XOR";	im[19] = "ROTL";
	im[20] = "ROTR";	im[21] = "RLZ";	im[22] = "RLN";	im[23] = "RRC";
	im[24] = "RRV";	im[25] = "CALL";	im[26] = "RET"; 
	im[27] = "CFGD"; im[28] = "SMXU"; im[29] = "NOP", im[30] = "CMXU";
/*---------------------------------------------------------------------------*/
/*The Ri-field string array */
/*---------------------------------------------------------------------------*/
	const	char	*Ri[16];
	Ri[0] = "R0,"; Ri[1] = "R1,"; Ri[2] = "R2,"; Ri[3] = "R3,";
	Ri[4] = "R4,"; Ri[5] = "R5,"; Ri[6] = "R6,"; Ri[7] = "R7,";
	Ri[8] = "R8,"; Ri[9] = "R9,"; Ri[10] = "R10,"; Ri[11] = "R11,";
	Ri[12] = "R12,"; Ri[13] = "R13,"; Ri[14] = "R14,"; Ri[15] = "R15,";
/*---------------------------------------------------------------------------*/
/*The Ri-field-value string array */
/*---------------------------------------------------------------------------*/
	const	char	*RiFieldValue[16];
	RiFieldValue[0] = "0000"; RiFieldValue[1] = "0001"; 
	RiFieldValue[2] = "0010"; RiFieldValue[3] = "0011";
	RiFieldValue[4] = "0100"; RiFieldValue[5] = "0101"; 
	RiFieldValue[6] = "0110"; RiFieldValue[7] = "0111";
	RiFieldValue[8] = "1000"; RiFieldValue[9] = "1001"; 
	RiFieldValue[10] = "1010"; RiFieldValue[11] = "1011";
	RiFieldValue[12] = "1100"; RiFieldValue[13] = "1101"; 
	RiFieldValue[14] = "1110"; RiFieldValue[15] = "1111";
/*---------------------------------------------------------------------------*/
/*The Rj-field string array */
/*---------------------------------------------------------------------------*/
	const	char	*Rj[16];
	Rj[0] = "R0;"; Rj[1] = "R1;"; Rj[2] = "R2;"; Rj[3] = "R3;";
	Rj[4] = "R4;"; Rj[5] = "R5;"; Rj[6] = "R6;"; Rj[7] = "R7;";
	Rj[8] = "R8;"; Rj[9] = "R9;"; Rj[10] = "R10;"; Rj[11] = "R11;";
	Rj[12] = "R12;"; Rj[13] = "R13;"; Rj[14] = "R14;"; Rj[15] = "R15;";
/*---------------------------------------------------------------------------*/
/*The Rj-field-value string array */
/*---------------------------------------------------------------------------*/
	const	char	*RjFieldValue[16];
	RjFieldValue[0] = "0000"; RjFieldValue[1] = "0001"; 
	RjFieldValue[2] = "0010"; RjFieldValue[3] = "0011";
	RjFieldValue[4] = "0100"; RjFieldValue[5] = "0101"; 
	RjFieldValue[6] = "0110"; RjFieldValue[7] = "0111";
	RjFieldValue[8] = "1000"; RjFieldValue[9] = "1001"; 
	RjFieldValue[10] = "1010"; RjFieldValue[11] = "1011";
	RjFieldValue[12] = "1100"; RjFieldValue[13] = "1101"; 
	RjFieldValue[14] = "1110"; RjFieldValue[15] = "1111";
/*---------------------------------------------------------------------------*/
/*The mnemonic opcode string array */
/*---------------------------------------------------------------------------*/
	const	char	*OpCode[31];
OpCode[0] = "00000000";	OpCode[1] = "00000001"; OpCode[2] = "00000010";	OpCode[3] = "00000011";
OpCode[4] = "00000100";	OpCode[5] = "00000101"; OpCode[6] = "00000110";	OpCode[7] = "00000111";
OpCode[8] = "00001000";	OpCode[9] = "00001001";	OpCode[10] = "00001010"; OpCode[11] = "00001011";
OpCode[12] = "00001100"; OpCode[13] = "00001101"; OpCode[14] = "00001110"; OpCode[15] = "00001111"; 
OpCode[16] = "00010000";	OpCode[17] = "00010001";	OpCode[18] = "00010010"; OpCode[19] = "00010011";
OpCode[20] = "00010100"; OpCode[21] = "00010101"; OpCode[22] = "00010110"; OpCode[23] = "00010111"; 
OpCode[24] = "00011000"; OpCode[25] = "00011001"; OpCode[26] = "00011010"; 
OpCode[27] = "00011011"; OpCode[28] = "00011100"; OpCode[29] = "00111110"; OpCode [30] = "00011101";
/*---------------------------------------------------------------------------*/
/* the M[Ri-field string array */
/*---------------------------------------------------------------------------*/
	const	char	*mri[16];
	mri[0] = "M[R0,"; mri[1] = "M[R1,"; mri[2] = "M[R2,"; mri[3] = "M[R3,";
	mri[4] = "M[R4,"; mri[5] = "M[R5,"; mri[6] = "M[R6,"; mri[7] = "M[R7,";
	mri[8] = "M[R8,"; mri[9] = "M[R9,"; mri[10] = "M[R10,"; mri[11] = "M[R11,";
	mri[12] = "M[R12,"; mri[13] = "M[R13,"; mri[14] = "M[R14,"; mri[15] = "M[R15,";
	

