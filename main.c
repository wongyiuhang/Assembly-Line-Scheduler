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

	int table[3][60] = { 0 }; // Schedule tabel
	bool keepLoop = true;	
	char command[100];

	struct Product * a = pdHead->next; 
	struct Product * b = pdHead->next->next;
	printf("a: %s\n", a->nameStr);
	printf("b: %s\n", b->nameStr);
	printf("A vs B: %d\n", checkEqiuipConflict(a,b));


	while(keepLoop){
		printf("Please enter: \n");
		if (scanf("%[^\n]",&command)!=1){
			printf("Command Error\n");
			 continue;			
		}
		switch(checkCommandExist(command)){
			case 0:cm_addOrder(command,queue,pdHead);break;
			case 1:cm_addBatchOrder(command,queue,pdHead);break;
			case 2:cm_runAls(command,pdHead);break;
			case 3:cm_printReport(command);break;
			case 4:endProgram();break;
		}
		if (strcmp(command,"endProgram")==0)break;
	}
	// scanf("%[^\n]",&command);
	// char * command = "addOrder R0001 D023 D025 Product_E 300";
	// switch(checkCommandExist(command)){
	// switch(checkCommandExist(command)){
	// 	case 0:cm_addOrder(command,queue,pdHead);break;
	// 	case 1:cm_addBatchOrder(command,queue,pdHead);break;
	// 	case 2:cm_runAls(command,pdHead);break;
	// 	case 3:cm_printReport(command);break;
	// 	case 4:endProgram();break;
	// }
	// printQueue(queue);
}	


// addOrder R0001 D023 D025 Product_B 300