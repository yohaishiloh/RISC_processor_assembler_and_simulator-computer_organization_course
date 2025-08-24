#include "stdio.h"
#include "FuncDeclaration.h"

void getWord(char line[MAX_LINE], int* pI, char reg[MAX_LINE]) { //gets line, pointer to the beginning of the next line in the file and destination register
	int j = 0;
	while (iswspace(line[*pI]) != 0) { // go to the first non white space char
		++*pI;
	}
	while (iswspace(line[*pI]) == 0 && line[*pI] != ',') { // copies the word 
		reg[j] = line[*pI];
		++j;
		++*pI;
	}
	++ * pI;
	reg[j] = '\0';
}

