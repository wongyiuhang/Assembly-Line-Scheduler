#include <stdio.h>
#include <unistd.h>

#include "struct.h"
#include "global.h"


#pragma once

int FCFS_daysleft(int num){
	return (num%PRODUCT_PER_DAY) ? (num/PRODUCT_PER_DAY+1) : num/PRODUCT_PER_DAY;
}

void FCFS_addOrderToSchedule(struct Schedule* scheduleTable, struct Order* order, int day, int line) {
	int i;
	int x = FCFS_daysleft(order->quantity) > (order->endDate-day) ? (order->endDate-day) : FCFS_daysleft(order->quantity);
	for(i = 0; i < x; i++) {
		struct DayJob* today = scheduleTable->days + day + i;
		today->orderID[line] = order->id;
	}
}

int FCFS_isConflict(const struct Order* order, const struct Order* todayOrder[3]) {
	int i;
	for(i = 0; i < 3; i++)
		if(todayOrder[i] != NULL && checkEqiuipConflict(order->prod, todayOrder[i]->prod))
			return 1;
	return 0;
}

int FCFS_freeline(struct Order* todayOrder[]) {
	if (todayOrder[0] == NULL ) {return 0;}
	if (todayOrder[1] == NULL ) {return 1;}
	if (todayOrder[2] == NULL ) {return 2;}
	return -1;
}

//assume order are ordered by start date
void FCFS_algorithm(struct Queue* jobQueue, char* filePath, struct Schedule* resultScheduleTable){
	// Initialization
	int day, line;
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	struct Node* nextNode;
	struct Order* firstOrder;
	strcpy(resultScheduleTable->algo, "FCFS");
	
	for(day = 0; day < NUM_OF_DAY; day++)
		for(line = 0; line < 3; line++) {
			resultScheduleTable->days[day].orderID[line] = 0;
		}

	for(day = 0; day < NUM_OF_DAY; day++) {
		// Initialise value
		int skipDay = 0;
		struct DayJob* today = resultScheduleTable->days + day;
		struct Order* todayOrder[3], buffer;
		for(line = 0; line < 3; line++) {
			struct Node* ordersearch = searchOrder(jobQueue,today->orderID[line]);
			todayOrder[line] = &ordersearch->data;
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

		/*if(skipDay)
			continue;*/

		// Pass DayJob to file output process
	}
	/*
	int lastworkingdate= 0;
	while (true) {
		//take first order
		int j = 0;
		int temp = dequeue(cloneJobQueue,&firstOrder);
		//check null queue -->quit the process
		if (temp) break;
		// if exceed enddate, for loop will not run.
		for (j=lastworkingdate;j<firstOrder->endDate;j++){
			
			struct DayJob* today = resultScheduleTable->days + j;
			struct Order* todayOrder[3];
			printf("%s\n", resultScheduleTable->algo);
			struct Node* ordersearch = searchOrder(jobQueue,today->orderID[0]);
			
			todayOrder[0] = &ordersearch->data;
			ordersearch = searchOrder(jobQueue,today->orderID[1]);
			todayOrder[1] = &ordersearch->data;
			ordersearch = searchOrder(jobQueue,today->orderID[2]);
			todayOrder[2] = &ordersearch->data;
			// Check conflict
			if (FCFS_isConflict(firstOrder,todayOrder)) {continue;}
			// Check busy line.  if all line are busy, continue
			if(FCFS_freeline < 0 ) {continue;}
			FCFS_addOrderToSchedule(resultScheduleTable, firstOrder, j, FCFS_freeline(todayOrder));
			lastworkingdate = j;
			break;
		}
		
	}
	FILE* file = fopen(filePath, "w+");

	// Print header
	fprintf(file, "Algorithm: FCFS\n");
	fprintf(file, "Day: %d\n\n", NUM_OF_DAY);
	fprintf(file, "\t\t%5s\t%5s\t%5s\n", "L1", "L2", "L3");
	
	for(i = 0; i < NUM_OF_DAY; i++) {
		struct DayJob* today = resultScheduleTable->days + i;
		char day[3][6];
		for(j = 0; j < 3; j++) {
			if(today->orderID[j] == 0)
				strcpy(day[j], "-");
			else
				sprintf(day[j], "%05d", today->orderID[j]);
		}
		fprintf(file, "Day %02d:\t%5s\t%5s\t%5s\n", i + 1, day[0], day[1], day[2]);
	}

	fclose(file);
	*/
	
	
}
