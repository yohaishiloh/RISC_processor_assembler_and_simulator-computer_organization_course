#include "FuncDeclaration.h"

// structures initializers:
Label* label_init(char name[50], int line_num) {
	Label* new_L = (Label*)malloc(sizeof(Label));
	// allocation success check:
	if (new_L == NULL) {
		printf("memory allocation failed!\nexit...\n ");
		return new_L;
	};
	char address[12] = { 0 };
	strcpy(new_L->name, name);
	sprintf(address, "%d", line_num);
	strcpy(new_L->line_num, address);
	new_L->next_L = NULL;
	return new_L;
};

void line_init(Line* dest, char opcode[], char rd[], char rs[], char rt[], char rm[], char imm1[], char imm2[]) {
	strcpy(dest->opcode, opcode);
	strcpy(dest->rd, rd);
	strcpy(dest->rs, rs);
	strcpy(dest->rt, rt);
	strcpy(dest->rm, rm);
	strcpy(dest->imm1, imm1);
	strcpy(dest->imm2, imm2);
	return;
};

// Initialize a new label:
void add_label(Label* head, Label* new_L) {
	Label* temp = head;
	while ((temp->next_L) != NULL) {
		temp = temp->next_L;
	}
	temp->next_L = new_L;
	return;
}