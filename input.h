#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#pragma once


void addOrder(char *orderID, char *startDateStr, char *endDateStr,char *pdNameStr,int quantity,struct Queue* queue){
	struct Order newOrder; 
	printf("**** addOrder ****\n");

	// save orderData as string
	strcpy(newOrder.startDateStr,startDateStr);
	strcpy(newOrder.endDateStr,endDateStr);
	strcpy(newOrder.pdNameStr,pdNameStr);
	strcpy(newOrder.orderID,orderID);

	// save orderData as int
	startDateStr[0] = '0';
	endDateStr[0]   = '0';
	orderID[0]      = '0';
	printf("startDateStr : %s\n",startDateStr );
	printf("endDateStr : %s\n",endDateStr );
	printf("orderID : %s\n",orderID );

	newOrder.startDate = atoi(startDateStr);
	newOrder.endDate   = atoi(endDateStr);
	newOrder.id        = atoi(orderID);
	newOrder.quantity  = quantity;
	newOrder.pdName    = pdNameStr[strlen(pdNameStr)-1];
	enqueue(queue, &newOrder);

	// printf("queue %d\n",queue->head->data.quantity);


	printf("**** End addOrder ****\n");
}
// *********************
// * end Projram	   *
// *********************

void endProgram(){

	// *********************
	// * Free var here	   *
	// *********************
	printf("Bye-bye!");
}



void substr(char *dest, const char* src, unsigned int start, unsigned int cnt) {
	strncpy(dest, src + start, cnt);
	dest[cnt] = 0;
}
int getFirstSpace(char * inStr){
	int i ;
	for (i = 0; i < strlen(inStr); i++){
		if (inStr[i] == ' ') {			
			return i;
		}
	}
	return  strlen(inStr)-1;
}

int checkCommandExist(char * inStr){
	const char *commandSet[] = {"addOrder","addBatchOrder","runALS","printReport","endProgram"};	
	int i ;
	char firComPart[20];
	int firstSpace = getFirstSpace(inStr);
	substr(firComPart, inStr, 0, firstSpace);

	
	for ( i = 0; i < 5; i++){
		if (strcmp(firComPart,commandSet[i]) == 0)
		{				
			return i;
		}
	}
	return -1;	
}



// addOrder command Reading and Check

void cm_addOrder(char * command,struct Queue* queue){
	printf("Command : %s\n",command );

	char orderID[6], startDateStr[5],endDateStr[5], pdNameStr[10],pdName;	
	int quantity,startDate,endDate,id; 
	sscanf( command, "addOrder %s%s%s%s%d", orderID, startDateStr, endDateStr,pdNameStr, &quantity );
	startDateStr[4] = 0;
	endDateStr[4]   = 0;
	orderID[5]      = 0;
	pdNameStr[9]    = 0;
	// *********************
	// * Check Here		   *
	// *********************
	addOrder(orderID, startDateStr, endDateStr,pdNameStr, quantity ,queue);
}
void cm_addBatchOrder(char * command,struct Queue* queue){
	char fileName[30],orderID[6], startDateStr[5],endDateStr[5], pdNameStr[10],pdName;	
	char line[256];
	int quantity;
	sscanf( command, "addBatchOrder  %s ", fileName);
	printf("fileName : %s\n",fileName );


	FILE *file;
	file = fopen(fileName, "r");
	while (fgets(line, sizeof(line), file)) {
		sscanf( line, "%s%s%s%s%d", orderID, startDateStr, endDateStr, pdNameStr, &quantity);
		// *********************
		// * Check Here		   *
		// *********************
		addOrder(orderID, startDateStr, endDateStr,pdNameStr, quantity, queue);
	}
		fclose(file);
	printf("**** End addBatchOrder ****\n");
}

void cm_printReport(char * command){
	char fileName[30], line[256];
	sscanf( command, "printReport > %s  ", fileName);

	FILE *file;
	file = fopen(fileName, "w");

	// *********************
	// * print Report	   *
	// *********************

	fclose(file);
}

void cm_runAls(char * command){


	char fileName[30],algo[6],algopar,dummy[50];
	int timeQuan;	
	sscanf(command,"runALS %s %[^\n]",algo,dummy);


	if (strcmp(algo,"-FCFS") == 0){
		sscanf( dummy, "| printSchedule >%s\n",fileName );
		printf("ALGO :%s\n",algo);
		printf("fileName: %s\n",fileName);

	}else if (strcmp(algo,"-PR") == 0){
		sscanf(dummy," %c | printSchedule > %s",&algopar,fileName);   
		printf("ALGO :%s\n",algo);
		printf("algopar: %c\n",algopar);
		printf("fileName: %s\n",fileName);
	}else if (strcmp(algo,"-RR") == 0){
		sscanf(dummy," %d | printSchedule > %s",&timeQuan,fileName); 
		printf("ALGO :%s\n",algo);      
		printf("timess: %d\n",timeQuan);
		printf("fileName: %s\n",fileName);
	}else if (strcmp(algo,"-SJF") == 0){
		sscanf( dummy, "| printSchedule >%s\n",fileName );
		printf("ALGO :%s\n",algo);
		printf("fileName: %s\n",fileName);

	}else if (strcmp(algo,"-SRF") == 0){
		sscanf( dummy, "| printSchedule >%s\n",fileName );  
		printf("ALGO :%s\n",algo);
		printf("fileName: %s\n",fileName);

	}

	// FILE *file;
	// file = fopen(fileName, "w");

	// *********************
	// * print Report	   *
	// *********************

	// fclose(file);
	
}

// void getFileNameInCommand(char* string,char *fileName) {
// 	int i, start, last, maxSpaceCount = 0;
// 	// char dest[50];

// 	for (i = strlen(string)-1 ; i <0 ; i--)
// 	{
// 		if (string[i] == ' ') {
// 			substr(fileName, string, i, strlen(string)-1);
// 			fileName[strlen(fileName)] = '\0';
// 		}
// 	}

// }


// void getAlgoInCommand(char* string,char *algo) {
// 	int i, start = 0, last, maxSpaceCount = 0;
// 	// char dest[50];

// 	for (i = 0 ; i <strlen(string)-1 ; i++)
// 	{
// 		if (string[i] == ' ') {
// 			maxSpaceCount++;
// 		}
// 		if (string[i] == '-') {
// 			start = i;
// 		}
// 		if (maxSpaceCount == 2) {
// 			last = i;
// 			break;
// 		}
// 	}

// 	substr(dest, string, start + 1, last);
// 	algo[strlen(algo)] = '\0';		
// }
// void getAlgoPamInCommand(char* string,char *algopar) {
// 	int i, start = 0, last, maxSpaceCount = 0;
// 	// char dest[50];

// 	for (i = 0 ; i <strlen(string)-1 ; i++)
// 	{
// 		if (string[i] == ' ') {
// 			maxSpaceCount++;
// 		}
// 		if (maxSpaceCount == 2) {
// 			start = i;
// 		}
// 		if (maxSpaceCount == 3) {
// 			start = i;
// 			break;
// 		}

// 	}

// 	substr(dest, string, start + 1, last);
// 	algopar[strlen(algo)] = '\0';		
// }
// *********************
// * Add Order		   *
// *********************
