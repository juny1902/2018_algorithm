#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10 // 실제론 9개까지 저장 가능.

int queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

int isQueueFull() {
	if (front == (rear + 1) % MAX_QUEUE_SIZE) {
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
		queue[rear] = v; // 먼저 값을 넣은 뒤에
		rear = (rear + 1) % MAX_QUEUE_SIZE; // Rear 인덱스 조정.
		return 1;
	}
}

int deQueue() {
	if (isQueueEmpty()) {
		printf("큐가 비어 있습니다..\n");
		return -999;
	}
	else {
		int tmp = queue[front];
		front =	(front + 1) % MAX_QUEUE_SIZE;
		return tmp;
	}
}


int main() {
	int n, v;
	printf("enQueue 할 개체 수를 입력하시오 : ");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("%d 번째 개체 : ", i);
		scanf_s("%d", &v);
		enQueue(v);
	}

	for (int i = 0; i < n; i++) {
		printf("꺼낸 값 : %d\n", deQueue());
	}

	return 0;
}