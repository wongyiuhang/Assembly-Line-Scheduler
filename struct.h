#include <stdlib.h>
#include <string.h>

#pragma once


/*************************
 *                       *
 *    Queue structure    *
 *                       *
 *************************/
struct Order {
	char orderID[6];
	char startDateStr[5];
	char endDateStr[5];
	char pdNameStr[10];	
	int quantity;
	char pdName;	
	int startDate; 
	int endDate;
	int id; // number of order
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
	free(queue->head);
	queue->head = nextNode;

	return result;
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
	int i = 0;
	while(nextNode != NULL) {
		printf("========== NODE %d ==========\n", i);
		printf("orderID: %s\n", nextNode->data.orderID);
		printf("startDateStr: %s\n", nextNode->data.startDateStr);
		printf("endDateStr: %s\n", nextNode->data.endDateStr);
		printf("pdNameStr: %s\n", nextNode->data.pdNameStr);
		printf("quantity: %d\n\n", nextNode->data.quantity);
		i++;
		nextNode = nextNode->next;
	}

	printf("===============\n");
	printf("===============\n\n");
}
