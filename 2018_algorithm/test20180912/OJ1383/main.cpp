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

void strDLL() {
	DLL_NODE *CUR = HEAD;
	while (CUR != 0) {
		printf("%d ", CUR->v);
		CUR = CUR->NEXT;
	}
}
void deleteNode(int v) {

	DLL_NODE *DEL = HEAD;

	while (DEL != 0) {
		if (DEL->v == v) break;
		DEL = DEL->NEXT;
	}
	if (HEAD == 0) return;
	if (DEL == HEAD) { // 지울 노드가 HEAD 인 경우
		HEAD = HEAD->NEXT;
		free(DEL);
		if (HEAD != 0) {
			HEAD->PREV = 0;
		}
	}
	if (DEL->NEXT != 0) { // DEL 이 가운데 낀 경우
		DEL->NEXT->PREV = DEL->PREV;
		DEL->PREV->NEXT = DEL->NEXT;
		free(DEL);
	}
	else { // DEL 이 마지막 
		DEL->PREV->NEXT = 0;
		free(DEL);
	}
}
int main() {
	int d;
	while (1) {
		scanf("%d", &d);
		if (d < 0) {
			if (HEAD != 0) invDLL();
			return 0;
		}
		else {
			if (isExist(d)) {
				deleteNode(d);
				addToDLL(d);
			}

			else {
				addToDLL(d);
			}

		}
	}
	return 0;
}