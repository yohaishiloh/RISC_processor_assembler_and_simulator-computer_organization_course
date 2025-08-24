#include "simulatorFunctions.h"

// initializing and adding new inerruption
interrupt* add_irq(interrupt* head, long value) {
	interrupt* new_interrupt = (interrupt*)malloc(sizeof(interrupt));
	if (new_interrupt == NULL) {
		printf("Memory allocation for interruption has failed! \nexit...\n");
		dynamic_mem_free(head);
		exit(2);
	}
	new_interrupt->next = NULL;
	new_interrupt->value = value;
	if (head == NULL) // it is the first interruption in the list
		return new_interrupt;
	interrupt* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new_interrupt;
	return head;
}

long imemin_read(FILE* imemin, instruction instructions[]) {
	int i = 0;
	char line[13];
	while (!feof(imemin) && i < 4096) {
		fgets(line, 13, imemin);
		if (line[0] == '\n')
			continue;
		if (line[0] == '\0' || 0 == strcmp(line, "000000000000")) // end of instructions input from imemin was reached
			break;
		structArrayCreator(i, line, instructions); // Cuts the line to it's parts and stores it in new instruction struct 
		i++;
	}
	return i; 
};

void dmemin_read(FILE* dmemin, long dmem[MAXLINES]) {
	char line[9];
	int i = 0;
	while (!feof(dmemin) && i < 4096) {
		fgets(line, 9, dmemin);
		if (line[0] == '\0')
			return;
		if (line[0] == '\n')
			continue;
		dmem[i] = strtol(line, NULL, 16);
		i++;
	};
	return;
};

void diskin_read(FILE* diskin, char diskmem[][9]) {
	char line[17];
	char line2[17] = "0";
	int i = 0;
	while (!feof(diskin) && i < DISKINMAXLINES) {
		fscanf(diskin, "%s", line);
		if (line[0] == '\0')
			return;
		if (line[0] == '\n')
			continue;
		strcpy(diskmem[i], line);
		i++;
	};
	return;
}

// Reads the irq2in file and saves it in interruptions linked list: 
interrupt* irq2in_read(FILE* irq2in, interrupt* irq2head) {
	char line[7];
	int i = 0;
	long value = 0;
	while (!feof(irq2in)) {
		fgets(line, 6, irq2in);
		if (line[0] == '\n' || line[0] == '\0')
			continue;
		value = strtol(line, NULL, 10);
		irq2head = add_irq(irq2head, value);
	};
	return irq2head;
}
