#include "FuncDeclaration.h"

void tabs_remove(char line[]) {
	int i = 0;
	while (line[i] == '\t' || line[i] == ' ') {
		i++;
	}
	strcpy(line, line + i);
}


// checks if a line is a label: 
int is_label(char line[]) {
	int len = 0, i = 0;
	len = strlen(line);
	i = len - 1;
	while (line[i] == '\t' || line[i] == ' ' || line[i] == '\n') {
		i--;
	}
	line[i + 1] = '\0';
	len = strlen(line);
	if ((isalpha(line[0]) != 0) && (line[len - 1] == ':')) // starts with a latter and ends with ':'
		return 1;
	if (isalpha(line[0]) != 0) { // starts with a latter but ends with something else then ':' 
		i = 0;
		while (line[i] != '\0') {
			if (line[i] == ':') { // checks if the line contains label and a commend afterward
				line[i + 1] = '\0';
				return (i + 2);
			}
			i++;
		}
	}
	return 0;
}

// Checks if the line is a word to write into the dmem file:
int is_dot_word(char line[]) {
	if (line[0] == 0)
		return 0;
	if (line[0] == '.') {
		return 1;
	}
	return 0;
}


void first_pass(FILE* program, Label* head) {
	int i = 0, j = 0, len = 0;
	Label* new_L;
	char line[MAX_LINE] = { 0 };
	head->next_L = NULL;
	while (!feof(program)) {
		fgets(line, MAX_LINE, program);
		if (line[0] == '\t' || line[0] == ' ')
			tabs_remove(line);
		if (line[0] == '\n') // Empty line
			continue;
		if (is_label(line) != 0) { // The line is a label
			len = strlen(line);
			if (line[len - 1] == ':')
				line[len - 1] = '\0';
			else
				line[len - 1] = '\0';
			new_L = label_init(line, i);
			add_label(head, new_L);
		}
		else if (is_dot_word(line) != 1) // if the line was an instruction - increase lines counter by 1
			i++;
		j = 0;
	}
}
