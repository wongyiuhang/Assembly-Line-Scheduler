int getLineOrderStartDay(struct Schedule * resultScheduleTable, int line, int orderId) {
	int a, pro_startDate;
	for ( a = 0 ; a< 60 ; a++) {
		if (resultScheduleTable->days[a].orderID[line] == orderId)
			pro_startDate= a;
		break;
	}
	return pro_startDate;
}

int getLineOrderEndDay(struct Schedule * resultScheduleTable, int line, int orderId) {
	int a, pro_endDate;
	for ( a = 60 ; a> 0 ; a--) {
		if (resultScheduleTable->days[a].orderID[line] == orderId)
			pro_endDate = a;
		break;
	}
	return pro_endDate;
}

int getQuantityProduce(struct Schedule * resultScheduleTable, int line, int orderId) {
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
	int sum,quantity = 0 ;

	if ((checkingNode->data.quantity) % 1000 == 0)
	sum += 1000;
	else {
		sum += (checkingNode->data.quantity) % 1000;
	}

	for ( a = 0 ; a<60 ; a++) {
		if (resultScheduleTable[0].days[a].orderID[line] == orderId)
			quantity += 1;
	}

	sum = sum + quantity * 1000 - 1000;
	return sum;

}


int getWorkingDay(struct Schedule * resultScheduleTable, int line, int orderId){
	int startDate, endDate,working_day;
	startDate = getLineStartDay(resultScheduleTable,line,orderId);
	endDate = getLineEndDay(resultScheduleTable,line,orderId);
	working_day = endDate - startDate + 1;
	return working_day;

}

int getDayInUse(struct Schedule * resultScheduleTable, int line){
	int a,day_use;

	for( a = 0; a < 60; a++ ){
		if (resultScheduleTable[0].days[a].orderID[line] !=0)
			day_use += 1;
	}
	return day_use;
}


int getDayNotUse(struct Schedule * resultScheduleTable, int line){
	int a,day_not_use;
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