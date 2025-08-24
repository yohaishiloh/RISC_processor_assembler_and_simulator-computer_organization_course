#include "stdio.h"
#include "string.h"
#include "FuncDeclaration.h"


void linetohexconvert(Line* line) {

	char opcodeHexCode[3];
	char rdCode[3];
	char rsCode[3];
	char rtCode[3];
	char rmCode[3];
	char imm1Code[5];
	char imm2Code[5];

	opcodeConvert(line->opcode, opcodeHexCode);

	regCodeConvert(line->rd, rdCode);
	regCodeConvert(line->rs, rsCode);
	regCodeConvert(line->rt, rtCode);
	regCodeConvert(line->rm, rmCode);

	immCodeConvert(line->imm1, imm1Code);
	immCodeConvert(line->imm2, imm2Code);

	strcpy_s(line->opcode,3, opcodeHexCode);
	strcpy_s(line->rd,3, rdCode);
	strcpy_s(line->rs,3, rsCode);
	strcpy_s(line->rt,3, rtCode);
	strcpy_s(line->rm,3, rmCode);
	strcpy_s(line->imm1,5,imm1Code);
	strcpy_s(line->imm2,5, imm2Code);

	return;
}
