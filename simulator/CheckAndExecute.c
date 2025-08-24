#include "simulatorFunctions.h"
//Here we check whice instruction we need to execute and execute it
void checkAndExecute(FILE* hwregtraceFile, long dmem[MAXLINES], long ioRegArray[IOREGNUM], long regArray[REGNUM], long *pc,
	instruction instructionArray[MAXLINES], long *isISR ) {


		regArray[1] = instructionArray[*pc].imm1AsInt;
		regArray[2] = instructionArray[*pc].imm2AsInt;

		switch (instructionArray[*pc].opcodeAsInt)
		{
		case 0:
			add(regArray, instructionArray[*pc]);
			break;

		case 1:
			sub(regArray, instructionArray[*pc]);
			break;

		case 2:
			mac(regArray, instructionArray[*pc]);
			break;

		case 3:
			and(regArray, instructionArray[*pc]);
			break;

		case 4:
			or(regArray, instructionArray[*pc]);
			break;

		case 5:
			xor(regArray, instructionArray[*pc]);
			break;
		
		case 6:
			sll(regArray, instructionArray[*pc]);
			break;
		
		case 7:
			sra(regArray, instructionArray[*pc]); 
			break;
		
		case 8:
			srl(regArray, instructionArray[*pc]);
			break;
		
		case 9:
			beq(pc ,regArray, instructionArray[*pc]);
			break;
		
		case 10:
			bne(pc, regArray, instructionArray[*pc]);
			break;
		
		case 11:
			blt(pc, regArray, instructionArray[*pc]);
			break;
		
		case 12:
			bgt(pc, regArray, instructionArray[*pc]);
			break;
		
		case 13:
			ble(pc, regArray, instructionArray[*pc]);
			break;
		
		case 14:
			bge(pc, regArray, instructionArray[*pc]);
			break;
		
		case 15:
			jal(pc, regArray, instructionArray[*pc]);
			break;
		
		case 16:
			lw(dmem, regArray, instructionArray[*pc]);
			break;
		
		case 17:
			sw(dmem, regArray, instructionArray[*pc]);
			break;
		
		case 18:
			reti(pc, ioRegArray[7],isISR);
			break;
		
		case 19:
			in(hwregtraceFile, pc, ioRegArray, regArray, instructionArray[*pc]);
			break;
		
		case 20:
			out(hwregtraceFile, pc, ioRegArray, regArray, instructionArray[*pc]);
			break;
		
		
		}
	
}