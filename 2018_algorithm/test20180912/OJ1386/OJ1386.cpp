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

int countsame(BST_NODE *NODE, int v) {
	BST_NODE *CUR = NODE;
	int count = 0;
	while (CUR != 0) {
		if (CUR->v == v) {
			count++;
			CUR = CUR->RIGHT;
		}
		else if (v < CUR->v) {
			CUR = CUR->LEFT;
		}
		else {
			CUR = CUR->RIGHT;
		}
	}
	return count;

}

void BST_inorder(BST_NODE *NODE) {
	int count = 0;
	if (NODE == 0)return;
	BST_inorder(NODE->LEFT);

	if ((count = countsame(ROOT, ROOT->v)) > 1) {
		printf("%d %d ", NODE->v, count);
	}
	else {
		printf("%d ", NODE->v);
	}
	BST_inorder(NODE->RIGHT);
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