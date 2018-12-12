#include <stdio.h>
#define MAX_STACK_SIZE 5
int top = -1;
int stack[MAX_STACK_SIZE] = { 0, };

int push(int v) {
	if (top == MAX_STACK_SIZE-1) {
		return 0;
	}
	else {
		top++;
		stack[top] = v;
		return 1;
	}
}

int pop() {
	if (top == -1) {
		return 0;
	}
	else {
		int tmp = stack[top];
		top--;
		return tmp;
	}
}
int getSum() {
	int i, sum = 0;
	int d = top;
	for (i = 0; i < 5; i++) {
		sum += pop();
	}
	return sum;
}

int peak() {
	if (top == -1) return -999;
	else return stack[top];
}

int main() {
	int i, d;
	while(1) {
		scanf("%d", &d);
		if (d == -1) {
			if(top != -1)
				push(getSum());
		}
		else if (d == -100) {
			if(top != -1)
				printf("%d ", peak());
			return 0;
		}
		else {
			push(d);
		}
	}
	return 0;
}