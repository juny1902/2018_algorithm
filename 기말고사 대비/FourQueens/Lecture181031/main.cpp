#include <stdio.h>
#include <stdlib.h>
#define SZ 8

int BOARD[SZ][SZ]; // ������ ���� Board

int abs(int v) {
	if (v < 0) {
		return -v;
	}
	return v;
}

int checkUpside(int i, int j) { // ���� ���� ������ ��, �ƴϸ� ����
	int k = 0;
	for (k = i - 1; k >= 0; k--) {
		if (BOARD[k][j] != 0) return 1; // ������ j���� ���� ������ 1 ��ȯ
	}
	return 0;
}

//���� (i,j)�� ���� ��,
//�밢������ ���� ���⿡
//���� ������ 1�� ��ȯ
//������ 0�� ��ȯ
int checkDiagonal(int _i, int _j)
{
	for (int i = 0; i <= _i; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (BOARD[i][j] != 0)
			{
				if (abs(i - _i) == abs(j - _j)) // 2���� if�� &&�� �����ʴ����� ? ���� if�� false �� ���̻����ʿ䰡����.
				{
					return 1;
				}

				else
				{
					break; //�̷����ϸ� ���귮�� ���ϼ� �ִ�.
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
	doBacktracking(0); // 0����� Queen �� ���� ����.
	printf("Num. of solutions : %d\n", cnt_solutions);
	return 0;
}