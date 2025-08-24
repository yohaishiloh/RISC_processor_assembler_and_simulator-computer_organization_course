#include "stdio.h"
#include "string.h"
#include "FuncDeclaration.h"


void lineToCode(char inpt_line[MAX_LINE], Line* inst_line) { // inpt line - raw line from the file, inst_line - destination, saved by fields in struct

	char opcode[MAX_LINE] = { 0 }; 
	char rd[MAX_LINE] = { 0 };
	char rs[MAX_LINE] = { 0 };
	char rt[MAX_LINE] = { 0 };
	char rm[MAX_LINE] = { 0 };
	char imm1[MAX_LINE] = { 0 };
	char imm2[MAX_LINE] = { 0 };
	int i = 0;	
	int imm_len = 0;

	getWord(inpt_line, &i,opcode);

	getWord(inpt_line, &i, rd);
	getWord(inpt_line, &i, rs);
	getWord(inpt_line, &i, rt);
	getWord(inpt_line, &i, rm);


	getWord(inpt_line, &i, imm1);
	imm_len = strlen(imm1);
	if (imm1[imm_len - 1] == ":")
		imm1[imm_len - 1] = "\0";
	getWord(inpt_line, &i, imm2);
	imm_len = strlen(imm2);
	if (imm2[imm_len - 1] == ":")
		imm2[imm_len - 1] = "\0";
	
	line_init(inst_line, opcode, rd, rs, rt, rm, imm1, imm2);
}
