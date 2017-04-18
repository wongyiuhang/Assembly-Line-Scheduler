#include "struct.h"

/***************************************************
 *                                                 *
 *     Input: Job queue [struct Queue*]            *
 *    Output: Schedule table [struct Schedule*]    *
 *                                                 *
 ***************************************************/

struct Schedule* SRT_algorithm(struct Queue* jobQueue) {
	int day, line;
	struct Schedule* scheduleTable = malloc(sizeof(schedule_t));
	struct Queue* cloneJobQueue = jobQueue;
	//cloneJobQueue = cloneQueue(jobQueue);

	for(day = 0; day < 60; day++) {
		// Initialise value
		for(line = 0; line < 3; line++)
			scheduleTable->day[day].orderID[line] = -1;
	}

	return scheduleTable;
}
