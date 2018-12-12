#include <stdio.h>

int exp_recursion(int n, int m) {
	if (m == 0) {
		return 1;
	}
	else if (m == 1) {
		return n;
	}
	else {
		return n * exp_recursion(n, m - 1);
	}
}

int factorial(int n) {
	if (n == 0) {
		return 0;
	}
	else if(n == 1){
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}

int pibonazi(int n) {
	if (n <= 2) {
		return 1;
	}
	else {
		return pibonazi(n - 1) + pibonazi(n - 2);
	}
}

void hanoi(int n, char from, char tmp, char to) {
	if (n==1) {
		printf("%c ���� %c �� �Ű���ϴ�.\n", from, to);
	}
	else {
		hanoi(n - 1, from, to, tmp);
		printf("%c ���� %c �� �Ű���ϴ�.\n", from, to);
		hanoi(n - 1, tmp, from, to);
	}
}

int main() {
	printf("2�� 3���� %d\n", exp_recursion(2, 3));
	printf("5! = %d\n", factorial(5));
	for (int i = 1; i <= 10; i++) {
		printf("%d ��° �Ǻ���ġ ���� %d\n", i,pibonazi(i));
	}
	char a = 'A', b = 'B', c = 'C';
	hanoi(3, a, b, c); // 3���� ������ a ���� c�� �ű��, b�� �ӽ÷� ���.
	getchar();
	return 0;
}