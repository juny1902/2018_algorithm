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
	else {
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
}

void BST_inorder(BST_NODE *ROOT) {
	if (ROOT == 0)return;
	BST_inorder(ROOT->LEFT);
	printf("%d ", ROOT->v);
	BST_inorder(ROOT->RIGHT);
}

int main() {
	int d;
	while (1) {
		scanf("%d", &d);
		if (d == -1) {
			BST_inorder(ROOT);
			break;
		}
		else {
			addToBST(d);
		}
	}
	return 0;
}