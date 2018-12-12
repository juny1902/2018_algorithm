#include <stdio.h>
#include <stdlib.h>
// 큐의 한 칸이 항상 비어있는 이유? : 큐가 비었는지 꽉 찼는지 알기 위함.

// Binary Search Tree : 작은건 왼쪽, 큰건 오른쪽.
// Search : 
// Traversal : Inorder traversal, 재귀로 구현.
// Delete : 루트가 사라지면, 왼쪽에서 가장 큰 노드, 오른쪽에서 가장 작은 노드가 옴.

#define MAX_STACK_SIZE 5

int stack[MAX_STACK_SIZE];
int top = -1; // Empty

int isStackEmpty() {
	if (top == -1) { // When the stack is empty
		return 1;
	}
	else {
		return 0;
	}
}

int isStackFull() {
	if (top == MAX_STACK_SIZE - 1) { // 인덱스 주의 !!!!
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
		return -999;
	}
	else {
		int tmp = stack[top];
		top--;
		return tmp;
	}
}

int main() {
	int n, v;
	printf("Push 할 개체 수를 입력하시오 : ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("%d 번째 개체 : ",i);
		scanf_s("%d", &v);
		push(v);
	}

	for (int i = 0; i < n; i++) {
		printf("꺼낸 값 : %d\n",pop());
	}

	return 0;
}