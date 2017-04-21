#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
//assume order are ordered by start date
void fcfs(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable, struct Product* pdHead){
	//********************************************************************************************
	// Initialization
	
	static const struct Order* EmptyOrder = {0,'\0','\0','\0','\0',NULL,0,'\0',0,0,0};
	struct Schedule sixtydaysschedule;
	// FCFS algorithm, assume jobQueue's job start date is in ascending order
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	
	//Current Date of process
	int currentDate;
	
	
	//handle the first process in queue
	struct Order handleprocess = dequeue(cloneJobQueue);
	struct Order running_process[3];
		
	//create pipe and child and initialize them
	int fd[2], pid;
	pid = fork();
	if ( pid < 0 ) { printf("Pipe creation error\n"); exit(1);}
	// child process
	else if ( pid > 0 ) { close(fd[1]);}
	//parent process
	else { close(fd[0]);}
	
	//********************************************************************************************	


	
	// run 60 times represent 60 days job
	for(currentDate=1; currentDate <= NUM_OF_DAY; currentDate++) {
	
			
		//end of last day.  Process time needed for each process minus 1.
		
		if(running_process[0].remainDay > 0 ) {running_process[0].remainDay--;}
		if(running_process[1].remainDay > 0 ) {running_process[1].remainDay--;}
		if(running_process[2].remainDay > 0 ) {running_process[2].remainDay--;}
		
		//check whether endtime come or the process is running.  If end time come, drop the process
		if (running_process[0].remainDay < 0 || running_process[0].endDate == currentDate) {running_process[0] = EmptyOrder;}
		if (running_process[1].remainDay < 0 || running_process[1].endDate == currentDate) {running_process[1] = EmptyOrder;}
		if (running_process[2].remainDay < 0 || running_process[2].endDate == currentDate) {running_process[2] = EmptyOrder;}
		
		// Handle new coming process
		while (true){ // when break, it can put data to child to pass data
			//when the new order's start date exceed currentDate, dequeue next order
			while (handleprocess.startDate < currentDate) { 
				handleprocess = dequeue(jobQueue);
				// when no more order available, break it
				if(&handleprocess == NULL) {
					break;
				}
			}
			//parent process: handle schedule
			if (pid > 0)	{	
				// Is process free? if some of them are not busy, check next condition.  Otherwise go to next day
				if (running_process[0].remainDay == 0 || running_process[1].remainDay == 0 || running_process[2].remainDay == 0){
					// Check whether the execution process having equipment conflict with others
					if (running_process[0].remainDay != 0) {if(checkEqiuipConflict(running_process[0].prod,handleprocess.prod)) {break;}}
					if (running_process[1].remainDay != 0) {if(checkEqiuipConflict(running_process[1].prod,handleprocess.prod)) {break;}}
					if (running_process[2].remainDay != 0) {if(checkEqiuipConflict(running_process[2].prod,handleprocess.prod)) {break;}}
					// All conditions satisfy that process can put to the line. 
					if (running_process[0].remainDay != 0) {running_process[0] = handleprocess; handleprocess = dequeue(cloneJobQueue); continue;}
					if (running_process[1].remainDay != 0) {running_process[1] = handleprocess; handleprocess = dequeue(cloneJobQueue); continue;}
					if (running_process[2].remainDay != 0) {running_process[2] = handleprocess; handleprocess = dequeue(cloneJobQueue); continue;}
				}
				else{ break;}
			}
			//child process: use pipe to output the process to txt (need typing)
			else {
				break;
			
			
			
				
			}
		}
	}	
	
	
	//Close the pipe and child
	if (pid > 0) { 
		close(fd[0]);
	}
	else{ 
		close(fd[1]);
		wait(NULL);
		exit(0); // need change
	}
	
}