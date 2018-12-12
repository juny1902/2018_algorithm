#include <stdio.h>
#include <stdlib.h>
/*
	HEAP ���� : �� �����, �� �����ʸ� ������ְ� ������ ���� �� ä��������.
	���� �켱������ ������ ROOT�� ����.
*/
int data[20] = { 0,6,3,5,7,10,1,2 }; // Max Heap ���°� �ƴ�.
void swap(int *data, int idx1, int idx2) {
	int tmp = data[idx1];
	data[idx1] = data[idx2];
	data[idx2] = tmp;
}

void findLocation(int cur_idx, int lastidx) {
	// ���� �ε����� �ι谡 �Ǵ� ������ ���� �ڽĳ�尡 �� ��.
	// ���� �ε����� �ι谡 �Ǵ� ������ ���� ������ ������ �ڽĳ�尡 �� ��.
	// ���� ū ���� ������ ����� �ε����� �ʱⰪ�� �ϴ� ���� ���� �����Ѵ�.

	// ���� ����� �ε����� ���� ���� �ְ�, ���� ��� ���� ũ�ٸ�
	// ū ���� ���� ��尡 �� ���̴�.
	
	// ���� ����� �ε����� ���� ���� �ְ�, ���� ��� ���� �۴ٸ�
	// ���� ���� ������ ��尡 �� ���̴�.
	
	// ���� ��尡 ���� ũ�ٸ� �ƹ��͵� �Ұ� ����(���� ��ġ�� ã�� �ʿ䰡 ����).

	// �׷��� �ʴٸ�?
	// ���� ū ���� ���� ���� ��ȯ
	// ��������� ū ��(�ε���) �� ���Ͽ� findLocation ����.
	
}

void heapify(int lastidx) { // Max Heap ���·� ����.
	/*
		���� �ڽ� �ε��� : ROOT �ε��� * 2
		������ �ڽ� �ε��� : ���� �ڽ� �ε��� + 1

		�ڽ��� �ִ� ������ ���(�ε����� 1���� ū ������ ���)���� �ٲ㳪��. (������ ����� �θ� ���)
	*/
}

int removeRoot(int lastidx) { // ��Ʈ�� ��ȯ.
	// ��Ʈ�� ��ȯ�� �غ�.
	// ������ ���� ��Ʈ�� �켱 �ø���, ��Ʈ���� ������ �ε����� ���� ������ �� ��ġ�� ã���� �Ѵ�.
	return 0;
}

void addToHeap(int v, int lastidx) {
	// �������� ���ο� �� �߰�
	int cur_idx = lastidx + 1;
	// �� ����� �θ� ������ �ٲ㳪��.
	int parent_idx = cur_idx / 2;

	data[cur_idx] = v;
	// �ݺ��ϸ�
	while (1) {
		// �ڽĺ��� �θ� ũ�� �Ϸ�.
		if (data[cur_idx] < data[parent_idx]) {
			return;
		}
		else {
			// �ƴϸ� �θ� ���� ���� ��� ��ȯ�ϰ� �θ��带 ������ �ø�
			swap(data, parent_idx, cur_idx);
			cur_idx = parent_idx;
			parent_idx = cur_idx / 2;
			// �� ���� �ø�.
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
	printf("���� ��Ʈ : %d\n", data[1]);
	addToHeap(30, 7);
	printf("���� ��Ʈ : %d\n", data[1]);
	addToHeap(40, 8);
	printf("���� ��Ʈ : %d\n", data[1]);
	addToHeap(20, 9);
	printf("���� ��Ʈ : %d\n", data[1]);
	int k = removeRoot(9);
	printf("���� ��Ʈ : %d, ���� ��Ʈ : %d\n", k, data[1]);

	k = removeRoot(8);
	printf("���� ��Ʈ : %d, ���� ��Ʈ : %d\n", k, data[1]);

	k = removeRoot(7);
	printf("���� ��Ʈ : %d, ���� ��Ʈ : %d\n", k, data[1]);

	k = removeRoot(6);
	printf("���� ��Ʈ : %d, ���� ��Ʈ : %d\n", k, data[1]);
	

	getchar();
	return 0;
}