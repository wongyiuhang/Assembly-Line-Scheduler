#include "struct.h"
#include "global.h"

#pragma once

void fileOutput(int fd[2], char* algo) {
	struct DayJob buffer;
	while(read(fd[0]), &buffer, sizeof(dayjob_t)) {
		
	}
}
