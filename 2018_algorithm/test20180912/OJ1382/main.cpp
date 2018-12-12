#include <stdio.h>
#include <stdlib.h>
typedef struct DLL_NODE {
	int v;
	DLL_NODE *PREV;
	DLL_NODE *NEXT;
}DLL_NODE;

DLL_NODE *HEAD = 0;

DLL_NODE *make_node(int v) {
	DLL_NODE *NEW = (DLL_NODE *)malloc(sizeof(DLL_NODE));
	NEW->PREV = NEW->NEXT = 0;
	NEW->v = v;
	return NEW;
}

void addToDLL(int v) {
	DLL_NODE *NEW = make_node(v);

	if (HEAD == 0) {
		HEAD = NEW;
		return;
	}
	else {
		DLL_NODE *CUR = HEAD;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
		NEW->PREV = CUR;
		return;
	}
}
int isExist(int v) {
	DLL_NODE *CUR = HEAD;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}
DLL_NODE *find_tail() {
	DLL_NODE *TAIL = HEAD;
	while (TAIL->NEXT != 0) {
		TAIL = TAIL->NEXT;
	}
	return TAIL;
}
void invDLL() {
	DLL_NODE *TAIL = find_tail();
	while (TAIL != 0) {
		printf("%d ", TAIL->v);
		TAIL = TAIL->PREV;
	}
}
int main() {
	int i, d;
	while (1) {
		scanf("%d", &d);
		if (d < 0) {
			invDLL();
			return 0;
		}
		else {
			if (!isExist(d)) {
				addToDLL(d);
			}
		}
	}
	return 0;
}