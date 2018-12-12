#include <stdio.h>
#include <stdlib.h>
struct node {
	int v;
	struct node *NEXT;
};
typedef struct node NODE;
NODE *HEAD = 0;
NODE *make_node(int v) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->v = v; NEW->NEXT = 0;
	return NEW;
}
void addToSLL(int v) {
	NODE *NEW = make_node(v);
	if (HEAD == 0) {
		HEAD = NEW;
		return;
	}
	else {
		NODE *CUR = HEAD;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
void insertToSLL(int w,int v) {
	NODE *NEW = make_node(v);
	NODE *CUR = HEAD;
	while (CUR != 0) {
		if (CUR->v == w) {
			NEW->NEXT = CUR->NEXT;
			CUR->NEXT = NEW;
			return;
		}
		else {
			CUR = CUR->NEXT;
		}
	}
	NODE *TMP = HEAD;
	HEAD = HEAD->NEXT;
	NEW->NEXT = TMP;
	TMP->NEXT = HEAD;
	HEAD = NEW;
}
void printSLL() {
	NODE *CUR = HEAD;
	while (CUR != 0) {
		printf("%d ", CUR->v);
		CUR = CUR->NEXT;
	}
}
int main() {
	int i, n, d, where, toInsert;
	scanf("%d", &n);
	if (n < 1) return 0;
	for (i = 0; i < n; i++) {
		scanf("%d", &d);
		addToSLL(d);
	}
	scanf("%d %d", &where, &toInsert);
	insertToSLL(where, toInsert);
	printSLL();
}