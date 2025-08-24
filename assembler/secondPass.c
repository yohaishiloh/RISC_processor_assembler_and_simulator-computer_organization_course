#include "FuncDeclaration.h"

// Search for labels and replaces them into address in the immediates:
void label_finder(Line* line, Label* header) {
	Label* next = header->next_L;
	int match = 0;
	if (isalpha(*(line->imm1)) != 0) {
		while (next != NULL && match == 0) {
			if (0 == strcmp(line->imm1, next->name)) {
				strcpy(line->imm1, next->line_num);
				match = 1;
				next = header->next_L;
			}
			next = next->next_L;
		}
	}
	else if (isalpha(*(line->imm2)) != 0) {
		while (next != NULL && match == 0) {
			if (0 == strcmp(line->imm2, next->name)) {
				strcpy(line->imm2, next->line_num);
				match = 1;
				next = header->next_L;
			}
			next = next->next_L;
		}
	}
	return;
}

void data_mem_init(char data_mem[][9]) {
	for (int i = 0; i < 4096; i++) {
		strcpy(&data_mem[i], "00000000");
	}
}


// Save data words into the data memory array: 
int store_word(char data_mem[][9], char curr_line[], int max_ind) {
	int i = 0, address = 0, value = 0, value_len = 0;
	char address_s[12];
	char value_s[9];
	char zeros_added_value[18] = "00000000";

	strcpy(curr_line, curr_line + 6);
	getWord(curr_line, &i, address_s);
	getWord(curr_line, &i, value_s);
	// Checking if parameters in dec or hex and handle them as needed:
	if (address_s[0] == '0' && address_s[1] == 'x')
		address = (int)strtol(address_s, NULL, 0);
	else
		address = (int)strtol(address_s, NULL, 10);
	if (value_s[0] == '0' && value_s[1] == 'x')
		value = (int)strtol(value_s, NULL, 0);
	else
		value = (int)strtol(value_s, NULL, 10);

	sprintf(value_s, "%x", value);

	// Sign extention:
	strcat(zeros_added_value, value_s);
	value_len = strlen(zeros_added_value);
	strcpy(value_s, zeros_added_value + value_len - 8);

	// Store the data word(value) in it's address in data_mem:
	strcpy(data_mem[address], value_s); 

	// Updating maximal saved index of data_mem:
	if (address > max_ind) {
		return address;
	}
	return max_ind;
}

// Writing output files:
void imem_write(FILE* imemin, Line* inst_mem, Label* header, int inst_len) {
	Line* next_line;
	for (int i = 0; i < inst_len; i++) {
		next_line = &inst_mem[i];
		label_finder(next_line, header);
		//		if (strcmp(&(next_line[i].opcode), "-1")==0) {
			//		return;
				//}
		linetohexconvert(next_line);
		fprintf(imemin, "%s%s%s%s%s%s%s\n", next_line->opcode, next_line->rd, next_line->rs, next_line->rt, next_line->rm, next_line->imm1, next_line->imm2);
	}
}

void dmem_write(FILE* dmemin, char data_mem[][9]) {
	int i = 0;
	while (i < 4096 && data_mem[i][0] != NULL) {
		fprintf(dmemin, "%s\n", data_mem[i]);
		i++;
	}
	return;
	//fprintf();
}

int second_pass(FILE* program, Line* inst_mem, char data_mem[][9]) {
	int i = 0, max_ind = 0, label_indicator = 0;
	char curr_line[MAX_LINE] = { 0 };
	Line* new_line = { 0 };
	char word_add[5];
	char word_value[10];
	while (!feof(program)) {
		fgets(curr_line, MAX_LINE, program);

		tabs_remove(curr_line);
		if (curr_line[0] != '\n') { // If not an empty line
			if ((label_indicator = is_label(curr_line)) == 0) { // If line isn't a label
				if (is_dot_word(curr_line) == 0) { // instruction line reached(neither label nor .word) 
					new_line = &inst_mem[i]; 
					lineToCode(curr_line, new_line); // Breaking the line by it's parts 
					i++;
				}
				else { // The line is data word:
					max_ind = store_word(data_mem, curr_line, max_ind);
				}
			}
			else if (label_indicator > 1) { // The line containing both label and instruction
				strcpy(curr_line, curr_line + label_indicator); // Pulling the instruction line from the text line at the file
				tabs_remove(curr_line);
				new_line = &inst_mem[i];
				lineToCode(curr_line, new_line); // Breaking the line by it's parts 
				i++;
			}
		}
	}
	data_mem[max_ind + 1][0] = NULL; // Marking the end of the array
	return i;
}