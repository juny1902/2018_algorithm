#include <stdio.h>
#include <stdlib.h>

// Recursion : �Լ� a �� �ڱ� �ڽ��� ȣ���Ѵ�
void hanoi(int n,char from, char to, char tmp) {
	if (n == 1) {
		printf("���ø� %c ���� %c �� �Ű���ϴ�.\n", from, to);
		return;
	}
	else {
		hanoi(n - 1, from, to, tmp);
		hanoi(1, from, tmp, to);
		hanoi(n - 1, to, from, tmp);
	}
	

}
int nth_pibo(int n) {
	if (n <= 2) {
		return 1;
	}
	else {
		return nth_pibo(n - 1) + nth_pibo(n - 2);
	}
}
int exp_non_recur(int x, int n) {
	int i, result=1;
	for (i = 0; i < n; i++) {
		result *= x;
	}
	return result;
}

int exp_recur(int x,int n) {
	if (n == 0) { // Ż�� ����
		return 1;
	}
	else if (n == 1) {
		return x;
	}
	else { // ����
		return exp_recur(x, n - 1) * 2; // 2^n = 2 * 2^(n-1)
	}
}

int fact(int n) {
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		return n * fact(n - 1);
	}
}

int main() {
	char poleA = 'A';
	char poleB = 'B';
	char poleC = 'C';

	hanoi(3, poleA, poleB, poleC);
	getchar();
	return 0;
}