#include "struct.h"
#include "global.h"

#pragma once

void fileOutput(int fd[2], char* algo, char* filePath) {
	int i, j;
	struct DayJob buffer;
	FILE file* = fopen(filePath, "w+");

	// Print header
	printf("Algorithm: %s\n", algo);
	printf("Day: %d\n\n", NUM_OF_DAY);
	printf("\t\t%5s\t%5s\t%5s\n", "L1", "L2", "L3");

	// Print each day
	for(i = 0; i < NUM_OF_DAY; i++) {
		if(read(fd[0], &buffer, sizeof(dayjob_t)) < 1)
			break;
		char day[3][6];
		for(j = 0; j < 3; j++) {
			if(buffer.orderID[j] == 0)
				strcpy(day[j], "-");
			else
				sprintf(day[j], "%05d", buffer.orderID[j]);
		}
		printf("Day %02d:\t%s\t%s\t%s\n", day[0], day[1], day[2]);
	}

	fclose(file);
	close(fd[0]);
}
