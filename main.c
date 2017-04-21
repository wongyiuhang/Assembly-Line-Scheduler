#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#include "input.h"
#include "global.h"




int main(int argc, char *argv[]){
	printf("\n");
	printf("\t\t ~~WELCOME TO ALS~~ \n");
	printf("\n");
	struct Product * pdHead = newProduct(); // product config initialize
	initProdConfig(pdHead);
	struct Queue* queue = newQueue(); // Order Queue
	bool keepLoop = true;

	struct Schedule resultScheduleTable[MAX_SCHEDULE_TABLE]; // Schedule tabel
	initScheduleTable(resultScheduleTable,MAX_SCHEDULE_TABLE);
	int schedTabIdx = 0;
	char command[100];
	while(keepLoop){
		printf("Please enter: ");
		fflush(stdout);
		if (scanf("%[^\n]",command)!=1){
			printf("Command Error\n");
			continue;
		}
		switch(checkCommandExist(command)){
			case 0:cm_addOrder(command,queue,pdHead);break;
			case 1:cm_addBatchOrder(command,queue,pdHead);break;
			case 2:cm_runAls(command,queue,&resultScheduleTable[schedTabIdx]); schedTabIdx++;break;
			case 3:cm_printReport(command);break;
			case 4:endProgram(queue,pdHead);break;
		}
		if (strcmp(command,"endProgram")==0)break;
	}
	// scanf("%[^\n]",&command);
	// char * command = "addBatchOrder batch_Order_01.dat";
	// // switch(checkCommandExist(command)){
	// // 	case 0:cm_addOrder(command,queue,pdHead);break;
	// // 	case 1:cm_addBatchOrder(command,queue,pdHead);break;
	// // 	case 2:cm_runAls(command,queue,&resultScheduleTable[schedTabIdx]); schedTabIdx++;break;
	// // 	case 3:cm_printReport(command);break;
	// // 	case 4:endProgram();break;
	// // }




	// printQueue(queue);
	// struct Node* test = searchOrder(queue,10);
	// printf("orderID: %s\n", test->data.orderID);		
	// printf("startDateStr: %s\n", test->data.startDateStr);
	// printf("endDateStr: %s\n", test->data.endDateStr);
	// printf("pdNameStr: %s\n", test->data.pdNameStr);


	return 0;
}	


// addOrder R0001 D023 D025 Product_B 300