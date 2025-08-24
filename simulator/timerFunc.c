#include "simulatorFunctions.h"

//Here we impliment the timer

void timer(long ioRegArray[IOREGNUM]) {

	//When timerenable = 1 incriment timercurrent by 1
	if (ioRegArray[11] == 1) { 

		ioRegArray[12]++;

	}
	//if timercurrent = timermax 
	if (ioRegArray[12] == ioRegArray[13]) {

		ioRegArray[12] = 0; //set timer current to 0
		ioRegArray[3] = 1; //set irq0status to 1
	}


}