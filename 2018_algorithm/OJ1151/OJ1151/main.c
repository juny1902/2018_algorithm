#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
int queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;
int enQueue(int v) {
	if (front == (rear + 1) % MAX_QUEUE_SIZE) {
		return 0;
	}
	else {
		queue[rear] = v;
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		return 1;
	}
}

char *deQueue() {
	if (front == rear) {
		return 0;
	}
	else {
		int *tmp = queue[front];
		front = (front + 1) % MAX_QUEUE_SIZE;
		return tmp;
	}
}

int main() {
	char cmd[80];
	int n, d;
	scanf("%d", &n);
	while (n--) {
		fgets(cmd, 80, stdin);
		if (strncmp(cmd, "push", 4) == 0) {
			scanf("%d", &d);
			printf("�Է� ��� : push %d\n", d);
		}
		else if (strcmp(cmd, "pop") == 0) {
			printf("�Է� ��� : pop \n");
		}
		else if (strcmp(cmd, "size") == 0) {
			printf("�Է� ��� : size \n");
		}
		else if (strcmp(cmd, "empty") == 0) {
			printf("�Է� ��� : empty \n");
		}
		else if (strcmp(cmd, "front") == 0) {
			printf("�Է� ��� : front \n");
		}
		else if (strcmp(cmd, "back") == 0) {
			printf("�Է� ��� : back \n");
		}
		else {
			printf("�߸��� ����Դϴ�.\n");
		}
	}

}