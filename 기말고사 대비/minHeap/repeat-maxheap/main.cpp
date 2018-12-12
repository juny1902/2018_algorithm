#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_SIZE 20
int HEAP[MAX_HEAP_SIZE];
int heapend = 0;
void printHeapRaw() {
	printf("---------- Raw Array ----------\n");
	for (int i = 0; i < MAX_HEAP_SIZE; i++) {
		printf("%d - ", HEAP[i]);
	}
	printf("\n");
	printf("-------------------------------\n");
}
void addToHeap(int v) {
	if (heapend == MAX_HEAP_SIZE - 1) return;

	heapend++;
	HEAP[heapend] = v;

	int me = heapend;
	int parent = (me>>1);
	
	while (1) {
		if (parent < 1 || HEAP[me] > HEAP[parent]) {
			printHeapRaw();
			return;
		}
		int tmp = HEAP[parent];
		HEAP[parent] = HEAP[me];
		HEAP[me] = tmp;

		me = parent;
		parent = (me>>1);
	}
	
}

int getSmallerIdx(int idx) {
	int left_child = idx * 2;
	int right_child = left_child + 1;

	if (right_child > heapend) return left_child;
	if (HEAP[right_child] > HEAP[left_child]) return left_child;
	else return right_child;
}

int deleteFromHeap() {
	if (heapend < 1) return -999;

	int ret = HEAP[1];

	HEAP[1] = HEAP[heapend];
	HEAP[heapend] = 0;
	heapend--;

	int me = 1;

	while (1) {
		
		int left_child = (me<<1);
		int right_child = left_child + 1;

		if (left_child > heapend) break;

		int smaller_idx = getSmallerIdx(me);
		if (HEAP[me] < HEAP[smaller_idx]) break;
		else {
			int tmp = HEAP[me];
			HEAP[me] = HEAP[smaller_idx];
			HEAP[smaller_idx] = tmp;

			me = smaller_idx;
		}


	}
	return ret;
}


int main() {
	addToHeap(3);
	addToHeap(3);
	addToHeap(4);
	addToHeap(4);
	addToHeap(2);
	addToHeap(2);
	addToHeap(2);
	addToHeap(1);
	addToHeap(1);
	addToHeap(5);
	addToHeap(3);
	addToHeap(100);
	addToHeap(100);
	addToHeap(100);
	addToHeap(50);
	addToHeap(20);
	addToHeap(3);

	for (int i = 0; i < MAX_HEAP_SIZE - 1; i++)
		printf("Picked up : %d\n", deleteFromHeap());
	return 0;
}