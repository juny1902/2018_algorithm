#include <stdio.h>
#include <stdlib.h>

typedef struct BST_NODE {
	int v;
	BST_NODE *LEFT;
	BST_NODE *RIGHT;
}BST_NODE;
BST_NODE *ROOT = 0;
BST_NODE *make_node(int v) {
	BST_NODE *NEW = (BST_NODE *)malloc(sizeof(BST_NODE));
	NEW->LEFT = NEW->RIGHT = 0;
	NEW->v = v;
	return NEW;
}
void addToBST(int v) {
	BST_NODE *NEW = make_node(v);
	if (ROOT == 0) {
		ROOT = NEW;
		return;
	}
	BST_NODE *CUR = ROOT;
	while (CUR != 0) {
		if (NEW->v < CUR->v) {
			if (CUR->LEFT == 0) {
				CUR->LEFT = NEW;
				return;
			}
			else {
				CUR = CUR->LEFT;
			}
		}
		else {
			if (CUR->RIGHT == 0) {
				CUR->RIGHT = NEW;
				return;
			}
			else {
				CUR = CUR->RIGHT;
			}
		}
	}
}
int findValue(int v) {
	BST_NODE *CUR = ROOT;
	while (CUR != 0) {
		if (CUR->v == v) {
			return 1;
		}
		else if (v < CUR->v) {
			CUR = CUR->LEFT;
		}
		else {
			CUR = CUR->RIGHT;
		}
	}
	return 0;
}

void BSTtraversal(BST_NODE *ROOT) {
	if (ROOT == 0)return;
	BSTtraversal(ROOT->LEFT);
	printf("%d ", ROOT->v);
	BSTtraversal(ROOT->RIGHT);
}
int main() {
	addToBST(3);
	addToBST(5);
	addToBST(1);
	addToBST(2);
	addToBST(3);
	printf("%d", findValue(3));
	BSTtraversal(ROOT);

}