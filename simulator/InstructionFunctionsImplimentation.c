#include "simulatorFunctions.h"

//Here we have all the implimentations of the instructions

void add(long regArray[REGNUM], instruction instruction) {

	regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt] + regArray[instruction.rmAsInt];
}

void sub(long regArray[REGNUM], instruction instruction) {

	regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] - regArray[instruction.rtAsInt] - regArray[instruction.rmAsInt];
}


void mac(long regArray[REGNUM], instruction instruction) {

	regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] * regArray[instruction.rtAsInt] + regArray[instruction.rmAsInt];
}

void and (long regArray[REGNUM], instruction instruction) {

	regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] & regArray[instruction.rtAsInt] & regArray[instruction.rmAsInt];

}

void or (long regArray[REGNUM], instruction instruction) {


	regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] | regArray[instruction.rtAsInt] | regArray[instruction.rmAsInt];

}

void xor (long regArray[REGNUM], instruction instruction) {


	regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] ^ regArray[instruction.rtAsInt] ^ regArray[instruction.rmAsInt];


}



void sll(long regArray[REGNUM], instruction instruction) {


	if (regArray[instruction.rtAsInt] > 31)
		regArray[instruction.rsAsInt] = 0;
	else
		regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] << regArray[instruction.rtAsInt];


}

void sra(long regArray[REGNUM], instruction instruction) {

	if (regArray[instruction.rtAsInt] > 31) {
		if (regArray[instruction.rsAsInt] >= 0)
			regArray[instruction.rdAsInt] = 0;
		else
			regArray[instruction.rdAsInt] = 0xFFFFFFFF;

	}
	else
	{
		regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] >> regArray[instruction.rtAsInt];

		//Check if add F from the left is needed by checking if rs is negative
		if (regArray[instruction.rsAsInt] < 0)
		{
			long i = 0xFFFFFFFF;
			i = i << (32 - regArray[instruction.rtAsInt]); // Sets how many F from left is needed

			regArray[instruction.rdAsInt] = i | regArray[instruction.rdAsInt]; //i | rd to add F from the left

		}


	}
}

void srl(long regArray[REGNUM], instruction instruction) {


	if (regArray[instruction.rtAsInt] > 31)
		regArray[instruction.rsAsInt] = 0;
	else
		regArray[instruction.rdAsInt] = regArray[instruction.rsAsInt] >> regArray[instruction.rtAsInt];

}

void beq(long* pc, long regArray[REGNUM], instruction instruction) {


	if (regArray[instruction.rsAsInt] == regArray[instruction.rtAsInt])
		*pc = regArray[instruction.rmAsInt] - 1;

}

void bne(long* pc, long regArray[REGNUM], instruction instruction) {


	if (regArray[instruction.rsAsInt] != regArray[instruction.rtAsInt])
		*pc = regArray[instruction.rmAsInt] - 1;

}


void blt(long* pc, long regArray[REGNUM], instruction instruction) {

	if (regArray[instruction.rsAsInt] < regArray[instruction.rtAsInt])
		*pc = regArray[instruction.rmAsInt] - 1;

}

void bgt(long* pc, long regArray[REGNUM], instruction instruction) {

	if (regArray[instruction.rsAsInt] > regArray[instruction.rtAsInt])
		*pc = regArray[instruction.rmAsInt] - 1;

}

void ble(long* pc, long regArray[REGNUM], instruction instruction) {

	if (regArray[instruction.rsAsInt] <= regArray[instruction.rtAsInt])
		*pc = regArray[instruction.rmAsInt] - 1;

}

void bge(long* pc, long regArray[REGNUM], instruction instruction) {

	if (regArray[instruction.rsAsInt] >= regArray[instruction.rtAsInt])
		*pc = regArray[instruction.rmAsInt] - 1;

}


void jal(long* pc, long regArray[REGNUM], instruction instruction) {

	regArray[instruction.rdAsInt] = *pc + 1;
	*pc = regArray[instruction.rmAsInt] - 1;

}



void lw(long dmem[MAXLINES], long regArray[REGNUM], instruction instruction) {

	regArray[instruction.rdAsInt] = dmem[regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt]] + regArray[instruction.rmAsInt];

}


void sw(long dmem[MAXLINES + 1], long regArray[REGNUM], instruction instruction) {

	dmem[regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt]] = regArray[instruction.rmAsInt] + regArray[instruction.rdAsInt];
	if ((regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt]) > dmem[MAXLINES]) {
		dmem[MAXLINES] = regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt];
	}
}

void reti(long* pc, long ioReg7, long* isISR) {

	*pc = ioReg7;
	*isISR = 0;
}


void in(FILE* hwregtraceFile, long* pc, long ioRegArray[IOREGNUM], long regArray[REGNUM], instruction instruction) {
//	printf("enter into in\n");
	if (regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt] == 22)
		regArray[instruction.rdAsInt] = 0;
	else {
		//printf("enter into the else\n");
		regArray[instruction.rdAsInt] = ioRegArray[regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt]];
		//printf("rs is: %d\nrt is: %d\n", regArray[instruction.rsAsInt] , regArray[instruction.rtAsInt]);
	}
	hwregtrace(hwregtraceFile, ioRegArray, instruction, regArray);
}

void out(FILE* hwregtraceFile, long* pc, long ioRegArray[IOREGNUM], long regArray[REGNUM], instruction instruction) {

	ioRegArray[regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt]] = regArray[instruction.rmAsInt];
	hwregtrace(hwregtraceFile, ioRegArray, instruction, regArray);

}