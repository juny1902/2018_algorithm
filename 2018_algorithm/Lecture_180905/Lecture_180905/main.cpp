// 1���� 
// ������ ���� ������

// �迭�� malloc ���� ? 
// �迭 : ���� �Ҵ� (���α׷� ���� �� �̸� �Ҵ��� ��. �޸� ���� �Ұ�.)
// malloc : ���� �Ҵ� (malloc �κп��� �Ҵ��. �޸� ���� ����.)

/*
Array �� ����
- ������� : �ѹ� ���ϸ� ���߿� ũ�⸦ �����ϱ� �����.
- ��� �ذ�? -> Linked List ����.
Linked List �� ����
- Array �� ���� �غ�
Linked List �� ����
- High Cost - (�ð�, ����...)

*/
#include "SLL.h"
SLL_NODE *HEAD = 0;

int main() {
	
	add(10, &HEAD);
	add(4, &HEAD);
	add(87, &HEAD);
	add(6,&HEAD);
	add(58,&HEAD);
	traversal(&HEAD);
	
	getchar();
	return 0;
}