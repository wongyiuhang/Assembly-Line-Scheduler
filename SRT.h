#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "struct.h"
#include "global.h"
#include "fout.h"

#pragma once

/***************************************************
 *                                                 *
 *     Input: Job queue [struct Queue*]            *
 *    Output: Schedule table [struct Schedule*]    *
 *                                                 *
 ***************************************************/

int SRT_notRepeat(int orderID, const struct Order* todayOrder[3]) {
	int i;
	for(i = 0; i < 3; i++)
		if(todayOrder[i] != NULL && orderID == todayOrder[i]->id)
			return 0;
	return 1;
}

int SRT_notConflict(const struct Order* order, const struct Order* todayOrder[3]) {
	int i;
	for(i = 0; i < 3; i++)
		if(todayOrder[i] != NULL && checkEqiuipConflict(order->prod, todayOrder[i]->prod))
			return 0;
	return 1;
}

struct Node* SRT_find(const struct Queue* jobQueue, int day, const struct Order* today[3]) {
	struct Node* nextNode = jobQueue->head;
	struct Node* SRT = NULL;
	while (nextNode != NULL) {
		if(
			nextNode->data.startDate <= day + 1 // Find an order exist on or before the day
			&&
			nextNode->data.remainDay > 0 // Reject finished order
			&&
			SRT_notRepeat(nextNode->data.id, today)
			&&
			SRT_notConflict(&nextNode->data, today)
			&&
			(
				SRT == NULL // For the first iteration
				||
				nextNode->data.remainDay < SRT->data.remainDay // Check if the current job is more suitable than previous
			)
		)
			SRT = nextNode;
		nextNode = nextNode->next;
	}
	return SRT;
}

void SRT_algorithm(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable) {
	int pid, day, line, fd[2], i;
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	struct Node* nodePointer = cloneJobQueue->head;
	strcpy(resultScheduleTable->algo, "SRT");

	// Initialise remain day value
	while(nodePointer != NULL){
		nodePointer->data.remainDay = nodePointer->data.quantity / PRODUCT_PER_DAY;
		if(nodePointer->data.quantity % PRODUCT_PER_DAY != 0)
			nodePointer->data.remainDay++;
		nodePointer = nodePointer->next;
	}

	// Prepare pipe for result streaming
	pipe(fd);

	// Prepare child process for file output
	if(fork()) {
		// Parent process
		// Close unnessary pipe end
		close(fd[0]);
		for(day = 0; day < NUM_OF_DAY; day++) {
			// Initialise value
			struct DayJob* today = resultScheduleTable->days + day;
			struct Order* todayOrder[3];
			for(line = 0; line < 3; line++) {
				todayOrder[line] = NULL;
				today->orderID[line] = 0;
			}

			// Find shortest remain time
			for(line = 0; line < 3; line++) {
				nodePointer = SRT_find(cloneJobQueue, day, todayOrder);
				if(nodePointer == NULL)
					break;
				today->orderID[line] = nodePointer->data.id;
				todayOrder[line] = &nodePointer->data;
			}

			// Pass DayJob to file output process
			write(fd[1], today, sizeof(dayjob_t));

			// Decrement remain time
			for(line = 0; line < 3; line++)
				if(todayOrder[line] != NULL)
					todayOrder[line]->remainDay--;
		}
		close(fd[1]);
		wait(NULL);
	} else {
		// Child process
		// Close unnessary pipe end
		close(fd[1]);
		fileOutput(fd, "SRT", outputPath);
	}

	// Prepare a list of dropped order(s)
	resultScheduleTable->droppedOrderCount = 0;
	// Count number of dropped order(s)
	nodePointer = cloneJobQueue->head;
	while(nodePointer != NULL) {
		if(nodePointer->data.remainDay > 0)
			resultScheduleTable->droppedOrderCount++;
		nodePointer = nodePointer->next;
	}
	resultScheduleTable->droppedOrder = malloc(sizeof(int) * resultScheduleTable->droppedOrderCount);
	// Mark the orderID of dropped order(s)
	nodePointer = cloneJobQueue->head;
	i = 0;
	while(nodePointer != NULL) {
		if(nodePointer->data.remainDay > 0)
			resultScheduleTable->droppedOrder[i++];
		nodePointer = nodePointer->next;
	}

	clearQueue(cloneJobQueue);
}
