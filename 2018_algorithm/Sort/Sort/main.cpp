#include <stdio.h>
int data[10] = { 1, 5, 3, 7, 8, 10, 2, 100, 99, 55 };

void printAll(int *data, int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}

void swap(int *data, int idx1, int idx2) {
	int tmp = data[idx1];
	data[idx1] = data[idx2];
	data[idx2] = tmp;
}

void bubbleSort(int *data, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 1 - i; j++) {
			if (data[j] > data[j + 1]) {
				swap(data, j, j + 1);
			}
		}
		printAll(data, size);
	}
}
int findSmallest(int *data, int start_idx, int size) {
	// start_idx ��� ���� �迭�� ���� ���� ����� �ε����� ��ȯ�Ѵ�.
	int smallest_idx = start_idx;
	int smallest = data[smallest_idx];

	for (int i = start_idx; i < size; i++) {
		if (data[i] < smallest) {
			smallest_idx = i;
			smallest = data[i];
			
		}
	}
	return smallest_idx;
}
void selectionSort(int *data, int size) {
	int i;
	// i���� ��Ҹ�ŭ �ݺ�
	for (i = 0; i < size; i++) {
		// i��° ��Һ��� ���� �迭���� ���� ���� ���� ã�´�.
		int smallest_idx = findSmallest(data, i, size);
		// ���� ���� ���� ���� ��ҿ� ��ȯ�Ѵ�.
		swap(data, smallest_idx, i);
		printAll(data, size);
	}
}

void insertionSort(int *data, int size) {
	int i;
	for (i = 1; i < size; i++) {
		int j = i;
		while ((j - 1) >= 0 && (data[j - 1] > data[j])) {
			swap(data, j - 1, j);
			j--;
		}
		printAll(data, size);
	}
}

int main() {
	selectionSort(data, 10);

	getchar();
	return 0;
}

