#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 9
int solutionCnt = 0;

int BOARD[BOARD_SIZE][BOARD_SIZE];
int BOARD_SWP[BOARD_SIZE][BOARD_SIZE];

void solveSudoku(int x, int y);
void checkNext(int x, int y);

void printBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i % 3 == 0) {
			printf("-------------------------------\n");
		}
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (j % 3 == 0) {
				printf("|");
			}
			printf(" %d ", BOARD_SWP[i][j]);
		}
		printf("|\n");
	}
	printf("-------------------------------\n");
}

int check_row(int x, int y, int n) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (BOARD[i][y] == n && i != x) return 0; // 넣을 수 없음. (충돌 있음)
	}
	return 1; // 넣을 수 있음. (충돌 없음)
}

int check_col(int x, int y, int n) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (BOARD[x][i] == n && i != y) return 0; // 열에 같은 숫자 발견
	}
	return 1;
}

int check_region(int x, int y, int n) {
	for (int i = (x/3)*3; i <= (x/3)*3+2; i++) {
		for (int j = (y/3)*3; j <= (y/3)*3+2; j++) {
			if (BOARD[i][j] == n && i != x && j != y) return 0; // 구역에 같은 숫자 발견
		}
	}
	return 1;
}

int isOkay(int x, int y, int n) {
	return check_row(x, y, n) && check_col(x, y, n) && check_region(x, y, n) ? 1 : 0;
	// 셋 중 하나라도 거짓이면 충돌 발생한것.
}

void printSolution() {
	solutionCnt++;

	printf("Solution %d\n", solutionCnt);

	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i % 3 == 0) {
			printf("-------------------------------\n");
		}
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (j % 3 == 0) {
				printf("|");
			}
			printf(" %d ", BOARD[i][j]);
		}
		printf ("|\n");
	}
	printf("-------------------------------\n");
}

void solveSudoku(int x, int y) {
	if (BOARD[x][y] > 0) {
		checkNext(x, y);
	}
	else {
		for (int i = 1; i <= 9; i++) {
			memcpy(&BOARD[x][y], &BOARD_SWP[x][y], 
				sizeof(int)*BOARD_SIZE*BOARD_SIZE - sizeof(int)*(x*BOARD_SIZE + y));
			if (isOkay(x, y, i)) {
				BOARD[x][y] = i;
				checkNext(x, y);
			}
		}
	}
}

void checkNext(int x, int y) {
	if (x == BOARD_SIZE - 1 && y == BOARD_SIZE - 1) {
		printSolution();
	}
	y++;
	if (y == BOARD_SIZE) {
		y = 0;
		x++;
	}
	solveSudoku(x, y);
}

void backupBoard() {
	memcpy(BOARD_SWP, BOARD, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
}

void cp_array(int from[], int to[], int size) {
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}

int main() {
	FILE *fp = fopen("D:/sudoku2.txt", "rt");

	int cnt = 0;
	if (fp == 0) return 0;
	while (!feof(fp) || cnt == BOARD_SIZE - 1) {
		int n_t[BOARD_SIZE];
		fscanf(fp, "%d %d %d %d %d %d %d %d %d\n", 
			&n_t[0], &n_t[1], &n_t[2], &n_t[3], &n_t[4], &n_t[5], &n_t[6], &n_t[7], &n_t[8]);
		cp_array(n_t, BOARD[cnt], BOARD_SIZE);
		cnt++;
	}
	fclose(fp);

	backupBoard();
	printf("Original Board\n");
	printBoard();
	solveSudoku(0, 0);

	return 0;
}