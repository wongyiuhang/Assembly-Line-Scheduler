#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #include "struct.h"
#pragma once






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
	int firstSpace;
	substr(firComPart, inStr, 0, firstSpace);

	for ( i = 0; i < 5; ++i){
		if (strcmp(firComPart,commandSet[i])!=0)
		{
			return i;
		}
	}
	return -1;	
}



// addOrder command Reading and Check

void cm_addOrder(char * command){
	char orderID[6], startDateStr[5],endDateStr[5], pdNameStr[10],pdName;	
	int quantity,startDate,endDate,id; 
	sscanf( command, "addOrder %s %s %s %s %d", orderID, startDateStr, endDateStr,pdNameStr, quantity );
	// *********************
	// * Check Here		   *
	// *********************
	addOrder(orderID, startDateStr, endDateStr, quantity);
}
void cm_addBatchOrder(char * command){
	char fileName[30],orderID[6], startDateStr[5],endDateStr[5], pdNameStr[10],pdName;	
	char line[256];
	int quantity;
	sscanf( command, "addBatchOrder %s ", fileName);

	FILE *file;
	file = fopen(fileName, "r");
	while (fgets(line, sizeof(line), file)) {
		sscanf( line, "%s%s%s%s%s", orderID, startDateStr, endDateStr,pdNameStr, quantity );
		// *********************
		// * Check Here		   *
		// *********************
		addOrder(orderID, startDateStr, endDateStr,pdNameStr, quantity);
		fclose(file);
	}
	
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
	char fileName[30], line[256],ans,algo[6],algopar[3] ;
	// sscanf( command, "runALS –PR n | printSchedule > %s", fileName);
	// const char *commandSet[] = {"FCFS","S","printReport","endProgram"};		
	getFileNameInCommand(command,fileName);
	getAlgoInCommand(command,algo);
	if (strcmp(algo,"FCFS") == 0){
		printf("ALGO :%s",algo);
	}else if (strcmp(algo,"PR") == 0){
		getAlgoPamInCommand(command,algopar);
		printf("ALGO :%s",algo);
		printf("algopar :%s",algopar);
		char pam = algopar[0];
	}else if (strcmp(algo,"RR") == 0){
		getAlgoPamInCommand(command,algopar);
		printf("ALGO :%s",algo);
		printf("algopar :%s",algopar);
		int pam = atoi(algopar);
	}

	// FILE *file;
	// file = fopen(fileName, "w");

	// *********************
	// * print Report	   *
	// *********************

	// fclose(file);
	
}

void getFileNameInCommand(char* string,char *fileName) {
	int i, start, last, maxSpaceCount = 0;
	// char dest[50];

	for (i = strlen(string)-1 ; i <0 ; i--)
	{
		if (string[i] == ' ') {
			substr(fileName, string, i, strlen(string)-1);
			fileName[strlen(fileName)] = '\0';
		}
	}
	
}
void getAlgoInCommand(char* string,char *algo) {
	int i, start = 0, last, maxSpaceCount = 0;
	// char dest[50];

	for (i = 0 ; i <strlen(string)-1 ; i++)
	{
		if (string[i] == ' ') {
			maxSpaceCount++;
		}
		if (string[i] == '-') {
			start = i;
		}
		if (maxSpaceCount == 2) {
			last = i;
			break;
		}
	}

	substr(dest, string, start + 1, last);
	algo[strlen(algo)] = '\0';		
}
void getAlgoPamInCommand(char* string,char *algopar) {
	int i, start = 0, last, maxSpaceCount = 0;
	// char dest[50];

	for (i = 0 ; i <strlen(string)-1 ; i++)
	{
		if (string[i] == ' ') {
			maxSpaceCount++;
		}
		if (maxSpaceCount == 2) {
			start = i;
		}
		if (maxSpaceCount == 3) {
			start = i;
			break;
		}

	}

	substr(dest, string, start + 1, last);
	algopar[strlen(algo)] = '\0';		
}
// *********************
// * Add Order		   *
// *********************
void addOrder(char *orderID, char *startDateStr, char *endDateStr,char *pdNameStr,int quantity){
	struct Order order; 

	// save orderData as string
	strcpy(order.startDateStr,startDateStr);
	strcpy(order.endDateStr,endDateStr);
	strcpy(order.pdNameStr,pdNameStr);
	strcpy(order.orderID,orderID);

	// save orderData as int
	startDateStr[0] = '0';
	endDateStr[0]   = '0';
	orderID[0]      = '0';

	order.startDateStr = atoi(startDateStr);
	order.endDateStr   = atoi(endDateStr);
	order.quantity     = quantity;
	order.pdName       = pdNameStr[strlen(pdNameStr)-1];
	// enqueue(queue, &order);
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