#include <stdio.h>
#include <stdlib.h>
/*
	HEAP 조건 : 잘 생겼다, 맨 오른쪽만 비어져있고 나머지 노드는 꽉 채워져있음.
	가장 우선순위가 높은게 ROOT에 있음.
*/
int data[20] = { 0,6,3,5,7,10,1,2 }; // Max Heap 형태가 아님.
void swap(int *data, int idx1, int idx2) {
	int tmp = data[idx1];
	data[idx1] = data[idx2];
	data[idx2] = tmp;
}

void findLocation(int cur_idx, int lastidx) {
	// 현재 인덱스의 두배가 되는 지점이 왼쪽 자식노드가 될 것.
	// 현재 인덱스의 두배가 되는 지점의 다음 지점이 오른쪽 자식노드가 될 것.
	// 가장 큰 값을 가지는 노드의 인덱스의 초기값은 일단 현재 노드로 설정한다.

	// 왼쪽 노드의 인덱스가 범위 내에 있고, 현재 노드 보다 크다면
	// 큰 값은 왼쪽 노드가 될 것이다.
	
	// 왼쪽 노드의 인덱스가 범위 내에 있고, 현재 노드 보다 작다면
	// 작은 값은 오른쪽 노드가 될 것이다.
	
	// 현재 노드가 가장 크다면 아무것도 할게 없음(굳이 위치를 찾을 필요가 없음).

	// 그렇지 않다면?
	// 둘중 큰 값과 현재 노드랑 교환
	// 재귀적으로 큰 값(인덱스) 에 대하여 findLocation 수행.
	
}

void heapify(int lastidx) { // Max Heap 형태로 만듬.
	/*
		왼쪽 자식 인덱스 : ROOT 인덱스 * 2
		오른쪽 자식 인덱스 : 왼쪽 자식 인덱스 + 1

		자식이 있는 마지막 노드(인덱스가 1보다 큰 마지막 노드)부터 바꿔나감. (마지막 노드의 부모 노드)
	*/
}

int removeRoot(int lastidx) { // 루트를 반환.
	// 루트를 반환할 준비.
	// 마지막 값을 루트로 우선 올리고, 루트부터 마지막 인덱스의 이전 노드까지 제 위치를 찾도록 한다.
	return 0;
}

void addToHeap(int v, int lastidx) {
	// 마지막에 새로운 값 추가
	int cur_idx = lastidx + 1;
	// 그 노드의 부모 노드부터 바꿔나감.
	int parent_idx = cur_idx / 2;

	data[cur_idx] = v;
	// 반복하며
	while (1) {
		// 자식보다 부모가 크면 완료.
		if (data[cur_idx] < data[parent_idx]) {
			return;
		}
		else {
			// 아니면 부모 노드와 현재 노드 교환하고 부모노드를 상위로 올림
			swap(data, parent_idx, cur_idx);
			cur_idx = parent_idx;
			parent_idx = cur_idx / 2;
			// 한 수준 올림.
			if (parent_idx < 1) return;
		}
	}
}

void printAll(int *data, int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}
int main() {
	heapify(7);
	printf("현재 루트 : %d\n", data[1]);
	addToHeap(30, 7);
	printf("현재 루트 : %d\n", data[1]);
	addToHeap(40, 8);
	printf("현재 루트 : %d\n", data[1]);
	addToHeap(20, 9);
	printf("현재 루트 : %d\n", data[1]);
	int k = removeRoot(9);
	printf("제거 루트 : %d, 현재 루트 : %d\n", k, data[1]);

	k = removeRoot(8);
	printf("제거 루트 : %d, 현재 루트 : %d\n", k, data[1]);

	k = removeRoot(7);
	printf("제거 루트 : %d, 현재 루트 : %d\n", k, data[1]);

	k = removeRoot(6);
	printf("제거 루트 : %d, 현재 루트 : %d\n", k, data[1]);
	

	getchar();
	return 0;
}