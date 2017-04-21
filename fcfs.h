#include "struct.h"
#include "global.h"

#pragma once

int daysleft(int num){
	return (num%PRODUCT_PER_DAY) ? (num/PRODUCT_PER_DAY+1) : num/PRODUCT_PER_DAY;
}

//assume order are ordered by start date
void FCFS_algorithm(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable){
	// Initialization
	int i, j;
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	
	for(i = 0; i < NUM_OF_DAY; i++) {
		for(j = 0; j < 3; j++) {
		}
	}
}