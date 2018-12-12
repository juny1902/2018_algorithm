#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 10
#define INVALID_VALUE -999
int top = -1;
int stack[MAX_STACK_SIZE];

int isStackFull() {
	if (top == MAX_STACK_SIZE) {
		return 1;
	}
	else {
		return 0;
	}
}

int isStackEmpty() {
	if (top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

int push(int v) {
	if (isStackFull()) {
		printf("스택이 가득 찼습니다.\n");
		return 0;
	}
	else {
		top++;
		stack[top] = v;
		return 1;
	}
}

int pop() {
	if (isStackEmpty()) {
		printf("스택이 비어있습니다.\n");
		return INVALID_VALUE;
	}
	else {
		int tmp = stack[top];
		top--;
		return tmp;
	}
}

int main() {
	int s = 0, a,r;
	while (s != -1) {
		printf("Push(1) or Pop(2) ? - ");
		scanf_s("%d", &s);

		switch (s) {
		case 1:
			printf("stack[%d] 에 삽입할 값 : ", top+1);
			scanf_s("%d", &a);
			push(a);
			break;
		case 2:
			if ((r = pop()) != INVALID_VALUE) {
				printf("stack[%d] 에서 %d 을 꺼냈습니다.\n", top+1, r);
			}			
			break;
		}
	}
}