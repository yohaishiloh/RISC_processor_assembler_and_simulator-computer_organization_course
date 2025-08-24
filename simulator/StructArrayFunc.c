#include "simulatorFunctions.h"
//Here we build the struct array that takes eace line from the imemin and seperate it to the opcode,rd,rs,rt,rm,imm1,imm2
//we get it in hexadecimal string and in decimal long
void structArrayCreator(long pc, char line[], instruction instruction[MAXLINES]) {
	
	char opcode[OPCODESIZE] = { 0 };
	char rd[RDSIZE] = { 0 };
	char rs[RSSIZE] = { 0 };
	char rt[RTSIZE] = { 0 };
	char rm[RMSIZE] = { 0 };
	char imm1[IMMSIZE] = { 0 };
	char imm2[IMMSIZE] = { 0 };

	//just looping trough the lineArray and assigning the values to the struct.

	opcode[0] = line[0];
	opcode[1] = line[1];
	opcode[2] = '\0';
	instruction[pc].opcodeAsInt = (long)strtol(opcode, NULL, 16); //Translate hexa string to dec long 

	rd[0] = line[2];
	rd[1] = '\0';
	instruction[pc].rdAsInt = (long)strtol(rd, NULL, 16);

	rs[0] = line[3];
	rs[1] = '\0';
	instruction[pc].rsAsInt = (long)strtol(rs, NULL, 16);

	rt[0] = line[4];
	rt[1] = '\0';
	instruction[pc].rtAsInt = (long)strtol(rt, NULL, 16);

	rm[0] = line[5];
	rm[1] = '\0';
	instruction[pc].rmAsInt = (long)strtol(rm, NULL, 16);

	imm1[0] = line[6];
	imm1[1] = line[7];
	imm1[2] = line[8];
	imm1[3] = '\0';

	if (imm1[0] >= '0' && imm1[0] <= '7')
		instruction[pc].imm1AsInt = (long)strtol(imm1, NULL, 16);
	else {
		char tempimm1[2];
		tempimm1[0] = imm1[1];
		tempimm1[1] = imm1[2];
		instruction[pc].imm1AsInt = -256 + ((long)strtol(tempimm1, NULL, 16));
	}
	imm2[0] = line[9];
	imm2[1] = line[10];
	imm2[2] = line[11];
	imm2[3] = '\0';

	if (imm2[0]  >= '0' && imm2[0]<= '7')
		instruction[pc].imm2AsInt = (long)strtol(imm2, NULL, 16);
	else {
		char tempimm2[2];
		tempimm2[0] = imm2[1];
		tempimm2[1] = imm2[2];
		instruction[pc].imm2AsInt = -256 + ((long)strtol(tempimm2, NULL, 16));
	}








};