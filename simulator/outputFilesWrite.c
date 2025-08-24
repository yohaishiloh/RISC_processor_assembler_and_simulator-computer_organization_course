#include "simulatorFunctions.h"
#define _CRT_SECURE_NO_WARNINGS

// Function that restore the instruction as string for the trace file:
void full_inst_restore(instruction inst, char dest[], char opcode[], char imm1[], char imm2[]) { 
	char full_inst[13];
	strcpy(full_inst, opcode);
	sprintf(dest, "%x%x%x%x", inst.rdAsInt, inst.rsAsInt, inst.rtAsInt, inst.rmAsInt);
	strcat(full_inst, dest);
	strcat(full_inst, imm1 + 5);
	strcat(full_inst, imm2 + 5);
	strcpy(dest, full_inst);
}

// sign extension of the immediates:
void imm_sign_extension(long immediate, char dest[]) {
	char zeros[17] = "00000000";
	char fs[17];
	if (immediate >= 0) { // If immediate is positive
		sprintf(dest, "%x", immediate);
		strcat(zeros, dest); // add zeros (sign extension)
		int zeros_added_len = strlen(zeros);
		strcpy(dest, zeros + (zeros_added_len - 8)); // take only the wanted size of the string
		return;
	}
	else { // If negative:
		sprintf(dest, "%x", immediate);
		return;
	}
};

void sign_extension(long reg, char dest[], int dest_max_len) {
	char zeros[25] = "000000000000";
	sprintf(dest, "%x", reg); 
	strcat(zeros, dest); // Add zeros
	int zeros_added_len = strlen(zeros);
	strcpy(dest, zeros + (zeros_added_len - dest_max_len)); // Take only the wanted size of the string
	return;
}


void trace_write(FILE* trace, instruction instruction, long pc_int, long inst_int, long regArray[REGNUM]) {
	char pc[4];
	char inst[3];
	char full_inst[13];
	char r0[9] = "00000000";
	char reg[9];
	char imm1[9];
	char imm2[9];

	// compute and write 'pc'
	sign_extension(pc_int, pc, 3);
	fprintf(trace, "%s ", pc);

	// compute and write the instruction line
	imm_sign_extension(instruction.imm1AsInt, imm1);
	imm_sign_extension(instruction.imm2AsInt, imm2);
	sign_extension(inst_int, inst, 2);
	full_inst_restore(instruction, full_inst, inst, imm1, imm2);
	fprintf(trace, "%s ", full_inst);

	// rewrite 0 into $zero and print it's value
	regArray[0] = 0;
	fprintf(trace, "%s ", r0);

	// compute and write the immediates
	fprintf(trace, "%s ", imm1);
	fprintf(trace, "%s ", imm2);

	// compute and write other registers
	for (int i = 3; i < 15; i++) {
		sign_extension(regArray[i], reg, 8);
		fprintf(trace, "%s ", reg);
	}
	sign_extension(regArray[15], reg, 8);
	fprintf(trace, "%s\n", reg);
}

//Here we create the hwregtrace.txt file:
void hwregtrace(FILE* hwregtraceFile, long ioRegArray[IOREGNUM], instruction instruction, long regArray[REGNUM]) {
	char ioRegNames[][IONAMESIZE] = { "irq0enable","irq1enable","irq2enable","irq0status","irq1status","irq2status",
		"irqhandler","irqreturn","clks","leds","display7seg","timerenable","timercurrent","timermax","diskcmd",
		"disksector","diskbuffer","diskstatus","reserved","reserved","monitoraddr","monitordata","monitorcmd" };

	char name[IONAMESIZE];
	char operation[IONAMESIZE] = "\0";
	long data;
	char data_str[9];

	// get operation
	if (instruction.opcodeAsInt == 19) strcpy(operation, "READ");
	else if (instruction.opcodeAsInt == 20) strcpy(operation, "WRITE");

	//get name
	strcpy(name, ioRegNames[regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt]]);

	//get data in int
	data = ioRegArray[regArray[instruction.rsAsInt] + regArray[instruction.rtAsInt]];
	sign_extension(data, data_str, 8);

	// print line into hwregtrace file:
	fprintf(hwregtraceFile, "%d %s %s %s\n", ioRegArray[8], operation, name, data_str);
}


void dmemout_write(FILE* dmemout, long dmem[]) {
	char mem_line[9];
	for (int i = 0; i < dmem[MAXLINES] && i < MAXLINES; i++) {
		if (dmem[i] == 0)
			fprintf(dmemout, "%s\n", "00000000");
		else {
			sign_extension(dmem[i], mem_line, 8);
			fprintf(dmemout, "%s\n", mem_line);
		}
	}
	return;
}

void regout_write(FILE* regout, long regArray[]) {
	char reg[9];
	for (int i = 3; i < 16; i++) {
		sign_extension(regArray[i], reg, 8);
		fprintf(regout, "%s\n", reg);
	}
	return;
}


void leds_write(FILE* leds, long ioRegArray[]) {
	char leds_str[9];
	sign_extension(ioRegArray[9], leds_str, 8);
	fprintf(leds, "%d %s\n", ioRegArray[8], leds_str);
	return;
}

void display7_write(FILE* display7seg, long ioRegArray[]) {
	char display7_str[9];
	sign_extension(ioRegArray[10], display7_str, 8);
	fprintf(display7seg, "%d %s\n", ioRegArray[8], display7_str);
	return;
}

void diskout_write(FILE* diskout, char diskmem[][9]) {
	char mem_line[10];
	if (diskmem[DISKINMAXLINES][0] == 255)
		return;
	for (int i = 0; i < diskmem[DISKINMAXLINES][0] + 1; i++) {
		for (int j = 0; j < 128; j++) {
			if (diskmem[i * 128 + j][0] == '\0') {
				fprintf(diskout, "%s\n", "00000000");
			}
			else {
				fprintf(diskout, "%s\n", diskmem[i * 128 + j]);
			}
		}
	}
	return;
}

void monitor_write(FILE* monitor_txt, FILE* monitor_yuv, long monitorPixels[]) {
	char moni_line[3];
	for (int i = 0; i < MONITORSIZE; i++) {
		if (i < monitorPixels[MONITORSIZE] + 1) {
			if (monitorPixels[i] == 0) {
				fprintf(monitor_txt, "%s\n", "00");
			}
			else {
				sign_extension(monitorPixels[i], moni_line, 2);
				fprintf(monitor_txt, "%s\n", moni_line);
			}
		}
		if (monitorPixels[i] == 0) {
			fprintf(monitor_yuv, "%c", 0);
		}
		else {
			fprintf(monitor_yuv, "%c", monitorPixels[i]);
		}
	}
	return;
}