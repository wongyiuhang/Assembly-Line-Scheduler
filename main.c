#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "input.h"
#include "struct.h"
#include "global.h"



int main(int argc, char *argv[]){
	printf("\n");
	printf("\t\t ~~WELCOME TO ALS~~ \n");
	printf("\n");


	struct Queue* queue = newQueue(); // Order Queue
	int table[3][60] = { 0 }; // Schedule tabel
	bool keepLoop = true;	
	char command[100];
	while(keepLoop){
		printf("Please enter: \n");
		if (scanf("%[^\n]",&command)!=1){
			printf("Command Error\n");
			 // continue;			
		}
		switch(checkCommandExist(command)){
			case 0:cm_addOrder(command,queue);break;
			case 1:cm_addBatchOrder(command,queue);break;
			case 2:cm_runAls(command);break;
			case 3:cm_printReport(command);break;
			case 4:endProgram();break;
		}
		if (strcmp(command,"endProgram")==0)break;
	}

}
