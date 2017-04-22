#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#include "global.h"

#pragma once

int getLineStartDay(struct Schedule * resultScheduleTable, int line){

	int i;
	for ( i = 0; i < NUM_OF_DAY; i++){	
		if (resultScheduleTable->days[i].orderID[line] != 0) {			
			return i;
		}
	}

}

int getLineEndDay(struct Schedule * resultScheduleTable, int line){
	int i;
	for ( i = 59; i > 0; i--){	
		if (resultScheduleTable->days[i].orderID[line] != 0) {
			return i;
		}
	}

}
int getLineOrderStartDay(struct Schedule * resultScheduleTable, int line, int orderId) {
	int a;
	int pro_startDate = 0;
	for ( a = 0 ; a< 60 ; a++) {
		if (resultScheduleTable->days[a].orderID[line] == orderId)
			return a;	
	}
	
}

int getLineOrderEndDay(struct Schedule * resultScheduleTable, int line, int orderId) {
	int a;
	for ( a = 60 ; a >= 0 ; a--) {
		if (resultScheduleTable->days[a].orderID[line] == orderId)
			return a;
	}

}

int getQuantityProduce(struct Schedule * resultScheduleTable, int line, int orderId ,struct Queue * queue) {
	int largest;
	int line1 = getLineOrderEndDay(resultScheduleTable,1,orderId);
	int line2 = getLineOrderEndDay(resultScheduleTable,2,orderId);
	int line3 = getLineOrderEndDay(resultScheduleTable,3,orderId);

	if (line1 >= line2 && line1 >= line3)
		largest = line1;
	else if (line2 >= line1 && line2 >= line3)
		largest = line2;
	else if (line3 >= line1 && line3 >= line2)
		largest = line3;

	struct Node * checkingNode = searchOrder(queue,orderId);
	int a;
	int sum = 0 ,quantity = 0 ;

	if ((checkingNode->data.quantity) % 1000 == 0)
		sum = 1000;
	else {
		sum = (checkingNode->data.quantity % 1000);
	}

	for ( a = 0 ; a<60 ; a++) {
		if (resultScheduleTable[0].days[a].orderID[line] == orderId)
			quantity += 1
		;

	}

	// printf("%d\n",checkingNode->data.quantity);
	// printf("%d\n",quantity);
	sum = sum + (quantity * 1000) - 1000;
	return sum;

}


int getWorkingDay(struct Schedule * resultScheduleTable, int line, int orderId){
	int startDate, endDate,working_day;
	startDate = getLineStartDay(resultScheduleTable,line);
	endDate = getLineEndDay(resultScheduleTable,line);
	working_day = endDate - startDate + 1;
	return working_day;
}
int getWorkingDayInLine(struct Schedule * resultScheduleTable, int line){
	int i,count=0;
	for ( i = 0 ; i <60 ;i++)
	{
		if (resultScheduleTable->days[i].orderID[line] != 0)
		{
			count++;
		}
	}
	return count;
}
int getDayInUse(struct Schedule * resultScheduleTable, int line){
	int a;
	int day_use = 0 ;

	for( a = 0; a < 60; a++ ){
		if (resultScheduleTable[0].days[a].orderID[line] !=0)
			day_use += 1;
	}
	return day_use;
}


int getDayNotUse(struct Schedule * resultScheduleTable, int line){
	int a;
	int day_not_use = 0 ;
	for( a = 0; a < 60; a++ ){
		if (resultScheduleTable[0].days[a].orderID[line] ==0)
			day_not_use += 1;
	}
	return day_not_use;
}

float getUtilization(struct Schedule * resultScheduleTable, int line, int orderId){
	int working_day = getWorkingDay(resultScheduleTable,line,orderId);
	int day_use = getDayInUse(resultScheduleTable,line);
	float utilization = day_use / working_day * 100;
	return utilization;

}

int getOrderAccept(struct Schedule * resultScheduleTable, int line){
	int day_use = getDayInUse(resultScheduleTable,line);
	int order_reject = getOrderReject(resultScheduleTable);
	int order_accept = day_use -  order_reject;
	return order_accept;

}

int getOrderReject(struct Schedule * resultScheduleTable, int line){
	int order_reject = resultScheduleTable->droppedOrderCount;
	return order_reject;

}


int * getAllorderIdInLine(struct Schedule * resultScheduleTable, int line){


	int *orderInLine,i,j,k,matched=0;
	orderInLine = malloc(NUM_OF_DAY*sizeof(int));
	for(i = 0; i<NUM_OF_DAY; ++i)
		orderInLine[i] = 0;


	for ( i = 0 ,j = 0 ; i < NUM_OF_DAY; i++){
		matched = 0;
		for (k = 0; k < NUM_OF_DAY; k++){
			if (resultScheduleTable->days[i].orderID[line] == orderInLine[k])
			{
				matched++;
			}
		}
		if (matched == 0)
		{
			orderInLine[j] = resultScheduleTable->days[i].orderID[line];
			j++;
		}
	}
	return orderInLine;
}
int getNumberofOrderInLine(int *orderInLine){
	int i;
	for ( i = 59; i >= 0; i--){	
		if (orderInLine[i] != 0) {
			return (i+1);
		}
	}
}



void printReport(char * fileName,struct Queue * queue,struct Schedule * resultScheduleTable){
	// printf("%s\n",resultScheduleTable[0].algo);
	// printf("%s\n",fileName);
	FILE *file;
	file = fopen(fileName, "w");
	char str[200];
	int table , line , day ;

	for (table = 0; table < MAX_SCHEDULE_TABLE  && resultScheduleTable[table].algo[0] != '\0'; table++)
	{
		for ( line = 0; line < 3; line++)
		{	



			int lineStartDay =  getLineStartDay(&resultScheduleTable[table],line);
			int lineEndDay =  getLineEndDay	(&resultScheduleTable[table],line);

			sprintf(str, "Assembly Line %d \n\nAlgorithm: %s\nStart Date: D%03d\nEnd Date: D%03d\n\n", 
				line+1, resultScheduleTable[table].algo, lineStartDay+1, lineEndDay+1 );
			// printf("%s\n",str);
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			strcpy(str, "Order Number | Start Date | End Date | Due Date | Quantity Requested | Quantity Produced\n");
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			strcpy(str, "-------------+------------+----------+----------+--------------------+------------------\n");
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			int *orderInLine = NULL ;
			orderInLine = getAllorderIdInLine(&resultScheduleTable[table],line);
			int orderNumber = getNumberofOrderInLine(orderInLine);
			int j;
			for (j = 0; j < orderNumber; ++j)
			{ 
				struct Node * checkingNode = searchOrder(queue,orderInLine[j]);

				sprintf(str, " %-12s| D%-10d| D%-8d|",
					checkingNode->data.orderID,
					getLineOrderStartDay(resultScheduleTable,line,orderInLine[j]),
					getLineOrderEndDay(resultScheduleTable,line,orderInLine[j]));
				fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );


				sprintf(str, " D%-8d| %-19d| %-18d", 
					checkingNode->data.endDate ,
					checkingNode->data.quantity,
					getQuantityProduce(resultScheduleTable,line,orderInLine[j],queue));
				fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

				strcpy(str, "\n");
				fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			}

			strcpy(str, "-----------------------------------------------------------------------------------------\n");
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

			sprintf(str, "Total number of working days: \t%d days\n",getWorkingDay(&resultScheduleTable[table],line,orderInLine[j]));
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			sprintf(str, "Order accepted:\t\t\t\t\t%d orders\n",getOrderAccept(&resultScheduleTable[table],line));
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			sprintf(str, "Day not in use:\t\t\t\t\t%d days\n",getDayNotUse(&resultScheduleTable[table],line));
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			sprintf(str, "Day in use:\t\t\t\t\t\t%d days\n",getDayInUse(&resultScheduleTable[table],line));
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

			int workingDay = getDayInUse(&resultScheduleTable[table],line);

			sprintf(str, "Utilization:\t\t\t\t\t%.2f\%\n",((float)getWorkingDayInLine(&resultScheduleTable[table],line)*100/60));
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
			strcpy(str, "=========================================================================================\n\n\n");
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );


		}



		sprintf(str, "***Summary of Schedules***\n Algorithm used: %s\n",resultScheduleTable[table].algo);
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
		int a;
		int sum = 0;

		

		sprintf(str, "There are %d orders scheduled in total. Details are as follows:\n",countQueue(queue));
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );


		sprintf(str, "Assembly Line | Order Accepted | Working Day | Utilization\n===========================================================================\n");
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );


		for(line=0;line<3;line++){
			int *orderInLine = NULL ;
			orderInLine = getAllorderIdInLine(&resultScheduleTable[table],line);
			int orderNumber = getNumberofOrderInLine(orderInLine);
			sprintf(str, "Line_%-13d| %-15d| %-12d| %.2f\% \n",
				line+1,
				orderNumber,
				getWorkingDayInLine(&resultScheduleTable[table],line),
				((float)getWorkingDayInLine(&resultScheduleTable[table],line)*100/60));
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
		}
		strcpy(str, "===========================================================================\n\n" );
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
		strcpy(str, "\n***PERFORMANCE***\n\n" );
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

		float sumUtit = 0 , sumWorkingDay = 0;
		for(line=0;line<3;line++)
		{
			sumUtit += (float)getWorkingDayInLine(&resultScheduleTable[table],line)*100/60;
			sumWorkingDay += getWorkingDayInLine(&resultScheduleTable[table],line);
		}

		
		sprintf(str, "AVERAGE OF WORKING DAYS FOR THE 3 ASSEMBLY LINES: %f DAYS \n",(sumWorkingDay/3));
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
		
		sprintf(str, "AVERAGE OF UTILIZATIOIN: %.2f\%\n\n",(sumUtit/3));
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

		sprintf(str, "TOTAL WORKING DAYS OF THE 3 ASSEMBLY LINES: %f DAYS \n",sumWorkingDay);
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
		sprintf(str, "UTILIZATION OF THE 3 ASSEMBLY LINES: %f \%\n\n\n",(sumUtit/3));
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );







		sprintf(str, "***Order Rejected List***\n");
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

		printf("droppedOrderCount: %d\n",resultScheduleTable[table].droppedOrderCount );
		printf("countQueue(queue): %d\n",countQueue(queue) );
		printf("total_receive: %d\n",countQueue(queue) - resultScheduleTable[table].droppedOrderCount );
		int total_receive = countQueue(queue) - resultScheduleTable[table].droppedOrderCount;


		sprintf(str, "TOTAL NUMBER OF ORDER RECEIVED: %d\n\n",countQueue(queue));
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

		sprintf(str, "- ORDER ACCEPTED: %d\n- ORDER REJECTED: %d\n",(countQueue(queue) - resultScheduleTable[table].droppedOrderCount),resultScheduleTable[table].droppedOrderCount);
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );




		sprintf(str, "REJECTED ORDER LIST\n================================== \n");
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
		int dropIdx ;
		for (dropIdx = 0; dropIdx < resultScheduleTable[table].droppedOrderCount; dropIdx++)
		{
			struct Node * droppedOrder = searchOrder(queue,resultScheduleTable[table].droppedOrder[dropIdx]);
			sprintf(str, "%s %s %s %s %d\n",
				droppedOrder->data.orderID,
				droppedOrder->data.startDateStr,
				droppedOrder->data.endDateStr,
				droppedOrder->data.pdNameStr,
				droppedOrder->data.quantity);
			fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );
		}



		sprintf(str, "There are %d Orders rejected.",resultScheduleTable[table].droppedOrderCount);
		fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );



	}

	sprintf(str, "======================================================= \n\n");
	fwrite(str , 1 , (strlen(str)*sizeof(char) ), file );

	fclose(file);
}




