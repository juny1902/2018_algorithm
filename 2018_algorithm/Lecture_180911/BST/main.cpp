#include <stdio.h>
#include <stdlib.h>
// 시험문제 : Judge 풀기.
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
			if (CUR->v > NEW->v) { // 추가할 값이 현재 노드보다 작다면 ? -> 왼쪽으로 가야함.
				if (CUR->LEFT == 0) { // 왼쪽 끝에 도달했다면
					CUR->LEFT = NEW; // 그곳에 새로운 노드 추가.
					return;
				}
				else { // 도달할 때 까지 왼쪽으로 쭉 이동.
					CUR = CUR->LEFT;
				}
			}
			else { // 추가할 값이 현재 노드보다 크다면 ? -> 오른쪽으로 가야함.
				if (CUR->RIGHT == 0) { // 오른쪽 끝에 도달했다면
					CUR->RIGHT = NEW; // 그곳에 새로운 노드 추가.
					return;
				}
				else { // 도달할 때 까지 오른쪽으로 쭉 이동.
					CUR = CUR->RIGHT;
				}

			}
		}
	}
}

BST_NODE *removeFromBST(BST_NODE *NODE, int key) {
	// 현재 노드가 Null 이면?
	if (NODE == 0) return 0;
	// 아무것도 할게 없이 함수 탈출.
	if (NODE->v == key) { // 지울 값을 찾았다면 ?
		// 지울 노드의 좌/우 자식 노드가 모두 비었다면 ?
		if (NODE->LEFT == 0 && NODE->RIGHT == 0) {
			// - 간단하게 그 노드를 지우면 됨.
			free(NODE);
			return 0;
		}

		// 지울 노드의 왼쪽 노드가 비었다면 ? -- 오른쪽 노드만 있는 경우.
		// - 오른쪽 노드를 반환하고 현재 노드 삭제.

		// 지울 노드의 오른쪽 노드가 비었다면 ? -- 왼족 노드만 있는 경우.
		// - 왼쪽 노드를 반환하고 현재 노드 삭제.

		// 지울 노드의 좌/우 자식 노드가 차있다면 ?
		// - 현재 BST 에서 대체할 노드를 찾는다 - (가장 작은 노드, findLeast 함수 정의하여 사용)
		// - 찾은 값을 대체한다.
	}
	else if (key < NODE->v) {
		// 지울 값이 현재 노드보다 작다면 ?
		// - 왼쪽부터 찾아나가서 그 결과를 왼쪽 노드에 대입.
		NODE->LEFT = removeFromBST(NODE->LEFT, key);
		return NODE;

	}
	else {
		// 지울 값이 현재 노드보다 크다면 ?
		// - 오른쪽부터 찾아나가서 그 결과를 오른쪽 노드에 대입.
		NODE->RIGHT = removeFromBST(NODE->RIGHT, key);
		return NODE;

	}
	return 0;
}


// 중간 노드를 언제 방문하냐에 따라 pre, in , post

void BST_InOrder_Traversal(BST_NODE *ROOT) { // BST 에서 오름차순 정렬.
	if (ROOT == 0) return;
	BST_InOrder_Traversal(ROOT->LEFT);
	printf("현재 노드 : %d\n", ROOT->v);
	BST_InOrder_Traversal(ROOT->RIGHT);
}

void BST_PreOrder_Traversal(BST_NODE *ROOT) {
	if (ROOT == 0) return;
	printf("현재 노드 : %d\n", ROOT->v);
	BST_PreOrder_Traversal(ROOT->LEFT);
	BST_PreOrder_Traversal(ROOT->RIGHT);
}

void BST_PostOrder_Traversal(BST_NODE *ROOT) {
	if (ROOT == 0) return;
	BST_PreOrder_Traversal(ROOT->LEFT);
	BST_PreOrder_Traversal(ROOT->RIGHT);
	printf("현재 노드 : %d\n", ROOT->v);
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
		printf("찾을 값을 입력하세요 : ");
		scanf_s("%d", &search);

		printf("%d : %d\n", search, SearchBST(search));

	}
	

}