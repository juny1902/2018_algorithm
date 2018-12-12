#include <stdio.h>
#include <stdlib.h>

typedef struct SLL_NODE {
	int value;
	SLL_NODE *NEXT;
}SLL_NODE;

SLL_NODE *HEAD = 0;

SLL_NODE *make_node(int v) {
	SLL_NODE *NEW = (SLL_NODE *)malloc(sizeof(SLL_NODE));
	NEW->value = v;
	NEW->NEXT = 0;
	return NEW;
}
void add(int v) {
	SLL_NODE *NEW = make_node(v);
	SLL_NODE *CUR = HEAD;
	if (HEAD == 0) {
		HEAD = NEW;
		return;
	}
	else {
		while (1) {
			if (CUR->NEXT == 0) {
				CUR->NEXT = NEW;
				return;
			}
			else {
				CUR = CUR->NEXT;
			}

		}
	}

}


void remove(int v) {
	SLL_NODE *DEL = HEAD;
	if (HEAD->value == v) {
		HEAD = HEAD->NEXT;
		free(DEL);
		return;
	}
	else {
		SLL_NODE *DEL_NEXT = HEAD;
		while (DEL_NEXT != 0) {
			if (DEL_NEXT->NEXT->value == v) {
				DEL = DEL_NEXT->NEXT;
				DEL_NEXT->NEXT = DEL->NEXT;
				free(DEL);
				return;
			}
			else {
				DEL_NEXT = DEL_NEXT->NEXT;
			}
		}
	}
}
void destroy() {
	SLL_NODE *CUR = HEAD;
	while (1) {
		if (HEAD == 0) return;
		else {
			HEAD = HEAD->NEXT;
			free(CUR);
			CUR = HEAD;
		}
	}
}
void insert(int w, int v) {
	SLL_NODE *CUR = HEAD;
	while (1) {
		if (CUR->value == w) {
			SLL_NODE *NEW = make_node(v);
			NEW->NEXT = CUR->NEXT;
			CUR->NEXT = NEW;
			return;
		}
		else if (CUR == 0) {
			return;
		}
		else {
			CUR = CUR->NEXT;
		}
	}
}
void print_node() {
	SLL_NODE *CUR = HEAD;
	while (CUR != 0) {
		printf("%d\n", CUR->value);
		CUR = CUR->NEXT;
	}
}

int main() {
	add(3);
	add(5);
	destroy();
	add(1);
	add(2);
	remove(2);
	insert(1, 100);
	add(4);
	print_node();
	getchar();
	return 0;
}