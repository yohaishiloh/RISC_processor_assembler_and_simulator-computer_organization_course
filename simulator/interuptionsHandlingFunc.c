#include "simulatorFunctions.h"
//Here we handle interuptions 

void interuptionsHandling(long ioRegArray[IOREGNUM], long* pc, long *isISR) {

	long irq = (ioRegArray[0] & ioRegArray[3]) | (ioRegArray[1] & ioRegArray[4]) | (ioRegArray[2] & ioRegArray[5]);

	if (irq == 1 && *isISR == 0) {//Checks if irq = 1 and we dont handle any interuption from before
		ioRegArray[7] = *pc; 
		*pc = ioRegArray[6] - 1;
		*isISR = 1;
	}

}