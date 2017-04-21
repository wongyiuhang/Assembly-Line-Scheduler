#include "struct.h"
#include "global.h"

#pragma once

int FCFS_daysleft(int num){
	return (num%PRODUCT_PER_DAY) ? (num/PRODUCT_PER_DAY+1) : num/PRODUCT_PER_DAY;
}

int FCFS_addOrderToSchedule(struct Schedule* scheduleTable, struct Order* order, int day, int line) {
	strcpy(resultScheduleTable->algo, "FCFS");
	struct DayJob* today = resultScheduleTable->days + day;
	today->orderID[line] = order->id;
}

int FCFS_isConflict(const struct Order* order, const struct Order* todayOrder[3]) {
	int i;
	for(i = 0; i < 3; i++)
		if(todayOrder[i] != NULL && checkEqiuipConflict(order->prod, todayOrder[i]->prod))
			return 1;
	return 0;
}



//assume order are ordered by start date
void FCFS_algorithm(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable){
	// Initialization
	int day, line;
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	struct Node* nextNode;
	struct Order* firstOrder;
	
	for(day = 0; day < NUM_OF_DAY; day++) {
		// Initialise value
		int skipDay = 0;
		struct DayJob* today = resultScheduleTable->days + day;
		struct Order* todayOrder[3], buffer;
		for(line = 0; line < 3; line++) {
			todayOrder[line] = NULL;
			today->orderID[line] = 0;
		}

		for(line = 0; line < 3; line++) {
			// Know the first order
			nextNode = cloneJobQueue->head;
			firstOrder = (nextNode != NULL) ? &nextNode->data : NULL;

			// Find the best start point of the order
			if(FCFS_isConflict(firstOrder, todayOrder)) {
				skipDay = 1;
				break;
			}

			// Add order to the position
			FCFS_addOrderToSchedule(resultScheduleTable, firstOrder, day, line);
			dequeue(cloneJobQueue, &buffer);
		}

		if(skipDay)
			continue;

		// Pass DayJob to file output process
	}
}
