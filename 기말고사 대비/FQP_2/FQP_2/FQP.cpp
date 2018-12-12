#include <stdio.h>
#include <stdlib.h>

#define SZ 8
int foundSolution = 0;
int BOARD[SZ][SZ] = { 0, };
int INPUT_BOARD[SZ][SZ] = { 0, };
int abs(int v) {
	if (v < 0) return -v;
	else return v;
}
int checkDiagonal(int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < SZ; j++) {
			if (BOARD[i][j] == 1) {
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
int checkUpside(int x, int y) {
	for (int i = 0; i < x; i++) {
		if (BOARD[i][y] == 1) {
			return 0;
		}
	}
	return 1;
}
int isOkay(int x, int y) {
	if (checkDiagonal(x, y) && checkUpside(x, y)) return 1;
	return 0;
}

void checkBoard() {
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			if (BOARD[i][j] == 1) {
				printf("*");
			}
			else {
				printf(".");
			}
		}
		printf("\n");
	}
	printf("\n");
}
void checkInput() {
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			if (INPUT_BOARD[i][j] == 1) {
				printf("*");
			}
			else {
				printf(".");
			}
		}
		printf("\n");
	}
	printf("\n");
}

int isSameArray() {
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			if (BOARD[i][j] != INPUT_BOARD[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

int doBacktracking(int row) {
	if (foundSolution) return 0;
	for (int i = 0; i < SZ; i++) {
		if (isOkay(row, i) == 1) {
			BOARD[row][i] = 1;
			if (row < SZ-1) {
				doBacktracking(row + 1);
			}
			else {
				if (isSameArray()) {
					foundSolution = 1;
				}
			}
			BOARD[row][i] = 0;
		}
	}
	return 0;
}
void loadBoard() {
	FILE *fp = fopen("d:/queens_false.txt", "rt");
	if (fp == 0) return;
	int i = 0, j = 0;
	char c = 0;
	for (i = 0; i < SZ; i++) {
		for (j = 0; j < SZ; j++) {
			fread(&c, sizeof(char), 1, fp);
			if (c == '\n') {
				j--;
			}
			else if (c == '.') {
				INPUT_BOARD[i][j] = 0;
			}
			else if (c == '*') {
				INPUT_BOARD[i][j] = 1;
			}
		}
	}
}
void loadBoard_scanf() {
	char c = 0;
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			c = getc(stdin);
			if (c == '\n') {
				j--;
				continue;
			}
			else if (c == '.') {
				INPUT_BOARD[i][j] = 0;
			}
			else if(c == '*'){
				INPUT_BOARD[i][j] = 1;
			}
		}
	}
}
int main() {
	loadBoard_scanf();
	doBacktracking(0);
	if (foundSolution) {
		printf("valid\n");
	}
	else {
		printf("invalid\n");
	}
	return 0;

}