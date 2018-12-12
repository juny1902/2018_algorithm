#include <stdio.h>
#include <stdlib.h>

int solutionCnt = 0;
int recursionFlag = 0;

void printBoard(int **BOARD, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", BOARD[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int **makeBoard(int size) {
	int **BOARD = (int **)malloc(sizeof(int *)*size);
	for (int i = 0; i < size; i++) {
		BOARD[i] = (int *)malloc(sizeof(int) * size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			BOARD[i][j] = 0;
		}
	}
	return BOARD;
}

int **loadBoard(int size, FILE *fp) {

	int **BOARD = (int **)malloc(sizeof(int *)*size);
	for (int i = 0; i < size; i++) {
		BOARD[i] = (int *)malloc(sizeof(int) *size);
	}

	if (fp == 0) {
		printf("File empty.\n");
	}

	char c = 0;

	for(int i=0; i<size; i++){
		for (int j = 0; j < size; j++) {
			fread(&c, sizeof(char), 1, fp);
			if (c == '\n') {
				j--;
				continue;
			}
			else if (c == '*') {
				BOARD[i][j] = 1;
			}
			else {
				BOARD[i][j] = 0;
			}
		}
	}

	return BOARD;
}

int abs(int v){
	if (v < 0) return -v;
	return v;
}

int checkUpside(int **BOARD,int size, int x, int y) {
	for (int i = 0; i < x; i++) {
		if (BOARD[i][y] != 0) return 0;
	}
	return 1;
}

int checkDiagonal(int **BOARD, int size, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < size; j++) {
			if (BOARD[i][j] != 0) {
				if (abs(x - i) == abs(y - j)) {
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
	return checkUpside(BOARD, size, x, y) && checkDiagonal(BOARD, size, x, y) ? 1 : 0;
}

int isSameBoard(int **BOARD1, int **BOARD2,int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (BOARD1[i][j] != BOARD2[i][j]) return 0;
		}
	}
	return 1;
}

void doBacktracking(int **BOARD,int **BOARD_IN, int size, int row) {
	if (recursionFlag == 1) {
		return;
	}
	for (int col = 0; col < size; col++) {
		if (isOkay(BOARD, size, row, col)) {
			BOARD[row][col] = 1;
			if (row < size - 1) {
				doBacktracking(BOARD, BOARD_IN, size, row+1);
			}
			else {
				solutionCnt++;
				// printf("- %d-th solution...\n", solutionCnt);
				// printBoard(BOARD, size);
				if (isSameBoard(BOARD, BOARD_IN, size)) {
					printBoard(BOARD, size);
					printf("¡Ø Board in %d-th board... The input was a soultion !\n\n",solutionCnt);
					recursionFlag = 1;
				}
			}
			BOARD[row][col] = 0;
		}
	}
}


int main() {
	FILE *fp = fopen("D:/16queens_true.txt","rt");
	if (fp == 0) return 0;
	int size = 0;
	fscanf(fp,"%d\n", &size);
	int **INPUT = loadBoard(size, fp);
	int **BOARD = makeBoard(size);
	printf("Board to check ... (Size : %d x %d)\n",size,size);
	printBoard(INPUT, size);
	printf("Solutions ... \n");
	doBacktracking(BOARD,INPUT,size,0);

	if (recursionFlag == 0) {
		printf("The input wasn't a solution.\n\n");
	}

	return 0;
}