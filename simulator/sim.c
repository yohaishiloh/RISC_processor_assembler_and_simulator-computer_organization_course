#define _CRT_SECURE_NO_WARNINGS
#include "simulatorFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void dynamic_mem_free(interrupt* head) {
	interrupt* next = head->next;
	while (next != NULL) {
		free(head);
		head = next;
		next = next->next;
	}
	free(head);
	return;
}


int main(int argc, char* argv[]) {
	// open input files:
	FILE* imemin = fopen(argv[1], "r");
	if (imemin == NULL) {
		printf("Reading the file 'imemin.txt' has failed! \nexit...\n");
		exit(1);
	};
	FILE* dmemin = fopen(argv[2], "r");
	if (dmemin == NULL) {
		printf("Reading the file 'dmemin.txt' has failed! \nexit...\n");
		fclose(imemin);
		exit(1);
	};
	FILE* diskin = fopen(argv[3], "r");
	if (imemin == NULL) {
		printf("Reading the file 'diskin.txt' has failed! \nexit...\n");
		fclose(imemin);	fclose(dmemin);
		exit(1);
	};
	FILE* irq2in = fopen(argv[4], "r");
	if (irq2in == NULL) {
		printf("Reading the file 'irq2in.txt' has failed! \nexit...\n");
		fclose(imemin);	fclose(dmemin); fclose(diskin);
		exit(1);
	};
	
	// read imemin file into array of 'instructions':
	instruction instructionsArray[MAXLINES]; //struct array of the instructions in imemin file
	imemin_read(imemin, instructionsArray); 
	fclose(imemin);
	
	// Read dmemin file into array:
	long dmem[MAXLINES+1] = { 0 }; 
	dmemin_read(dmemin, dmem);
	fclose(dmemin);

	// Read irq2in file into array:
	interrupt* irq2_head = NULL;
	irq2_head = irq2in_read(irq2in, irq2_head);
	fclose(irq2in);

	// Read diskin file into array:
	char diskmem[DISKINMAXLINES + 1][9] = {0};
	diskin_read(diskin, diskmem);
	fclose(diskin);
	diskmem[DISKINMAXLINES][0] = 255;
	
	// Initialize output files:
	FILE* dmemout = fopen(argv[5], "w");
	FILE* regout = fopen(argv[6], "w");
	FILE* trace = fopen(argv[7], "w");
	FILE* hwregtrace = fopen(argv[8], "w");
	FILE* cycles = fopen(argv[9], "w");
	FILE* leds = fopen(argv[10], "w");
	FILE* display7seg = fopen(argv[11], "w");
	FILE* diskout = fopen(argv[12], "w");
	FILE* monitor_txt = fopen(argv[13], "w");
	FILE* monitor_yuv = fopen(argv[14], "w");

	// Additional varaiables:
	long pc= 0;
	long regArray[REGNUM] = { 0 }; // Array of registers
	long ioRegArray[IOREGNUM] = { 0 }; // Array of I/O registers
	long monitorPixels[MONITORSIZE+1] = { 0 }; // Array of monitor values
	monitorPixels[MONITORSIZE] = -1; // set max-index-changed indicator into -1 (as "nothing has being changed yet")
	long isISR = 0;
	long next_irq = irq2_head->value; // Set header of irq2 interruptions list
	long diskClock = 0;

	// instructions execution:
	for (pc = 0; instructionsArray[pc].opcodeAsInt != 21; pc = (pc + 1) % 4096) {
		trace_write(trace, instructionsArray[pc], pc, instructionsArray[pc].opcodeAsInt, regArray); // Write line into trace
		checkAndExecute(hwregtrace, dmem, ioRegArray, regArray, &pc, instructionsArray, &isISR); // Reads an instruction line and execute it's content
		if (instructionsArray[pc].opcodeAsInt == 20 && regArray[instructionsArray[pc].rsAsInt] + regArray[instructionsArray[pc].rtAsInt] == 9) // If inst was to change leds - write into leds file
			leds_write(leds, ioRegArray);
		if (instructionsArray[pc].opcodeAsInt == 20 && regArray[instructionsArray[pc].rsAsInt] + regArray[instructionsArray[pc].rtAsInt] == 10) // If inst was to change 7seg - write into 7seg file
			display7_write(display7seg, ioRegArray);
		timer(ioRegArray); 
		diskDrive(&diskClock, diskmem, ioRegArray, dmem);
		monitor(ioRegArray, monitorPixels);
		next_irq = interupt2(ioRegArray, irq2_head, next_irq); // Check if the cycle equal to an interruption, and if it does - updating next interruption value 
		interuptionsHandling(ioRegArray, &pc, &isISR);
		if (ioRegArray[8] == 0xffffffff) ioRegArray[8] = 0; // Checks if pc > 4096 (if it had make a full cycle over mas pc) 
		else ioRegArray[8]++; // cycle += 1
	}
	
	if (instructionsArray[pc].opcodeAsInt == 21) { // Print last trace - before the halt command
		trace_write(trace, instructionsArray[pc], pc, instructionsArray[pc].opcodeAsInt, regArray);
		ioRegArray[8]++; // cycle += 1
	}

	// Print output files:
	dmemout_write(dmemout, dmem);
	regout_write(regout, regArray);
	fprintf(cycles, "%d", ioRegArray[8]);
	if (diskmem[DISKINMAXLINES]!= -1) // Get in if diskmem has changed: 
		diskout_write(diskout, diskmem);
	if (monitorPixels[MONITORSIZE] != -1) // Get in if monitorPixels has changed:
		monitor_write(monitor_txt,monitor_yuv, monitorPixels);

	// And of run - free allocated memory and close output files:
	dynamic_mem_free(irq2_head);
	fclose(dmemout); fclose(regout); fclose(trace);	fclose(hwregtrace);
	fclose(cycles); fclose(leds); fclose(display7seg); fclose(diskout);
	fclose(monitor_txt); fclose(monitor_yuv);

	return 0;
}