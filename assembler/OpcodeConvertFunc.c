#include "stdio.h"
#include "string.h"
#include "FuncDeclaration.h"


void opcodeConvert(char opcode[MAX_LINE], char opcodeHex[HEX_CODE]) {
	char inst[][6] = { "add" , "sub", "mac", "and", "or", "xor", "sll", "sra", "srl", "beq", "bne", "blt",
"bgt", "ble", "bge", "jal", "lw", "sw", "reti", "in", "out", "halt" };

	int opcodeCode=0;
	for (int i = 0; i <= 21; i++)
		if (strcmp(opcode, inst[i]) == 0)
			opcodeCode = i;

	if (opcodeCode < 16)
		sprintf_s(opcodeHex, 3, "0%x", opcodeCode); // convert to two  Hexadecimal digits
	else
		sprintf_s(opcodeHex, 3, "%x", opcodeCode);

}