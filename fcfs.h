#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "global.h"

#include "struct.h"


int daysleft(int num){
	if(num%PRODUCT_PER_DAY == 0) {return num/PRODUCT_PER_DAY;}
	else{return (num/PRODUCT_PER_DAY+1);}
}

//assume order are ordered by start date
void FCFS_algorithm(struct Queue* jobQueue, char* outputPath, struct Schedule* resultScheduleTable){
	//********************************************************************************************
	// Initialization
	printf("Fuck this program");
	static const struct Order EmptyOrder = {0,'\0','\0','\0','\0',NULL,0,'\0',0,0,0};
	struct Schedule sixtydaysschedule;
	// FCFS algorithm, assume jobQueue's job start date is in ascending order
	struct Queue* cloneJobQueue = cloneQueue(jobQueue);
	strcpy(resultScheduleTable->algo, "FCFS");
	
	
	//Current Date of process
	int currentDate;
	
	
	//handle the first process in queue
	struct Order handleprocess;
	dequeue(cloneJobQueue, &handleprocess);
	handleprocess.remainDay = daysleft(handleprocess.quantity);
	struct Order running_process[3];
	int flag[3] = {0,0,0};
		
	//create pipe and child and initialize them
	int fd[2], pid;
	if (pipe(fd) < 0) {printf("Pipe creation error.");}
	pid = fork();
	if ( pid < 0 ) { printf("Child creation error\n"); exit(1);}
	//parent process.  fd[0] for parent to read
	else if ( pid > 0 ) { close(fd[1]);}
	//child process.  fd[1] for child to write 
	else { close(fd[0]);}
	
	//********************************************************************************************	

	
	if (pid > 0) {
		// run 60 times represent 60 days job
		printf("Parent:1");
		for(currentDate=1; currentDate <= NUM_OF_DAY; currentDate++) {
			char tochild[16];
			printf("P2");
				
			//end of last day.  Process time needed for each process minus 1.
			
			if(running_process[0].remainDay > 0 ) {running_process[0].remainDay--;}
			if(running_process[1].remainDay > 0 ) {running_process[1].remainDay--;}
			if(running_process[2].remainDay > 0 ) {running_process[2].remainDay--;}
			
			//check whether endtime come or the process is finished.  If end time come, drop the process
			if (running_process[0].remainDay < 0 || running_process[0].endDate > currentDate) {running_process[0] = EmptyOrder;}
			if (running_process[1].remainDay < 0 || running_process[1].endDate > currentDate) {running_process[1] = EmptyOrder;}
			if (running_process[2].remainDay < 0 || running_process[2].endDate > currentDate) {running_process[2] = EmptyOrder;}
			
			// Handle new coming process
			while (handleprocess.startDate >= currentDate){ // when break, it can put data to child to pass data
				//when the new order's start date exceed currentDate, dequeue next order
				
				printf("P344");
				while (handleprocess.startDate < currentDate) { 
					//function: check whether it is null
					int result = dequeue(jobQueue, &handleprocess);
					handleprocess.remainDay = daysleft(handleprocess.quantity);
					// when no more order available, break it
					// 1 = null
					if(!result) {break;}
					
				}
				
				//parent process: handle schedule
				// Is process free? if some of them are not busy, check next condition.  Otherwise go to next day
				if (running_process[0].remainDay == 0 || running_process[1].remainDay == 0 || running_process[2].remainDay == 0){
					// Check whether the execution process having equipment conflict with others
					if (running_process[0].remainDay != 0) {
						printf("AA1");
						if(checkEqiuipConflict(running_process[0].prod,handleprocess.prod)) {
						strcpy(tochild, running_process[0].orderID); 
						strcat(tochild, running_process[1].orderID); 
						strcat(tochild, running_process[2].orderID); 
						write(fd[1],tochild,strlen(tochild)); 
						break;
						}
					}
					if (running_process[1].remainDay != 0) {
						printf("AA2");
						if(checkEqiuipConflict(running_process[0].prod,handleprocess.prod)) {
						strcpy(tochild, running_process[0].orderID); 
						strcat(tochild, running_process[1].orderID); 
						strcat(tochild, running_process[2].orderID); 
						write(fd[1],tochild,strlen(tochild)); 
						break;
						}
					}
					if (running_process[2].remainDay != 0) {
						printf("AA3");
						if(checkEqiuipConflict(running_process[0].prod,handleprocess.prod)) {
						strcpy(tochild, running_process[0].orderID); 
						strcat(tochild, running_process[1].orderID); 
						strcat(tochild, running_process[2].orderID); 
						write(fd[1],tochild,strlen(tochild)); 
						break;
						}
					}
					// All conditions satisfy that process can put to the line. 
					if (running_process[0].remainDay != 0) {
						printf("AA4");
						running_process[0] = handleprocess; 
						while (dequeue(cloneJobQueue, &handleprocess)){
							continue;
						} 
						continue;}
					if (running_process[1].remainDay != 0) {printf("AA5");running_process[1] = handleprocess; while (dequeue(cloneJobQueue, &handleprocess)){continue;} continue;}
					if (running_process[2].remainDay != 0) {printf("AA6");running_process[2] = handleprocess; while (dequeue(cloneJobQueue, &handleprocess)){continue;} continue;}
				}
				else{ 
					printf("AA6");
					strcpy(tochild, running_process[0].orderID); 
					strcat(tochild, running_process[1].orderID); 
					strcat(tochild, running_process[2].orderID); 
					write(fd[1],tochild,strlen(tochild)); 
					break;
				}
				break;
			}
			
		}	
	}
	else { //child process: use pipe to output the process to txt (need typing)
		
		struct DayJob buffer;
		FILE* file = fopen(outputPath, "w+");

		// Print header
		fprintf(file, "Algorithm: FCFS\n");
		fprintf(file, "Day: %d\n\n", NUM_OF_DAY);
		fprintf(file, "\t\t%5s\t%5s\t%5s\n", "L1", "L2", "L3");

		for(currentDate=0; currentDate < NUM_OF_DAY; currentDate++) {
			
			printf("C1");
			char temp[16],orderID_1[6],orderID_2[6],orderID_3[6];
			read(fd[0],temp,15);
			int i, j;
			for (i = 0; i<15; i++){
				if(i>=1 && i<5)	{strcat(orderID_1,temp[i]);}
				else if (i>=6 && i<10) {strcat(orderID_2,temp[i]);}
				else if (i>=11 && i<15){strcat(orderID_3,temp[i]);}
			}
			
			resultScheduleTable->days[currentDate].orderID[0] = atoi(orderID_1);
			resultScheduleTable->days[currentDate].orderID[1] = atoi(orderID_2);
			resultScheduleTable->days[currentDate].orderID[2] = atoi(orderID_3);
			
		
			buffer.orderID[0] = atoi(orderID_1);
			buffer.orderID[1] = atoi(orderID_2);
			buffer.orderID[2] = atoi(orderID_3);
			
			char day[3][6];
			for(j = 0; j < 3; j++) {
				if(buffer.orderID[j] == 0)
					strcpy(day[j], "-");
				else
					sprintf(day[j], "%05d", buffer.orderID[j]);
			}
			fprintf(file, "Day %02d:\t%5s\t%5s\t%5s\n", i + 1, day[0], day[1], day[2]);	
		}
		fclose(file); 
		
	}
	
	
	
	
	
	//Close the pipe and child
	if (pid > 0) { 
		close(fd[1]);
	}
	else{ 
		close(fd[0]);
		wait(NULL);
		exit(0); // need change
	}
	
}