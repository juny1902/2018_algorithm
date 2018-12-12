#include <stdio.h>
#include <stdlib.h>

typedef struct DLL_NODE {
	int value;
	DLL_NODE *PREV;
	DLL_NODE *NEXT;
}DLL_NODE;

DLL_NODE *HEAD = 0;
DLL_NODE *make_node(int v) {
	DLL_NODE *NEW = (DLL_NODE *)malloc(sizeof(DLL_NODE));
	NEW->NEXT = 0; NEW->PREV = 0;
	NEW->value = v;
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

void deleteFromDLL(int v) {
	DLL_NODE *DEL = HEAD;

	while (DEL != 0) {
		if (DEL->value == v) break;
		else DEL = DEL->NEXT;
	}

	if (DEL == 0) return; // 지울 노드가 없는 경우,

	if (DEL == HEAD) { // 지울 노드가 HEAD 인 경우
		HEAD = HEAD->NEXT;
		free(DEL);
		if (HEAD != 0) {
			HEAD->PREV = 0;
		}
	}
	else if (DEL->NEXT != 0) { // 지울 노드가 마지막 노드가 아닌 경우
		DEL->NEXT->PREV = DEL->PREV;
		DEL->PREV->NEXT = DEL->NEXT;
		free(DEL);
	}
	else { // 지울 노드가 마지막 노드인 경우
		DEL->PREV->NEXT = 0;
		free(DEL);
	}
}

// d = 1 : w 의 다음 노드
// d = -1 : w 의 이전 노드
void insertToDLL(int w, int v, int d) {
	DLL_NODE *CUR = HEAD;
	while (1) { // 대상 노드 탐색 과정
		if (CUR == 0) {
			return; // 대상 노드 없음.
		}
		else if (CUR->value == w) {
			break; // 현재 노드의 앞/뒤에 추가하고자 함.
		}
		else {
			CUR = CUR->NEXT; // 다음으로
		}
	}

	DLL_NODE *NEW = make_node(v);
	if (d == -1) { // 현재 노드의 이전 노드에 추가하고자 함.
		NEW->NEXT = CUR; // 현재 노드는, 추가할 노드의 다음 노드가 된다.
		NEW->PREV = CUR->PREV; // 현재 노드의 이전 노드는 추가할 노드의 이전 노드가 된다.
		CUR->PREV = NEW; // 현재 노드의 이전 노드에 새로운 노드 추가.
		if (NEW->NEXT != 0) { // 만약 새 노드의 다음 노드가 존재한다면
			NEW->NEXT->PREV = NEW; // 그 이전 노드는 새 노드가 될 것.
		}
		return;
	}
	else if (d == 1) { // 현재 노드의 다음 노드에 추가하고자 함.
		NEW->NEXT = CUR->NEXT; // 현재 노드의 다음 노드는 새 노드의 다음 노드가 됨.
		NEW->PREV = CUR; // 현재 노드는 새 노드의 이전 노드가 됨.
		CUR->NEXT = NEW; // 현재 노드의 다음 노드는 새 노드가 됨.
		if (NEW->NEXT != 0) {
			NEW->NEXT->PREV = NEW;
		}

		return;
	}
	else {
		printf("순/역방향을 선택해주세요.\n");
	}
}

void forwardDLL() {
	DLL_NODE *CUR = HEAD;
	while (CUR != 0) {
		printf("%d\n", CUR->value);
		CUR = CUR->NEXT;
	}
}

void destroyDLL() {
	DLL_NODE *CUR = HEAD;
	while (1) {
		if (HEAD == 0) return;
		else {
			HEAD = HEAD->NEXT;
			free(CUR);
			CUR = HEAD;
		}
	}
}

int main() {

	addToDLL(3);
	addToDLL(5);
	addToDLL(1);
	deleteFromDLL(1);
	addToDLL(6);
	addToDLL(2);
	insertToDLL(1, 100, -1);
	destroyDLL();
	forwardDLL();
	getchar();
	return 0;
}