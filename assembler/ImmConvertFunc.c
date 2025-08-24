#include "FuncDeclaration.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void immCodeConvert(char imm[500], char immHex[4]) { // convert immediats 

	int immInInt;
	int i = 2;
	if (imm[0] == '0' && imm[1] == 'x') {
		while (imm[i] != '\0')	{
			immHex[i - 2] = imm[i];
			i++;
		}
		immHex[i - 2] = '\0';
	}
	else if (isdigit(imm[0])){
		immInInt = atoi(imm); // converts immediate to integer
		if (immInInt < 16) {
			sprintf_s(immHex, 4, "00%x", immInInt);
		}
		else if (15 < immInInt && immInInt < 256) {
			sprintf_s(immHex, 4, "0%x", immInInt);
		}
		else {
			sprintf_s(immHex, 4, "%x", immInInt);
		}
	}
	else if (imm[0] == '-') {
		immInInt = atoi(imm);
		sprintf_s(immHex, 4, "%x", (immInInt & 0xFFF));
	}	
}


