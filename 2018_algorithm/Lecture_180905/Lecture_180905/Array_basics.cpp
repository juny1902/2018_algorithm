#include "SLL.h"
int exp(int n, int m) {
	if (m == 0) {
		return 1;
	}
	else if (m == 1) {
		return n;
	}
	else {
		return n * exp(n, m - 1);
	}
}

int fibo(int n) {
	if (n <= 0) {
		printf("n should be greater than 0\n");
		return -1;
	}
	if (n <= 2) {
		return 1;
	}
	else {
		return fibo(n - 1) + fibo(n - 2);
	}
}

int factorial(int n) {
	if (n <= 0) {
		printf("n should be greater than 0\n");
		return -1;
	}
	if (n == 1) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}

typedef struct AA {
	int n;
	char c;
	double f;
}AA;

typedef struct node {
	int v;
	double f;
}node;

void struct_test() {
	AA a = { 3,'a',3.14159 };

	AA *b = (AA *)malloc(sizeof(AA));
	*b = { 5,'b',123.456 };

	printf("A의 내용물 : {%d, %c, %lf}\n", a.n, a.c, a.f);
	printf("B의 내용물 : {%d, %c, %lf}\n", (*b).n, b->c, b->f);

	node m = { 10, 3.14 };
	printf("node m의 내용물 : {%d, %lf}\n", m.v, m.f);
}
void struct_array() {
	node *p = (node *)malloc(sizeof(node) * 20);
	*(p + 9) = { 20,4.5 };

	printf("10번째 구조체 변수의 값은 ? %d %f\n", p[9].v, (p + 9)->f);
}
void struct_malloc() {
	node *p = (node *)malloc(sizeof(node));
	*p = { 10, 3.14 };
	printf("%d, %lf\n", p->v, (*p).f);
}

typedef struct self_ref {
	int v;
	self_ref *next;
}self_ref;
