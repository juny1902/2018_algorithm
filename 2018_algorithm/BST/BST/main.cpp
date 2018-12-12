#include <stdio.h>
#include <stdlib.h>

typedef struct BST_NODE {
	int v;
	BST_NODE *LEFT;
	BST_NODE *RIGHT;
}BST_NODE;

BST_NODE *ROOT = 0;
BST_NODE *findLeast(BST_NODE *NODE);
BST_NODE *make_node(int v) {
	BST_NODE *NEW = (BST_NODE *)malloc(sizeof(BST_NODE));
	NEW->v = v; NEW->LEFT = 0; NEW->RIGHT = 0;
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
			if (NEW->v < CUR->v) { // 새로운 값이 부모 노드보다 작으면 왼쪽
				if (CUR->LEFT == 0) { // 왼쪽이 비어있다면 삽입
					CUR->LEFT = NEW;
					return;
				}
				else {
					CUR = CUR->LEFT; // 아니면 계속 왼쪽 노드로
				}
			}
			else {  // 새로운 값이 부모 노드보다 크면 오른쪽
				if (CUR->RIGHT == 0) { // 오른쪽이 비어있다면 삽입
					CUR->RIGHT = NEW;
					return;
				}
				else {
					CUR = CUR->RIGHT; // 아니면 계속 오른쪽으로
				}
			}

		}
	}
}

BST_NODE *removeFromBST(BST_NODE *NODE, int key) {
	if (NODE == 0) return 0;
	if (key == NODE->v) {
		if (NODE->LEFT == 0 && NODE->RIGHT == 0) {
			free(NODE);
			return 0;
		}
		else if (NODE->LEFT == 0) {
			BST_NODE *ret = NODE->RIGHT;
			free(NODE);
			return ret;
		}
		else if (NODE->RIGHT == 0) {
			BST_NODE *ret = NODE->LEFT;
			free(NODE);
			return ret;
		}
		else {
			BST_NODE *toReplace = findLeast(NODE);
			NODE->v = toReplace->v;
			NODE->RIGHT = removeFromBST(NODE->RIGHT, toReplace->v);
			return NODE;
		}
		
	}
	else if (key < NODE->v) {
		NODE->LEFT = removeFromBST(NODE->LEFT, key);
		return NODE;
	}
	else {
		NODE->RIGHT = removeFromBST(NODE->RIGHT, key);
		return NODE;
	}
}
BST_NODE *findLeast(BST_NODE *NODE) {
	BST_NODE *CUR = NODE;
	while (CUR->LEFT != 0) {
		CUR = CUR->LEFT;
	}
	return CUR;
}
void inorderBST(BST_NODE *ROOT) {
	if (ROOT != 0) {
		inorderBST(ROOT->LEFT);
		printf("현재 노드의 값은 %d 입니다.\n", ROOT->v);
		inorderBST(ROOT->RIGHT);
	}
	
}
int SearchBST(int key) { // v 가 있으면 1 반환, 없으면 0 반환
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
	addToBST(3);
	addToBST(7);
	addToBST(1);
	addToBST(5);
	addToBST(4);
	removeFromBST(ROOT,7);
	inorderBST(ROOT);
	getchar();
	return 0;
}