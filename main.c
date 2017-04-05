#include <stdio.h>

#include "struct.h"
#include "global.h"

#include "input.h"


int main(int argc, char *argv[]){
	printf("\n");
	printf("\t\t ~~WELCOME TO ALS~~ \n");
	printf("\n");
	bool keepLoop = true;
	char command[100];
	while(keepLoop){
		printf("Please enter: \n");
		scanf("%s",command);
		switch(checkCommandExist(command)){
			case 0:cm_addOrder(command);break;
			case 1:cm_addBatchOrder(command);break;
			case 2:cm_runAls(command);break;
			case 3:cm_printReport(command);break;
			case 4:endProgram();break;
		}
		if (strcmp(command,"endProgram")==0)break;
	}

}
