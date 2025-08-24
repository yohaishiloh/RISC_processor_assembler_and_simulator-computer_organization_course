#include "stdio.h"
#include "string.h"
#include "FuncDeclaration.h"


void regCodeConvert(char reg[MAX_LINE], char regcodeHex[HEX_CODE]) {

	char inst[][6] = { "$zero" , "$imm1", "$imm2", "$v0", "$a0", "$a1","$a2", "$t0", "$t1", "$t2", "$s0", "$s1", "$s2",
"$gp", "$sp", "$ra" };

	int regCode = 0;
	for (int i = 0; i <= 15; i++)
		if (strcmp(reg, inst[i]) == 0)
			regCode = i;
	sprintf_s(regcodeHex, 3, "%x", regCode);
}