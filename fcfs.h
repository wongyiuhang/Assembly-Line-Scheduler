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
	int i, j;
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	
	for(i = 0; i < NUM_OF_DAY; i++) {
		for(j = 0; j < 3; j++) {
			// Know the first order
			// Find the best start point of the order
			isConflict();
			// Add order to the position
			FCFS_addOrderToSchedule(struct Schedule* scheduleTable, struct Order* order, int day, int line);
		}
	}
}