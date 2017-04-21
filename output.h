#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "struct.h"
#include "global.h"

#pragma once

		//output
void printReport(char * fileName,struct Queue * queue,struct Schedule * resultScheduleTable){
	FILE *fp;
		printf("%s\n",resultScheduleTable[0].algo);


	fp=fopen(fileName, "w");

	char str[255];


	//first part
	char algo;
	int startDate; 
	int endDate;

	//second part
	int pro_startDate; 
	int pro_endDate;
	int pro_dueDate;
	int remainDay;
	int order;
	int quantity_requested;
	int sum;
	int quantity_produced;


	//third part
	int working_day;
	int order_accept;
	int day_not_use;
	int day_use;
	int utilization;


	//fourth part
	int line1[3];
	int line2[3];
	int line3[3];

	int i = 0;
	while(resultScheduleTable[i].algo != NULL){
		algo = resultScheduleTable[i].algo  ;


			//each line
		for(int line= 0 ; line<3 ; line++){



			for(int a = 0; a < 60; a++ ){
				if (resultScheduleTable[i].days[a].orderID[line] !=0){
					startDate = a;
					break;
				}
			}


			for (int a = 60 ; a> 0 ; a--) {
				if (resultScheduleTable[i].days[a].orderID[line] !=0){
					endDate = a;
					break;
				}
			}


			sprintf(str, "Assembly Line %d \n Algorithm: %s\n Start Date: D%02d\n End Date: D%02d\n", line, algo,startDate,endDate );
			fprintf(fp, str);
			working_day = endDate - startDate + 1;



			for(int a = 0; a < 60; a++ ){
				if (resultScheduleTable[0].days[a].orderID[line] !=0)
					day_use += 1;	
				if (resultScheduleTable[0].days[a].orderID[line] ==0)
					day_not_use += 1;
			}

			utilization = day_use / working_day * 100;


			sprintf(str, "Order Number   Start Date   End Date   Due Date   Quantity Requested   Quantity Produced" );
			fprintf(fp, str);


			
			for(int a = 0; a < 60; a++ ){
				if (resultScheduleTable[0].days[a].orderID !=0){
					order = resultScheduleTable[0].days[a].orderID;

							//startDate
					for (int b = 0 ; b< 60 ; a++) {
						if (resultScheduleTable[0].days[b].orderID[line] == order)
							pro_startDate= b;
						break;
					}

							//endDate
					for (int b = 60 ; b> 0 ; b--) {
						if (resultScheduleTable[0].days[b].orderID[line] == order)
							pro_endDate = b;
						break;
					}

					//quality produced
					for (int b = 0 ; b<60 ; b++) {
						if (resultScheduleTable[0].days[b].orderID[line] == order)
							sum = sum + 1;
						quantity_produced = sum * 1000;

					}

					struct Node * checkingNode = searchOrder(queue,order);


					sprintf(str, "%s %s %s %s %s %s\n", order , pro_startDate,pro_endDate , checkingNode->data.endDate,checkingNode->data.quantity, quantity_produced);
					fprintf(fp, str);

				}
			}

			if (line == 0){
				line1[0] = order_accept;
				line1[1] = working_day;
				line1[2] = utilization;
			}
			else if (line == 1){
				line2[0] = order_accept;
				line2[1] = working_day;
				line2[2] = utilization;
			}
			else if (line == 2){
				line3[0] = order_accept;
				line3[1] = working_day;
				line3[2] = utilization;
			}


			sprintf(str, "Total number of working days: %d\n Order accepted:  %d\n ", working_day , order_accept);
			fprintf(fp, str);

			sprintf(str, "Day not in use:  %d\nDay in use:  %d\n  ", day_not_use , day_use);
			fprintf(fp, str);

			sprintf(str, "Utilization:%d \n" , utilization );
			fprintf(fp, str);


		}


	//Summary Schedule
		int totalOrder;
		double avg_day,avg_util,totalWorkDay;

		totalOrder = line1[0]+line2[0]+line3[0];
		totalWorkDay =  line1[1]+line2[1]+line3[1];
		avg_util = (line1[2]+line2[2]+line3[2])/3*100;
		avg_day = totalWorkDay/3*100;

		sprintf(str,"**Summary Schedule**\nAlgorithm used:%s\nThere are %d orders scheduled in total",algo,totalOrder);
		fprintf(fp, str);
		sprintf(str,"Details are as follows:\n Assembly Line | Order Accepted | Working Day | Utilization\n");
		fprintf(fp, str);
		sprintf(str,"line_1\t%d\t%d\t%d\n",line1[0],line1[1],line1[2]);
		fprintf(fp, str);
		sprintf(str,"line_2\t%d\t%d\t%d\n",line2[0],line2[1],line2[2]);
		fprintf(fp, str);
		sprintf(str,"line_3\t%d\t%d\t%d\n",line3[0],line3[1],line3[2]);
		fprintf(fp,  str);

		sprintf(str,"***Performance***\n");
		fprintf(fp, str);
		sprintf(str,"AVERAGE OF WORKING DAYS FOR THE 3 ASSEMBLY LINES:\t%.1f DAYS\n",avg_day);
		fprintf(fp, str);
		sprintf(str,"AVERAGE OF UTILIZATIOIN:\t%.1f\n",avg_util);
		fprintf(fp, str);
		sprintf(str,"TOTAL WORKING DAYS OF THE 3 ASSEMBLY LINES:%.1f DAYS\n",totalWorkDay);
		fprintf(fp, str);
		sprintf(str,"UTILIZATION OF THE 3 ASSEMBLY LINES:\t%.1f\n",avg_util);
		fprintf(fp, str);

		i+= 1;


		//print report
		int count_dropped = resultScheduleTable[i].droppedOrderCount;

		int totalOrder_receive = count_dropped + totalOrder;

		sprintf(str,"***Order Rejected List***\nTOTAL NUMBER OF ORDER RECEIVED: %d",totalOrder_receive);
		fprintf(fp, str);

		sprintf(str,"- ORDER ACCEPTED: %d\n - ORDER REJECTED: %d\n REJECTED ORDER LIST: \n",count_dropped);
		fprintf(fp, str);

		sprintf(str,"REJECTED ORDER LIST\n==================================\n");
		fprintf(fp, str);





		for (int a = 0; a < count_dropped; a++){
			


		order = resultScheduleTable[i].droppedOrder[a];

		struct Node * checkingNode = searchOrder(queue,order);


		sprintf(str,"%d%d%d",checkingNode->data.id,checkingNode->data.startDate,checkingNode->data.endDate);
		fprintf(fp, str);
		

		sprintf(str,"%s%d",checkingNode->data.pdName,checkingNode->data.quantity);
		fprintf(fp, str);
		


		}


		sprintf(str,"There are %d Orders rejected",count_dropped);
		fprintf(fp, str);

	}

	fclose(fp);

}

