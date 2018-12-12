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
	NEW->v = v; NEW->PREV = 0; NEW->NEXT = 0;
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
void insertToDLL(int w, int v) {
	DLL_NODE *CUR = HEAD;
	while (1) {
		if (CUR == 0) {
			return;
		}
		else if (CUR->v == w) {
			break;
		}
		else {
			CUR = CUR->NEXT;
		}
	}
	DLL_NODE *NEW = make_node(v);
	NEW->NEXT = CUR->NEXT;
	if (CUR->NEXT != 0) CUR->NEXT->PREV = NEW;
	NEW->PREV = CUR;
	CUR->NEXT = NEW;
	
	return;
}
void deleteFromDLL(int v) {
	DLL_NODE *DEL = HEAD;
	while (DEL != 0) { // 우선 del 커서를 지울곳으로 이동.
		if (DEL->v == v) break;
		else {
			DEL = DEL->NEXT;
		}
	}
	if (DEL == 0) return; // 지울게 없음.

	if (DEL == HEAD) {
		HEAD = HEAD->NEXT;
		if (HEAD != 0) {
			HEAD->PREV = 0;
		}
		free(DEL);
	}
	else if (DEL->NEXT != 0) { // DEL 이 중간에 끼어있음.
		DEL->NEXT->PREV = DEL->PREV;
		DEL->PREV->NEXT = DEL->NEXT;
		free(DEL);
	}
	else { // DEL 이 마지막 노드
		DEL->PREV->NEXT = 0;
		free(DEL);

	}
}

int countElement(int v) {
	int c = 0;
	DLL_NODE *CUR = HEAD;
	while (CUR != 0) {
		if (CUR->v == v) c++;
		CUR = CUR->NEXT;
	}
	return c;
}

void printDLL() {
	if (HEAD == 0) {
		printf("-999");
	}
	else {
		DLL_NODE *CUR = HEAD;
		while (CUR != 0) {
			printf("%d ", CUR->v);
			CUR = CUR->NEXT;
		}
	}
}
DLL_NODE *find_tail() {
	DLL_NODE *TAIL = HEAD;
	while (TAIL->NEXT != 0) {
		TAIL = TAIL->NEXT;
	}
	return TAIL;
}
void printDLLinv() {
	if (HEAD == 0) {
		printf("-999");
	}
	else {
		DLL_NODE *CUR = find_tail();
		while (CUR != 0) {
			printf("%d ", CUR->v);
			CUR = CUR->PREV;
		}
	}
}

int main() {
	int i, n, x;
	int w, v;
	scanf("%d", &n);
	if (n < 1) return 0;
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		addToDLL(x);
	}
	scanf("%d %d", &w, &v);
	insertToDLL(w, v);
	printDLLinv();
	return 0;
}