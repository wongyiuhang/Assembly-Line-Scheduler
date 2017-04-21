int getLineOrderStartDay(struct Schedule * resultScheduleTable, int line, int orderId) {
	int a, pro_startDate
	for ( a = 0 ; a< 60 ; a++) {
		if (resultScheduleTable->.days[b].orderID[line] == orderID)
			pro_startDate= a;
		break;
	}
	return pro_startDate;
}

int getLineOrderEndDay(struct Schedule * resultScheduleTable, int line, int orderId) {
	int a, pro_endDate
	for ( a = 60 ; a> 0 ; b--) {
		if (resultScheduleTable->days[b].orderID[line] == orderId)
			pro_endDate = b;
		break;
	}
	return pro_endDate;
}

int getQuantityProduce(struct Schedule * resultScheduleTable, int line, int orderId) {
	int largest;
	int line1 = getLineOrderEndDay(resultScheduleTable,1,orderID)
	int line2 = getLineOrderEndDay(resultScheduleTable,2,orderID)
	int line3 = getLineOrderEndDay(resultScheduleTable,3,orderID)

	if (line1 >= line2 && line1 >= line3)
		largest = line1;
	else if (line2 >= line1 && line2 >= line3)
		leargest = line2;
	else if (line3 >= line1 && line3 >= line2)
		leargest = line3;

	struct Node * checkingNode = searchOrder(queue,orderID);
	int a;
	int sum,quantity = 0 ;

	if ((checkingNode->data.quantity) % 1000 == 0);
	sum += 1000;
	else 
		sum += (checkingNode->data.quantity) % 1000;

	for ( a = 0 ; a<60 ; a++) {
		if (resultScheduleTable[0].days[a].orderID[line] == orderID)
			quantity += 1;
	}

	sum = sum + quantity * 1000 - 1000;
	return sum;

}


int getWorkingDay(struct Schedule * resultScheduleTable, int line, int orderId){
	int startDate, endDate,working_day;
	startdate = getLineStartDay(resultScheduleTable,line,orderId);
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

float getUtilization(){
	int working_day = getWorkingDay(resultScheduleTable,line);
	int dayinuse = getDayInUse(resultScheduleTable,line);
	float utilization = wdayinuse / workday * 100;
	return utilization;

}

int getOrderAccept(){

	int day_use = getDayInUse(resultScheduleTable,line);
	int order_reject = getOrderReject(resultScheduleTable);
	int order_accept = day_use -  order_reject;
	return order_accept;

}

int getOrderReject(struct Schedule * resultScheduleTable){
	int order_reject = resultScheduleTable[i].droppedOrderCount;
	return order_reject;

}