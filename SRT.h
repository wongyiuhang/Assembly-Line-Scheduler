#include <stdbool.h>
#include <string.h>

#include "struct.h"
#include "global.h"

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
			nextNode->data.startDate <= day // Find an order exist on or before the day
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
	int day, line;
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
			nodePointer = SRT_find(jobQueue, day, todayOrder);
			if(nodePointer == NULL)
				break;
			today->orderID[line] = nodePointer->data.id;
			todayOrder[line] = &nodePointer->data;
		}

		// Decrement remain time
		for(line = 0; line < 3; line++)
			if(todayOrder[line] != NULL)
				todayOrder[line]->remainDay--;
	}
}
