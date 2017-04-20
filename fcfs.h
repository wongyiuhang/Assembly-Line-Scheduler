
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"

//first: handle the array / linked list that store the process: when time comes, put the process in queue
//假設 order are ordered by start date
//second: run the process according to the order(give to the child) (if child1 return free, run the process, otherwise child2, otherwise child3, otherwise continue)
int fcfs(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable, struct Pdhead* product){
	//********************************************************************************************
	// Initialization
	Schedule sixtydaysschedule;
	// FCFS algorithm, assume jobQueue's job start date is in ascending order
	Queue* cloneJobQueue = cloneQueue(jobQueue);
	
	//Current Date of process
	int currentDate;
	
	//process
	
	
	//handle the first process in queue
	Order handleprocess = dequeue(jobQueue);
	Order running_process[3];
	
	//create pipe and child and initialize them
	int fd[2], pid;
	pid = fork();
	if ( pid < 0 ) { printf("Pipe creation error\n"); exit(1); return 0;}
	// child process
	else if ( pid > 0 ) { close(fd[1]);}
	//parent process
	else { close(fd[0]);}
	
	
	
				handleprocess = dequeue(order);
	//********************************************************************************************	


	
	// run 60 times represent 60 days job
	for(currentDate=1; currentDate <= 60; currentDate++) {
		//end of last day.  Process time needed for each process minus 1.
		if(processtime[0] > 0 ) {running_process[0].remainDay--;}
		if(processtime[1] > 0 ) {running_process[1].remainDay--;}
		if(processtime[2] > 0 ) {running_process[2].remainDay--;}
		
		//check whether endtime come or the process running.  If end time come, drop the process
		if (running_process[0].remainDay < 0 running_process[0].endDate == currentDate) {running_process[0] = NULL;}
		if (running_process[1].remainDay < 0 running_process[1].endDate == currentDate) {running_process[1] = NULL;}
		if (running_process[2].remainDay < 0 running_process[2].endDate == currentDate) {running_process[2] = NULL;}
		
		// Handle new coming process
		while (true){
			while (handleprocess.startDate < currentDate) { handleprocess = dequeue(jobQueue);}
			//parent process: handle schedule
			if (pid > 0)	{	
				// Is process free? if some of them are not busy, check next condition.  Otherwise go to next day
				if (run_process[0].remainDay == 0 || running_process[1].remainDay == 0 || processtime[2].remainDay == 0){
					// Check whether the execution process having equipment conflict with others
					if (running_process[0].remainDay != 0) {if(checkEqiuipConflict(running_process[0].prod,handleprocess.prod)) {break;}
					if (running_process[1].remainDay != 0) {if(checkEqiuipConflict(running_process[1].prod,handleprocess.prod)) {break;}
					if (running_process[2].remainDay != 0) {if(checkEqiuipConflict(running_process[2].prod,handleprocess.prod)) {break;}
					// All conditions satisfy that process can put to the line.  (Needed to clone order?) 
					if (running_process[0].remainDay != 0) {running_process[0] = handleprocess; handleprocess = dequeue(jobQueue); continue;}
					if (running_process[1].remainDay != 0) {running_process[1] = handleprocess; handleprocess = dequeue(jobQueue); continue;}
					if (running_process[2].remainDay != 0) {running_process[2] = handleprocess; handleprocess = dequeue(jobQueue); continue;}
				}
				else{ break;}
			}
			//child process: use pipe to output the process to txt
			else {
				
			
			
			
				
			}
		}
		
	}
	
	//Close the pipe and child
	if (pid > 0) { close(fd[0]);}
	else { close(fd[1]); wait(NULL); exit();}
	// correct
	return 1;
	
	struct Order nextorder(Queue* cloneJobQueue) {
		struct Order nextorder = dequeue(jobQueue);
		if (nextorder.endDate)
	}

}