
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"

//first: handle the array / linked list that store the process: when time comes, put the process in queue
//假設 order are ordered by start date
//second: run the process according to the order(give to the child) (if child1 return free, run the process, otherwise child2, otherwise child3, otherwise continue)
int fcfs(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable, struct Pdhead* product){
	
	// direct copy 
	Schedule sixtydaysschedule;
	Queue* cloneJobQueue = cloneQueue(jobQueue);
	
	//time of process
	int currenttime = 1;
	
	//create pipe and child and initialize them
	int fd[2], pid;
	pid = fork();
	if (pid < 0 ) {printf("Pipe creation error\n"); exit(1); return 0;}
	// child process
	else if (pid > 0) {
		close(fd[1]);
	}
	//parent process
	else {
		close(fd[0]);
	}
	
	//process
	
	
	//temp
	Order handleprocess = dequeue(jobQueue);
	
	while (currenttime<=60) {
		
		while (handleprocess.startDate == currenttime){
			
			//parent process to handle schedule
			if (pid > 0)	{	
				handleprocess = dequeue(order);
			}
			//child process to handle output
			else {
				
			
			
			
				
			}
		}
	}
	
	//Close the pipe and child
	if (pid > 0) { close(fd[0]);}
	else { close(fd[1]);}
	// correct
	return 1;

}
