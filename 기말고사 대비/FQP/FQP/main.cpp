#include <stdio.h>
#include <stdlib.h>

#define SZ 5

int BOARD[SZ][SZ];

int abs(int v) {
	if (v < 0) return -v;
	return v;
}

int checkUpside(int x, int y) { // 놓을수 있으면 1, 놓을수 없으면 0

	for (int i = x-1; i >= 0; i--) {
		if (BOARD[i][y] != 0) return 0;
	}
	return 1;
}

int checkDiagonal(int x, int y) { // 놓을수 있으면 1, 놓을수 없으면 0
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j < SZ; j++) {
			if (BOARD[i][j] != 0) {
				if (abs(i - x) == abs(j - y)) {
					return 0;
				}
				else {
					break;
				}
			}
		}
	}
	return 1;
}


void checkBoard() {
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			printf("%d ", BOARD[i][j]);
		}
		printf("\n");
	}
}
int solution_cnt = 0;
void doBacktracking(int row) {
	for (int i = 0; i < SZ; i++) {
		if (checkDiagonal(row, i) && checkUpside(row, i)) {
			BOARD[row][i] = 1;
			if (row < SZ - 1) {
				doBacktracking(row + 1);
			}
			else {
				solution_cnt++;
				checkBoard();
			}
			BOARD[row][i] = 0;
		}
	}
}

int main() {
	doBacktracking(0);
	printf("총 솔루션 수 : %d\n", solution_cnt);
	return 0;
}