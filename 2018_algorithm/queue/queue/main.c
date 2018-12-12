#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
#define INVALID_VALUE -999

int front = 0; rear = 0;
int queue[MAX_QUEUE_SIZE];
int isQueueFull() {
	if (front == (rear+1)%MAX_QUEUE_SIZE) {
		return 1;
	}
	else {
		return 0;
	}
}
int isQueueEmpty() {
	if (front == rear) {
		return 1;
	}
	else {
		return 0;
	}
}
int enQueue(int v) {
	if (isQueueFull()) {
		printf("큐가 가득 찼습니다.\n");
		return 0;
	}
	else {
		queue[rear] = v;
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		return 1;
	}
}
int deQueue() {
	if (isQueueEmpty()) {
		printf("큐가 비어 있습니다.\n");
		return INVALID_VALUE;
	}
	else {
		int tmp = queue[front];
		front = (front + 1) % MAX_QUEUE_SIZE;
		return tmp;
	}
}
int main() {
	enQueue(3);
	enQueue(5);
	enQueue(1);
	enQueue(2);
	enQueue(3);
	
	int i = 5;
	while (i--) {
		printf("%d, ", deQueue());
	}
	getchar();
	
}