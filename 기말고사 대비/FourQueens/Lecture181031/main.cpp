#include <stdio.h>
#include <stdlib.h>
#define SZ 8

int BOARD[SZ][SZ]; // 게임을 위한 Board

int abs(int v) {
	if (v < 0) {
		return -v;
	}
	return v;
}

int checkUpside(int i, int j) { // 위에 뭔가 있으면 참, 아니면 거짓
	int k = 0;
	for (k = i - 1; k >= 0; k--) {
		if (BOARD[k][j] != 0) return 1; // 같은행 j열에 뭔가 있으면 1 반환
	}
	return 0;
}

//내가 (i,j)에 있을 때,
//대각선으로 위쪽 방향에
//누가 있으면 1을 반환
//없으면 0을 반환
int checkDiagonal(int _i, int _j)
{
	for (int i = 0; i <= _i; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (BOARD[i][j] != 0)
			{
				if (abs(i - _i) == abs(j - _j)) // 2개의 if를 &&로 묶지않는이유 ? 앞의 if가 false 면 더이상할필요가없음.
				{
					return 1;
				}

				else
				{
					break; //이렇게하면 연산량을 줄일수 있다.
				}
			}
		}
	}
	return 0;
}
int cnt_solutions = 0;
void checkBoard() {
	cnt_solutions++;
	printf("---------------------------------\n");
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			printf("| %d ", BOARD[i][j]);
		}
		printf("|");
		printf("\n");
		printf("---------------------------------\n");
	}
	printf("\n");
}

void doBacktracking(int row) {
	for (int i = 0; i < SZ; i++) {
		if (checkDiagonal(row, i)==0 && checkUpside(row, i)==0) {
			BOARD[row][i] = 1;
			if (row < SZ - 1) {
				doBacktracking(row+1);
			}
			else {
				checkBoard();
			}
			BOARD[row][i] = 0;
		}
	}
}

int main(void) {
	doBacktracking(0); // 0행부터 Queen 을 놓고 시작.
	printf("Num. of solutions : %d\n", cnt_solutions);
	return 0;
}