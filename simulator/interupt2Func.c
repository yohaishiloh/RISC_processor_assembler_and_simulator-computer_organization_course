#include "simulatorFunctions.h"

//Here we handle irq2 sets irq2 to 1 if the current clock cycle mantioned in the irq2in file 

long interupt2(long ioRegArray[IOREGNUM], interrupt* irq2head, long next_irq) {
	
	if (ioRegArray[8] == next_irq) {
		ioRegArray[5] = 1;
		next_irq = irq2Update(irq2head, next_irq);
	};



	return next_irq;
}