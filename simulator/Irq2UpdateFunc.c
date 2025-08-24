#include "simulatorFunctions.h"

long irq2Update(interrupt* irq2head, long last_irq) {
	long next_irq = 0;
	interrupt* temp = irq2head;

	while (temp->next != NULL) {
		if (temp->value == last_irq) {
			next_irq = temp->next->value;
			return next_irq;
		}
		temp = temp->next;
	}
	return 0; // last irq2 was the last one - so the next irq will be updated as zero so it won't interrupt anymore
};


