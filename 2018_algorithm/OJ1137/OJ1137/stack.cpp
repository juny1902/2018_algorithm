#include <stdio.h>
#define MAX_STACK_SIZE 100
#define INVALID_VALUE -999
int top = -1;
int stack[MAX_STACK_SIZE];
void sum_all() {
	int sum = 0;

	while (top > -1) {
		sum += stack[top];
		top--;
	}
	top++;
	stack[top] = sum;
}
int push(int v) {
	if (top == MAX_STACK_SIZE - 1)
		return 0;
	else {
		stack[++top] = v;
		return 1;
	}
}
int pop() {
	if (top == -1)
		return INVALID_VALUE;
	else {
		int tmp = stack[top--];
		return tmp;
	}
}
int main() {
	int i, n, d, k;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &d);
		if (d == 100) {
			sum_all();
		}
		else {
			push(d);
		}
	}
	for (i = 0; i < n; i++) {
		if ((k = pop()) != INVALID_VALUE)
			printf("%d ", k);
	}
}