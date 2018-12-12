#include <stdio.h>
#include <stdlib.h>

typedef struct EDGE {
	char src;
	char dst;
	int weight;
	EDGE *NEXT;
}EDGE;

typedef struct VERTEX {
	char v;
	char family;
	VERTEX *NEXT;
}VERTEX;

EDGE *EDGES = 0;
VERTEX *VERTEXES = 0;

EDGE *make_EDGE_node(char src, char dst, int weight) {
	EDGE *NEW = (EDGE *)malloc(sizeof(EDGE));
	NEW->NEXT = 0;
	NEW->src = src;
	NEW->dst = dst;
	NEW->weight = weight;
	return NEW;
}
VERTEX *make_VERTEX_node(char v, char family) {
	VERTEX *NEW = (VERTEX *)malloc(sizeof(VERTEX));
	NEW->NEXT = 0;
	NEW->v = v;
	NEW->family = family;
	return NEW;
}

// Edge ���� �Լ�

void addEdge(char src, char dst, int weight) {
	EDGE *NEW = make_EDGE_node(src, dst, weight);
	EDGE *CUR = EDGES;
	if (EDGES == 0) {
		EDGES = NEW;
		return;
	}
	else {
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
int countEdge(EDGE *EDGES) {
	int cnt = 0;
	EDGE *CUR = EDGES;
	while (CUR != 0) {
		cnt += 1;
		CUR = CUR->NEXT;
	}
	return cnt;
}

// Vertex ���� �Լ�
int checkVertex(char v);
void addVertex(char v, char family) {
	VERTEX *NEW = make_VERTEX_node(v, family);
	if (checkVertex(v) == 1) return;
	// Vertex �� �̹� ������ �߰����� ����.
	if (VERTEXES == 0) {
		VERTEXES = NEW;
		return;
	}
	else {
		VERTEX *CUR = VERTEXES;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
int checkVertex(char v) { 
	// Vertex v �� �ִ��� Ȯ��.
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}
int countVertex(VERTEX *VERTEXES) {
	int cnt = 0;
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		cnt += 1;
		CUR = CUR->NEXT;
	}
	return cnt;
}


// Family ���� �Լ�

char findFamily(char v) {
	// Vertex v �� ������ ã�� ��ȯ.
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return CUR->family;
		CUR = CUR->NEXT;
	}
	return 0;
}

int AreWeFamily(char v1, char v2) {
	// v1 �� v2 �� ���� �����̸� 1, �ƴϸ� 0
	char family_v1 = findFamily(v1);
	char family_v2 = findFamily(v2);
	if (family_v1 == family_v2) {
		return 1;
	}
	else {
		return 0;
	}

}
void justMarried(char v1, char v2) {
	// ���� ������ �Ǿ��⿡ Family �� ���� ��.
	VERTEX *CUR = VERTEXES;
	char family;
	if (v1 < v2) {
		family = findFamily(v2);
	}
	else {
		family = findFamily(v1);
	}
	
	while (CUR != 0) {
		if (CUR->v == v1) CUR->v = family;
		if (CUR->v == v2) CUR->v = family;
		CUR = CUR->NEXT;
	}
}

int main() {
	// Edge ���� �߰��Ѵ�.
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 5);
	addEdge('A', 'D', 3);
	addEdge('B', 'C', 7);
	addEdge('B', 'E', 13);
	addEdge('C', 'D', 4);
	addEdge('C', 'E', 20);
	addEdge('C', 'F', 80);
	addEdge('C', 'G', 17);
	addEdge('D', 'G', 2);
	addEdge('E', 'F', 15);

	// 1. Edge �� ������������ �����Ѵ�.
	// bubble sort�� Ȱ��
	int n = countEdge(EDGES); // EDGE ���� ����.

	// ������ �迭�� �����.
	EDGE *edgeArray = (EDGE *)malloc(sizeof(EDGE) * n);

	// SLL EDGES�� ��带 �ϳ��� �湮�Ͽ� �迭�� �����Ѵ�.
	EDGE *TEMP = EDGES;
	for (int i = 0; i < n; i++) {
		edgeArray[i].src = TEMP->src;
		edgeArray[i].dst = TEMP->dst;
		edgeArray[i].weight = TEMP->weight;
		TEMP = TEMP->NEXT;
	}

	// ����� �迭�� ���Ͽ� Bubble Sort �� �����Ͽ� ������������ �����.
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (edgeArray[j].weight > edgeArray[j + 1].weight) {
				EDGE TMP = edgeArray[j];
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = TMP;
			}
		}
	}
	
	// ���� ����
	printf("... �������� ���� ���� ...\n");
	for (i = 0; i < n; i++) {
		printf("[%c-%c] Weight : %d\n",
			edgeArray[i].src, edgeArray[i].dst, edgeArray[i].weight);
	}

	// 2. ���� ���̺��� �����.
	// �� Vertex�� ���� ���� ����(�̸�, ��)
	// �� �迭�� �����鼭 �ϳ��� ã�Ƴ���.
	for (int i = 0; i < n; i++) {
		// Vertex�� ���ο� SLL�� Vertexes�� �߰��Ѵ�.
		// �ߺ����� ���� Vertex�� �߰�.
		addVertex(edgeArray[i].src, edgeArray[i].src);
		addVertex(edgeArray[i].dst, edgeArray[i].dst);
	}

	// edge���� ������������ �ϳ��� �˻��ϸ鼭
	// MST�� �߰��� �� �ִ����� Ȯ��
	printf("\n... MST ���� ...\n");
	int MSTcnt = 0;
	for (int i = 0; i < n; i++) {
		// ���� �ٸ� �����̹Ƿ� MST�� �߰�.
		if (AreWeFamily(edgeArray[i].src, edgeArray[i].dst) == 0) {
			printf("Add edge %c - %c\n",edgeArray[i].src,edgeArray[i].dst);
			MSTcnt += 1;
			if (MSTcnt == (countVertex(VERTEXES) - 1)) break;
			justMarried(edgeArray[i].src, edgeArray[i].dst);
		}
	}


	return 0;
}