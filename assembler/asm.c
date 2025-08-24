#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "FuncDeclaration.h"
#define MAX_LINE 500


// crash handle function here:
void crash_handle(Label* l_label) {
	Label* n_label = l_label->next_L ;
	Label* n_n_label;
	while (n_label->next_L != NULL) {
		n_n_label = n_label->next_L;
		free(n_label);
		n_label = n_n_label;
	};	
	free(l_label);
	return;
};


int main(int argc, char* argv[]) {

	FILE* program = fopen(argv[1], "r"); 
	if (program == NULL) {
		printf("Reading the file 'program.asm' has failed! \nexit...\n");
		exit(1);
	};
	// First iteration - labels collecting
	Label* Labels_list_header = label_init("head", -1);
	first_pass(program, Labels_list_header);
	rewind(program); // Puts file pointer back to its beginning for the second pass

	// Second iteration - instruction lines and data words reading:
	int inst_len = 0;
	Line inst_mem[4096] = { 0 };
	char data_mem[4096][9] = { 0 };
	data_mem_init(data_mem);
	inst_len = second_pass(program, inst_mem,data_mem);
	fclose(program);

	FILE* imemin = fopen(argv[2], "w");
	if (imemin == NULL) {
		printf("Reading the file 'imemin.txt' has failed! \nexit...\n");
		crash_handle(Labels_list_header);
		exit(1);
	};
	FILE* dmemin = fopen(argv[3], "w");
	if (dmemin == NULL) {
		printf("Reading the file 'dmemin.txt' has failed! \nexit...\n");
		fclose(imemin);
		crash_handle(Labels_list_header);
		exit(1);
	};
	
	// Output writing:
	imem_write(imemin, inst_mem, Labels_list_header, inst_len);
	dmem_write(dmemin, data_mem);
	
	// Free allocated memory and closing files before exiting:
	crash_handle(Labels_list_header);
	fclose(imemin);
	fclose(dmemin);
	
	return 0;
};