#include "SLL.h"

NODE_SLL *make_node(int _v) // Vertex _v �� ����� Edge�� ����.
{
	NODE_SLL *NEW = (NODE_SLL *)malloc(sizeof(NODE_SLL)); // ������ �Ҵ� ���� ��
	NEW->NEXT = 0; NEW->v = _v; // Edge �� ����� Vertex �� _v ���� ����.
	return NEW; // �ش� Edge ��ȯ
}
// �������� �پ��� ����� ���� �� ����.
void addToSLL(NODE_SLL **src, int dst) // �־��� Vertex src �� dst �� �����ϴ� Edge�� �����Ѵ�.
{
	// ������ SLL �迭�� v1�� �ش��ϴ� �ε����� v2 ���� ���� ��带 �߰��ϴ� ��.
	NODE_SLL *NEW = make_node(dst); // v2 �� ����� ���ο� Edge�� ����.
	if (*src == 0) { // Vertex v1 �� �ٸ� Vertex �� ���� ����Ǿ����� �ʴٸ�?
		*src = NEW; // Vertex v1 �� ���� �մ��� ���ο� Edge�� ����. 
		return;
	}
	else { // ������ �̹� Edge �� �����Ѵٸ� ?
		NODE_SLL *CUR = *src;  // �ش� Vertex�� ù��°�� ����� Vertex ���� ...
		while (CUR->NEXT != 0) { // �̹� �����ϴ� Edge�� ��� ����
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW; // �� �������� ���ο� Edge�� ����.
		return;
	}
}

void printSLL(NODE_SLL *NODE) { // SLL�� ��� ��带 ����Ѵ�.
	NODE_SLL *CUR = NODE;
	while (CUR != 0) {
		printf("�� %c �� ����Ǿ� �ֽ��ϴ�.\n", CUR->v + 'A');
		CUR = CUR->NEXT;
	}
}