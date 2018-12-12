#include <stdio.h>
#include <stdlib.h>

#define SZ 4

int BOARD[SZ][SZ];

typedef struct QUEEN{
	int x, y;
	QUEEN *NEXT;
}QUEEN;

QUEEN *HEAD = 0;

QUEEN *make_queen_node(int x, int y) {
	QUEEN *NEW = (QUEEN *)malloc(sizeof(QUEEN));
	NEW->x = x;
	NEW->y = y;
	NEW->NEXT = 0;
	return NEW;
}

QUEEN *findQueenNode(int x, int y) {
	QUEEN *CUR = HEAD;
	while (CUR != 0) {
		if (CUR->x == x && CUR->y == y) return CUR;
		CUR = CUR->NEXT;
	}
	return 0;
}
int isThereQueen(int x, int y) {
	QUEEN *CUR = HEAD;
	while (CUR != 0) {
		if (CUR->x == x && CUR->y == y) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}

void placeQueen(int x, int y) {
	if (isThereQueen(x, y))return;
	QUEEN *NEW = make_queen_node(x, y);
	if (HEAD == 0) {
		HEAD = NEW;
		return;
	}
	else {
		QUEEN *CUR = HEAD;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}

void deleteNode(QUEEN *TARGET) {
	if (HEAD == TARGET) {
		QUEEN *TMP = HEAD;
		HEAD = HEAD->NEXT;
		free(TMP);
	}
	QUEEN *DEL_NEXT = HEAD;
	while (DEL_NEXT != 0) {
		if (DEL_NEXT->NEXT == TARGET) break;
		DEL_NEXT = DEL_NEXT->NEXT;
	}
	if (DEL_NEXT != 0) {
		QUEEN *DEL = DEL_NEXT->NEXT;
		if (DEL->NEXT != 0) {
			DEL_NEXT->NEXT = DEL->NEXT;
		}
		else {
			DEL_NEXT->NEXT = 0;
		}
		free(DEL);
	}

}

void removeQueen(int x, int y) {
	QUEEN *CUR = HEAD;
	while (CUR != 0) {
		if (CUR->x == x && CUR->y == y) {
			deleteNode(CUR);
			return;
		}
		CUR = CUR->NEXT;
	}
}

int abs(int v) {
	if (v < 0) return -v;
	return v;
}

int checkUpside(int x, int y) {
	for (int i = 0; i < x; i++) {
		if (BOARD[i][y] != 0) return 0;
	}
	return 1;
}
int checkDiagonal(int x, int y) {
	for (int i = 0; i < x; i++) {
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
int isOkay(int x, int y) {
	return checkUpside(x, y) && checkDiagonal(x, y) ? 1 : 0;
}

void checkBoard() {
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			printf("%d ", BOARD[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void doBacktracking(int row) {
	for (int col = 0; col < SZ; col++) {
		if (isOkay(row, col)) {
			placeQueen(row, col);
			if (row < SZ - 1) {
				doBacktracking(row + 1);
			}
			else {
				checkBoard();
			}
			placeQueen(row, col);
		}
		
	}

}
void showBoard() {
	QUEEN *CUR = HEAD;
	while (CUR != 0) {
		printf("%d %d\n", CUR->x, CUR->y);
		CUR = CUR->NEXT;
	}
}
int main() {
	placeQueen(1, 2);
	placeQueen(3, 3);
	placeQueen(0, 2);
	placeQueen(2, 2);
	placeQueen(1, 2);
	removeQueen(2, 2);
	showBoard();
	return 0;
}