#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "struct.h"
#include "global.h"


#pragma once

int FCFS_daysleft(int num){
	return (num%PRODUCT_PER_DAY) ? (num/PRODUCT_PER_DAY+1) : num/PRODUCT_PER_DAY;
}

void FCFS_addOrderToSchedule(struct Schedule* scheduleTable, struct Order* order, int day, int line) {
	int i;
	// int x = FCFS_daysleft(order->quantity) > (order->endDate-day) ? (order->endDate-day) : FCFS_daysleft(order->quantity);
	// for(i = 0; i < x; i++) {
	// 	scheduleTable->days[day + i].orderID[line] = order->id;
	// }
	int totalDay = FCFS_daysleft(order->quantity);
	for(i = 0; i < totalDay; i++) {
		if(day + i >= order->endDate || day + i >= 60)
			break;
		scheduleTable->days[day + i].orderID[line] = order->id;
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
	int pid, day, line, fd[2], i;
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	struct Node* nextNode;
	struct Order* firstOrder;
	strcpy(resultScheduleTable->algo, "FCFS");
	
	for(day = 0; day < NUM_OF_DAY; day++)
		for(line = 0; line < 3; line++) {
			resultScheduleTable->days[day].orderID[line] = 0;
		}

	// Prepare pipe for result streaming
	pipe(fd);

	// Prepare child process for file output
	if(fork()) {
		// Parent process
		// Close unnessary pipe end
		close(fd[0]);
		nextNode = cloneJobQueue->head;
		for(day = 0; day < NUM_OF_DAY; day++) {
			// Initialise value
			struct DayJob* today = resultScheduleTable->days + day;
			struct Order* todayOrder[3];
			struct Order buffer;

			// Error checking
			if(nextNode == NULL)
				break;
			for(line = 0; line < 3; line++) {
				struct Node* ordersearch = searchOrder(jobQueue,today->orderID[line]);
				todayOrder[line] = (ordersearch != NULL) ? &ordersearch->data : NULL;
			}

			for(line = 0; line < 3; line++) {
				// Know the first order
				if(nextNode == NULL)
					break;
				firstOrder = &nextNode->data;

				// Find the best start point of the order
				if(FCFS_isConflict(firstOrder, todayOrder))
					break;

				// Add order to the position
				FCFS_addOrderToSchedule(resultScheduleTable, firstOrder, day, line);
				nextNode = nextNode->next;
			}
		}
		// Pass DayJob to file output process
		for(day = 0; day < NUM_OF_DAY; day++)
			write(fd[1], resultScheduleTable->days + day, sizeof(dayjob_t));

		close(fd[1]);
		wait(NULL);
	} else {
		// Child process
		// Close unnessary pipe end
		close(fd[1]);
		fileOutput(fd, "FCFS", filePath, resultScheduleTable);
	}
}
