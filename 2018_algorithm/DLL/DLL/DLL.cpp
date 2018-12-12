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

	if (DEL == 0) return; // ���� ��尡 ���� ���,

	if (DEL == HEAD) { // ���� ��尡 HEAD �� ���
		HEAD = HEAD->NEXT;
		free(DEL);
		if (HEAD != 0) {
			HEAD->PREV = 0;
		}
	}
	else if (DEL->NEXT != 0) { // ���� ��尡 ������ ��尡 �ƴ� ���
		DEL->NEXT->PREV = DEL->PREV;
		DEL->PREV->NEXT = DEL->NEXT;
		free(DEL);
	}
	else { // ���� ��尡 ������ ����� ���
		DEL->PREV->NEXT = 0;
		free(DEL);
	}
}

// d = 1 : w �� ���� ���
// d = -1 : w �� ���� ���
void insertToDLL(int w, int v, int d) {
	DLL_NODE *CUR = HEAD;
	while (1) { // ��� ��� Ž�� ����
		if (CUR == 0) {
			return; // ��� ��� ����.
		}
		else if (CUR->value == w) {
			break; // ���� ����� ��/�ڿ� �߰��ϰ��� ��.
		}
		else {
			CUR = CUR->NEXT; // ��������
		}
	}

	DLL_NODE *NEW = make_node(v);
	if (d == -1) { // ���� ����� ���� ��忡 �߰��ϰ��� ��.
		NEW->NEXT = CUR; // ���� ����, �߰��� ����� ���� ��尡 �ȴ�.
		NEW->PREV = CUR->PREV; // ���� ����� ���� ���� �߰��� ����� ���� ��尡 �ȴ�.
		CUR->PREV = NEW; // ���� ����� ���� ��忡 ���ο� ��� �߰�.
		if (NEW->NEXT != 0) { // ���� �� ����� ���� ��尡 �����Ѵٸ�
			NEW->NEXT->PREV = NEW; // �� ���� ���� �� ��尡 �� ��.
		}
		return;
	}
	else if (d == 1) { // ���� ����� ���� ��忡 �߰��ϰ��� ��.
		NEW->NEXT = CUR->NEXT; // ���� ����� ���� ���� �� ����� ���� ��尡 ��.
		NEW->PREV = CUR; // ���� ���� �� ����� ���� ��尡 ��.
		CUR->NEXT = NEW; // ���� ����� ���� ���� �� ��尡 ��.
		if (NEW->NEXT != 0) {
			NEW->NEXT->PREV = NEW;
		}

		return;
	}
	else {
		printf("��/�������� �������ּ���.\n");
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