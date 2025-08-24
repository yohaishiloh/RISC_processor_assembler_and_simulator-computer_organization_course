#include "simulatorFunctions.h"
//Here we impliment the disk drive

void diskDrive(long *diskClock, char diskmem[DISKINMAXLINES+1][9], long ioRegArray[IOREGNUM], long dmem[MAXLINES]) {

	if (ioRegArray[14] != 0 && ioRegArray[17] == 0) 
		ioRegArray[17] = 1; 

	if (ioRegArray[14] == 1 && ioRegArray[17]==1) {
		if (*diskClock % 8 == 0) { //every 8 clock cycles we reading 1 word from the sector to main memory
			dmem[ioRegArray[16]+((*diskClock)/8)] = strtoll(diskmem[ioRegArray[15] * 128 + (*diskClock) / 8], NULL, 16);
		}
}
	else if (ioRegArray[14] == 2 && ioRegArray[17] == 1) { //Every 8 clock cycles we write 1 word from main memory to the sector
		if (*diskClock % 8 == 0) {
			imm_sign_extension(dmem[ioRegArray[16] + ((*diskClock) / 8)], diskmem[ioRegArray[15] * 128 + (*diskClock) / 8]);
			if (diskmem[DISKINMAXLINES][0] < ioRegArray[15])
				diskmem[DISKINMAXLINES][0] = ioRegArray[15];
		}
	}
	if (*diskClock == 1023) { 
		ioRegArray[17] = 0;
		ioRegArray[14] = 0;
		ioRegArray[4] = 1;
		*diskClock = 0;
	}
	else if (ioRegArray[17] == 1)
		++(*diskClock);
}


