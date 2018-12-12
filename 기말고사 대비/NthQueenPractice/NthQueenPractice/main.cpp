#include <stdio.h>
#include <stdlib.h>

int solutionCnt = 0;
int recursionFlag = 1;

void printBoard(int **BOARD, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", BOARD[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int abs(int v) {
	if (v < 0) return -v;
	return v;
}

int checkUpside(int **BOARD, int size, int x, int y) {
	for (int i = 0; i < x; i++) {
		if (BOARD[i][y] != 0) return 0;
	}
	return 1;
}

int checkDialog(int **BOARD, int size, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < size; j++) {
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

int isOkay(int **BOARD, int size, int x, int y) {
	return checkDialog(BOARD, size, x, y) && checkUpside(BOARD, size, x, y) ? 1 : 0;
}

int isSameArray(int **BOARD, int **INPUT, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (BOARD[i][j] != INPUT[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

void doBacktracking(int **BOARD, int **INPUT, int size, int row) {
	if (recursionFlag == 0) return;
	for(int col=0; col<size; col++){
		if (isOkay(BOARD, size, row, col)) {
			BOARD[row][col] = 1;
			if (row < size - 1) {
				doBacktracking(BOARD, INPUT, size, row + 1);
			}
			else {
				if (isSameArray(BOARD, INPUT, size)) {
					printf("Solution found in %d-th solution.\n", solutionCnt);
					printBoard(BOARD, size);
					recursionFlag = 0;
				}
				solutionCnt++;
			}
			BOARD[row][col] = 0;
		}
	}	
}

int **makeBoard(int size) {
	int **BOARD = (int **)malloc(sizeof(int *)*size*size);
	for (int i = 0; i < size; i++) {
		BOARD[i] = (int *)malloc(sizeof(int) * size*size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			BOARD[i][j] = 0;
		}
	}
	return BOARD;
}

int **loadBoard(FILE *fp, int &size) {
	if (fp == 0) return 0;

	size = 0;

	fscanf(fp,"%d\n", &size);
	int **BOARD = makeBoard(size);

	char buf = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fread(&buf, sizeof(char), 1, fp);
			if (buf == '\n') {
				j--;
				continue;
			}
			else if (buf == '*') {
				BOARD[i][j] = 1;
			}
			else {
				BOARD[i][j] = 0;
			}
		}
	}

	return BOARD;
}

int main() {

	FILE *fp = fopen("D:/16queens_true.txt", "rt");
	int size = 0;
	int **INPUT = loadBoard(fp,size);
	int **BOARD = makeBoard(size);
	printf("Input board (%d x %d)\n", size, size);
	printBoard(INPUT, size);

	doBacktracking(BOARD, INPUT, size, 0);
	

	return 0;
}