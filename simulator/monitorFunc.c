#include "simulatorFunctions.h"
//Here we impliment the monitor

void monitor(long ioRegArray[IOREGNUM],long monitorPixels[MONITORSIZE+1]) {


	if (ioRegArray[22] == 1) {

		monitorPixels[ioRegArray[20]] = ioRegArray[21];
		if (monitorPixels[MONITORSIZE] < ioRegArray[20])
			monitorPixels[MONITORSIZE] = ioRegArray[20];
		ioRegArray[22] = 0;

	}




}