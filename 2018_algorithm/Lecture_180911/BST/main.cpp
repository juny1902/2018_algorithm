#include <stdio.h>
#include <stdlib.h>
// ���蹮�� : Judge Ǯ��.
typedef struct BST_NODE {
	int v;
	BST_NODE *LEFT;
	BST_NODE *RIGHT;
}BST_NODE;

BST_NODE *ROOT = 0;

BST_NODE *make_node(int v) {
	BST_NODE *NEW = (BST_NODE *)malloc(sizeof(BST_NODE));
	NEW->RIGHT = 0; NEW->LEFT = 0; NEW->v = v;
	return NEW;
}
void addToBST(int v) {
	BST_NODE *NEW = make_node(v);
	if (ROOT == 0) {
		ROOT = NEW;
		return;
	}
	else {
		BST_NODE *CUR = ROOT;
		while (CUR != 0) {
			if (CUR->v > NEW->v) { // �߰��� ���� ���� ��庸�� �۴ٸ� ? -> �������� ������.
				if (CUR->LEFT == 0) { // ���� ���� �����ߴٸ�
					CUR->LEFT = NEW; // �װ��� ���ο� ��� �߰�.
					return;
				}
				else { // ������ �� ���� �������� �� �̵�.
					CUR = CUR->LEFT;
				}
			}
			else { // �߰��� ���� ���� ��庸�� ũ�ٸ� ? -> ���������� ������.
				if (CUR->RIGHT == 0) { // ������ ���� �����ߴٸ�
					CUR->RIGHT = NEW; // �װ��� ���ο� ��� �߰�.
					return;
				}
				else { // ������ �� ���� ���������� �� �̵�.
					CUR = CUR->RIGHT;
				}

			}
		}
	}
}

BST_NODE *removeFromBST(BST_NODE *NODE, int key) {
	// ���� ��尡 Null �̸�?
	if (NODE == 0) return 0;
	// �ƹ��͵� �Ұ� ���� �Լ� Ż��.
	if (NODE->v == key) { // ���� ���� ã�Ҵٸ� ?
		// ���� ����� ��/�� �ڽ� ��尡 ��� ����ٸ� ?
		if (NODE->LEFT == 0 && NODE->RIGHT == 0) {
			// - �����ϰ� �� ��带 ����� ��.
			free(NODE);
			return 0;
		}

		// ���� ����� ���� ��尡 ����ٸ� ? -- ������ ��常 �ִ� ���.
		// - ������ ��带 ��ȯ�ϰ� ���� ��� ����.

		// ���� ����� ������ ��尡 ����ٸ� ? -- ���� ��常 �ִ� ���.
		// - ���� ��带 ��ȯ�ϰ� ���� ��� ����.

		// ���� ����� ��/�� �ڽ� ��尡 ���ִٸ� ?
		// - ���� BST ���� ��ü�� ��带 ã�´� - (���� ���� ���, findLeast �Լ� �����Ͽ� ���)
		// - ã�� ���� ��ü�Ѵ�.
	}
	else if (key < NODE->v) {
		// ���� ���� ���� ��庸�� �۴ٸ� ?
		// - ���ʺ��� ã�Ƴ����� �� ����� ���� ��忡 ����.
		NODE->LEFT = removeFromBST(NODE->LEFT, key);
		return NODE;

	}
	else {
		// ���� ���� ���� ��庸�� ũ�ٸ� ?
		// - �����ʺ��� ã�Ƴ����� �� ����� ������ ��忡 ����.
		NODE->RIGHT = removeFromBST(NODE->RIGHT, key);
		return NODE;

	}
	return 0;
}


// �߰� ��带 ���� �湮�ϳĿ� ���� pre, in , post

void BST_InOrder_Traversal(BST_NODE *ROOT) { // BST ���� �������� ����.
	if (ROOT == 0) return;
	BST_InOrder_Traversal(ROOT->LEFT);
	printf("���� ��� : %d\n", ROOT->v);
	BST_InOrder_Traversal(ROOT->RIGHT);
}

void BST_PreOrder_Traversal(BST_NODE *ROOT) {
	if (ROOT == 0) return;
	printf("���� ��� : %d\n", ROOT->v);
	BST_PreOrder_Traversal(ROOT->LEFT);
	BST_PreOrder_Traversal(ROOT->RIGHT);
}

void BST_PostOrder_Traversal(BST_NODE *ROOT) {
	if (ROOT == 0) return;
	BST_PreOrder_Traversal(ROOT->LEFT);
	BST_PreOrder_Traversal(ROOT->RIGHT);
	printf("���� ��� : %d\n", ROOT->v);
}

int SearchBST(int key) { // v �� ������ 1 ��ȯ, ������ 0 ��ȯ
	BST_NODE *CUR = ROOT;

	while (CUR != 0) {
		if (CUR->v == key) {
			return 1;
		}
		else if (key > CUR->v) {
			CUR = CUR->RIGHT;
		}
		else if (key < CUR->v) {
			CUR = CUR->LEFT;
		}
	}
	return 0;
}

int main() {
	addToBST(100);
	addToBST(50);
	addToBST(150);
	addToBST(25);
	addToBST(75);
	addToBST(125);
	addToBST(175);
	BST_InOrder_Traversal(ROOT);
	while (1) {
		int search;
		printf("ã�� ���� �Է��ϼ��� : ");
		scanf_s("%d", &search);

		printf("%d : %d\n", search, SearchBST(search));

	}
	

}