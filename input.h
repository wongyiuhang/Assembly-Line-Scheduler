#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "global.h"
#include "output.h"
#include "SRT.h"
#include "fcfs.h"


#pragma once

void addOrder(char* orderID, char* startDateStr, char* endDateStr, char* pdNameStr, int quantity, struct Queue* q, struct Product* pdhead){
	struct Order newOrder; 
	printf("**** addOrder ****\n");
	if (orderExist(q,orderID)){
		printf("This order was existed\n");
		return;
	}
	strcpy(newOrder.startDateStr,startDateStr);
	strcpy(newOrder.endDateStr,endDateStr);
	strcpy(newOrder.pdNameStr,pdNameStr);
	strcpy(newOrder.orderID,orderID);
	startDateStr[0] = '0';
	endDateStr[0]   = '0';
	orderID[0]      = '0';

	if (atoi(endDateStr)>NUM_OF_DAY){
		printf("This order was out of end date\n");
		return;
	}


	// save orderData as string

	// save orderData as int

	printf("startDateStr : %s\n",startDateStr );
	printf("endDateStr : %s\n",endDateStr );
	printf("orderID : %s\n",orderID );

	newOrder.startDate = atoi(startDateStr);
	newOrder.endDate   = atoi(endDateStr);
	newOrder.id        = atoi(orderID);
	newOrder.quantity  = quantity;
	newOrder.pdName    = pdNameStr[strlen(pdNameStr)-1];
	newOrder.prod      = searchProduct(pdhead, newOrder.pdName);
	printf("product : %s\n",newOrder.prod->nameStr );
	enqueue(q, &newOrder);

	// printf("queue %d\n",queue->head->data.quantity);


	printf("**** End addOrder ****\n");
}
// *********************
// * end Projram	   *
// *********************

void endProgram(struct Queue* queue,struct Product *pdHead){
	// *********************
	// * Free var here	   *
	// *********************
	clearQueue(queue);
	struct Product * current = pdHead;
	while(current != NULL) {
		struct Product * temp = current;
		current = current->next;
		free(temp->equipments);
		free(temp);
	}


	printf("Bye-bye!");
}


// function substring (result string , soucre string . strat index , last index)
void substr(char *dest, const char* src, unsigned int start, unsigned int cnt) {
	strncpy(dest, src + start, cnt);
	dest[cnt] = 0;
}
// substring (result string )
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
	printf("%s\n",firComPart);
	for ( i = 0; i < 5; i++){
		if (strcmp(firComPart,commandSet[i]) == 0)
		{				
			return i;
		}
	}
	return -1;	
}



// read addOrder Command and parameter checking 
void cm_addOrder(char * command,struct Queue* queue,struct Product * products){
	printf("Command : %s\n",command );

	char orderID[6], startDateStr[5],endDateStr[5], pdNameStr[10],pdName;	
	int quantity,startDate,endDate,id; 
	sscanf( command, "addOrder %s%s%s%s%d", orderID, startDateStr, endDateStr,pdNameStr, &quantity);
	startDateStr[4] = 0;
	endDateStr[4]   = 0;
	orderID[5]      = 0;
	pdNameStr[9]    = 0;
	// *********************
	// * Check Here		   *
	// *********************
	addOrder(orderID, startDateStr, endDateStr,pdNameStr, quantity ,queue, products);
}
// read addBatchOrder Command and parameter checking 
void cm_addBatchOrder(char * command,struct Queue* queue,struct Product * products){
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
		addOrder(orderID, startDateStr, endDateStr,pdNameStr, quantity, queue,products);
	}
	fclose(file);
	printf("**** End addBatchOrder ****\n");
}
// read printReort Command
void cm_printReport(char * command,struct Queue * queue,struct Schedule * scheduleTable){
	char fileName[30], line[256];
	sscanf( command, "printReport > %s  ", fileName);
	printReport(fileName,queue,scheduleTable);
}
// _addBatchOrder(command,queue,pdHead)read runAls Command
void cm_runAls(char * command,struct Queue * queue,struct Schedule * resultScheduleTable){


	char fileName[30],algo[6],algopar,dummy[50];
	int timeQuan;	
	sscanf(command,"runALS %s %[^\n]",algo,dummy);


	if (strcmp(algo,"-FCFS") == 0){
		sscanf( dummy, "| printSchedule >%s\n",fileName );  
		printf("ALGO :%s\n",algo);
		printf("fileName: %s\n",fileName);
		strcpy(resultScheduleTable->algo,"FCFS");
		FCFS_algorithm(queue, fileName,resultScheduleTable);



	}else if (strcmp(algo,"-PR") == 0){
		sscanf(dummy," %c | printSchedule > %s",&algopar,fileName);   
		printf("ALGO :%s\n",algo);
		printf("algopar: %c\n",algopar);
		printf("fileName: %s\n",fileName);
		strcpy(resultScheduleTable->algo,"PR");

	}else if (strcmp(algo,"-RR") == 0){
		sscanf(dummy," %d | printSchedule > %s",&timeQuan,fileName); 
		printf("ALGO :%s\n",algo);      
		printf("timess: %d\n",timeQuan);
		printf("fileName: %s\n",fileName);
		strcpy(resultScheduleTable->algo,"RR");

	}else if (strcmp(algo,"-SJF") == 0){
		sscanf( dummy, "| printSchedule >%s\n",fileName );
		printf("ALGO :%s\n",algo);
		printf("fileName: %s\n",fileName);
		strcpy(resultScheduleTable->algo,"SJT");


	}else if (strcmp(algo,"-SRT") == 0){
		sscanf( dummy, "| printSchedule >%s\n",fileName );  
		printf("ALGO :%s\n",algo);
		printf("fileName: %s\n",fileName);
		strcpy(resultScheduleTable->algo,"SRT");
		SRT_algorithm(queue, fileName,resultScheduleTable);
	}

	// FILE *file;
	// file = fopen(fileName, "w");

	// *********************
	// * print Report	   *
	// *********************

	// fclose(file);
}

int compare( const void* a, const void* b)
{
	return ( *(int*)a - *(int*)b );
}

void initProdConfig(struct Product * pdHead){
	char line[256],nameStr[10],dummy[100],name,shitStr[12];
	int *equipPtr,equipCount;
	int i,j,index;
	struct Product newPd;
	FILE *file;
	file = fopen("product.config", "r");
	for ( index = 1; fgets(line, sizeof(line), file) ; index++)
	{
		sscanf( line, "%9s:%d%s", nameStr,&equipCount,dummy);
		name = nameStr[8];
		equipPtr = malloc(equipCount * sizeof(int) );

		for (i = 0; i < equipCount ; i++ )
			sscanf( dummy, ",Equipment_%d%s", &equipPtr[i],dummy);
		

		qsort( equipPtr, equipCount, sizeof(int), compare ); // sort array

		newPd.id = index;
		strcpy(newPd.nameStr,nameStr);
		newPd.name = name;
		newPd.equipments = equipPtr;
		newPd.equipmentCount = equipCount;
		productPush(pdHead,&newPd);
	}

	fclose(file);

}

