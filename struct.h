#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma once
/*************************
 *                       *
 *   Product structure   *
 *                       *
 *************************/

struct Product {
	int id;
	char nameStr[10];
	char name;
	int *equipments;
	int equipmentCount;
	struct Product* next;
} product_t;


/****************************
 *                          *
 *    Schedule structure    *
 *                          *
 ****************************/
struct DayJob {
	int orderID[3];
} dayjob_t;

struct Schedule {
	struct DayJob days[60];
	char algo[10];
} schedule_t;


/*************************
 *                       *
 *    Queue structure    *
 *                       *
 *************************/
struct Order {
	int id; // number of order
	char orderID[6];
	char startDateStr[5];
	char endDateStr[5];
	char pdNameStr[10];
	struct Product* prod;
	int quantity;
	char pdName;	
	int startDate; 
	int endDate;
	int remainDay; // number of order
} order_t;

struct Node {
	struct Order data;
	struct Node* next;
} node_t;

struct Queue {
	struct Node* head;
	struct Node* tail;
} queue_t;

/************************
 *                      *
 *    Queue function    *
 *                      *
 ************************/
struct Queue* newQueue() {
	struct Queue* obj = malloc(sizeof(queue_t));
	obj->head = NULL;
	obj->tail = NULL;
	return obj;
}

struct Queue* cloneQueue(struct Queue* sourseQueue) {
	const struct Node* nextNode = sourseQueue->head;
	struct Queue* cloneQueue = newQueue();
	while(nextNode != NULL) {
		enqueue(cloneQueue, &(nextNode->data));	
		nextNode = nextNode->next;
	}
	return cloneQueue;
}

struct Product* newProduct() {
	struct Product* obj = malloc(sizeof(product_t));
	obj->next = NULL;
	return obj;
}

int enqueue(struct Queue* queue, const struct Order* job) {
	// Error checking
	if(queue == NULL)
		return 1;

	// Prepare node
	struct Node* newNode = malloc(sizeof(node_t));
	memcpy(&newNode->data, job, sizeof(order_t));
	newNode->next = NULL;

	// Enqueue
	if(queue->head == NULL) {
		queue->head = newNode;
		queue->tail = newNode;
	} else {
		queue->tail->next = newNode;
		queue->tail = newNode;
	}

	return 0;
}

struct Order dequeue(struct Queue* queue) {
	struct Order result;

	// Error checking
	if(queue == NULL || queue->head == NULL)
		return result;

	// Prepare output
	memcpy(&result, &queue->head->data, sizeof(order_t));

	// Dequeue
	struct Node* nextNode;
	nextNode = queue->head->next;
	free(queue->head->data.prod->equipments);
	free(queue->head);
	queue->head = nextNode;

	return result;
}
struct Product * searchProduct(struct Product * head,char name){
	struct Product * current = head->next;
	while (current != NULL) {
		if (name == current->name){				
			return current;
		}	
		current = current->next;
	}
	return NULL;
}
struct Node * searchOrder(struct Queue * queue,int orderId){
	struct Node* nextNode = queue->head;
	while (nextNode != NULL) {
		if (nextNode->data.id == orderId){				
			return nextNode;
		}	
		nextNode = nextNode->next;
	}
	return NULL;
}
bool orderExist(struct Queue* queue,char * orderID){
	const struct Node* nextNode = queue->head;
	while(nextNode != NULL) {
		if (strcmp(orderID,nextNode->data.orderID) == 0){
			return true;
		}
		nextNode = nextNode->next;
	}
	return false;
}

int countQueue(struct Queue* queue) {
	// Error checking
	if(queue == NULL)
		return -1;

	int count = 0;
	struct Node* nextNode = queue->head;

	// Loop through queue
	while(nextNode != NULL) {
		count++;
		nextNode = nextNode->next;
	}

	return count;
}

struct Order queueRemoveById(struct Queue* queue, int id) {
	int i;
	struct Order result;

	// Error checking
	if(id >= countQueue(queue))
		return result;

	// Remove element
	struct Node *temp, *node;
	if(id == 0) {
		temp = queue->head;
		queue->head = queue->head->next;
	} else {
		node = queue->head;
		for(i = 1; i < id; i++)
			node = node->next;
		temp = node->next;
		node->next = temp->next;
	}
	memcpy(&result, &temp->data, sizeof(order_t));
	free(temp);

	return result;
}

void clearQueue(struct Queue* queue) {
	if(queue == NULL)
		return;
	struct Node* nextNode = queue->head;

	// Clear node
	while(nextNode != NULL) {
		struct Node* temp = nextNode->next;
		free(nextNode->data.prod->equipments);
		free(nextNode);
		nextNode = temp;
	}

	// Clear queue
	free(queue);
}

void printQueue(const struct Queue* queue) {
	printf("***************\n");
	printf("*             *\n");
	printf("*    DEBUG    *\n");
	printf("*             *\n");
	printf("***************\n\n");

	printf("========== HEAD ==========\n");
	printf("head -> %p\n", queue->head);
	printf("tail -> %p\n\n", queue->tail);

	const struct Node* nextNode = queue->head;
	int i = 0,j;
	while(nextNode != NULL) {
		printf("========== NODE %d ==========\n", i);
		printf("NODE Data address: %p\n", nextNode->data);
		printf("orderID: %s\n", nextNode->data.orderID);		
		printf("startDateStr: %s\n", nextNode->data.startDateStr);
		printf("endDateStr: %s\n", nextNode->data.endDateStr);
		printf("pdNameStr: %s\n", nextNode->data.pdNameStr);

		printf("quantity: %d\n\n", nextNode->data.quantity);
		printf("********** NODE->Product ***********\n");
		printf("product nameStr: %s\n", nextNode->data.prod->nameStr);
		printf("product name: %c\n", nextNode->data.prod->name);
		printf("product nameStr: %s\n", nextNode->data.prod->nameStr);
		printf("product equipments: %d items\n", nextNode->data.prod->equipmentCount);

		for (j = 0; j <  nextNode->data.prod->equipmentCount; j++)
		{
			printf("%d ", nextNode->data.prod->equipments[j]);
		}
		printf("\n");

		i++;
		nextNode = nextNode->next;
	}

	printf("===============\n");
	printf("===============\n\n");
}

void productPush(struct Product * head, struct Product * newPd) {

	struct Product * current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(product_t));
	memcpy(current->next, newPd, sizeof(product_t));
}
void printProductList(struct Product * head) {
	printf("***************\n");
	printf("*             *\n");
	printf("*    DEBUG    *\n");
	printf("*             *\n");
	printf("***************\n\n");
	printf("**************print Product*************\n");

	struct Product * current = head;
	int i ;
	while (current != NULL) {
		printf("Product id : %d\n", current->id);
		printf("Product name : %c\n", current->name);
		printf("Product nameStr : %s\n", current->nameStr);
		printf(" --- Product equipments  --- \n");
		for (i = 0; i < current->equipmentCount; i++)
		{
			printf("%d, ",current->equipments[i]);
		}
		printf("\n");

		current = current->next;
	}
	printf("**************End Product*************\n");
}

bool checkEqiuipConflict(struct Product* a, struct Product* b ){
	int i , j;
	int max =( a->equipmentCount > b->equipmentCount )? a->equipmentCount : b->equipmentCount;

	for (i = 0; i < a->equipmentCount; i++)
	{
		for (j = i; j < b->equipmentCount; ++j)
		{
			if (a->equipments[i] == b->equipments[j])
				return true;
		}
	}
	return false;
}
