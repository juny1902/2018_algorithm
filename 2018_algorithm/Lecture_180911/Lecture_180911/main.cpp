#include <stdio.h>
#include <stdlib.h>
// ť�� �� ĭ�� �׻� ����ִ� ����? : ť�� ������� �� á���� �˱� ����.

// Binary Search Tree : ������ ����, ū�� ������.
// Search : 
// Traversal : Inorder traversal, ��ͷ� ����.
// Delete : ��Ʈ�� �������, ���ʿ��� ���� ū ���, �����ʿ��� ���� ���� ��尡 ��.

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
	if (top == MAX_STACK_SIZE - 1) { // �ε��� ���� !!!!
		return 1;
	}
	else {
		return 0;
	}
}

int push(int v) {
	if (isStackFull()) {
		printf("������ ���� á���ϴ�.\n");
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
		printf("������ ����ֽ��ϴ�.\n");
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
	printf("Push �� ��ü ���� �Է��Ͻÿ� : ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("%d ��° ��ü : ",i);
		scanf_s("%d", &v);
		push(v);
	}

	for (int i = 0; i < n; i++) {
		printf("���� �� : %d\n",pop());
	}

	return 0;
}