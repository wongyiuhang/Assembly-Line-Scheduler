#include "struct.h"

/***************************************************
 *                                                 *
 *     Input: Job queue [struct Queue*]            *
 *    Output: Schedule table [struct Schedule*]    *
 *                                                 *
 ***************************************************/

void SRT_algorithm(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable) {
	int day, line;
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);

	for(day = 0; day < 60; day++) {
		// Initialise value
		for(line = 0; line < 3; line++)
			resultScheduleTable->days[day].orderID[line] = -1;
	}
}
