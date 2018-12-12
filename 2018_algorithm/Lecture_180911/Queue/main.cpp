#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10 // ������ 9������ ���� ����.

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
		printf("ť�� ���� á���ϴ�.\n");
		return 0;
	}
	else {
		queue[rear] = v; // ���� ���� ���� �ڿ�
		rear = (rear + 1) % MAX_QUEUE_SIZE; // Rear �ε��� ����.
		return 1;
	}
}

int deQueue() {
	if (isQueueEmpty()) {
		printf("ť�� ��� �ֽ��ϴ�..\n");
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
	printf("enQueue �� ��ü ���� �Է��Ͻÿ� : ");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("%d ��° ��ü : ", i);
		scanf_s("%d", &v);
		enQueue(v);
	}

	for (int i = 0; i < n; i++) {
		printf("���� �� : %d\n", deQueue());
	}

	return 0;
}