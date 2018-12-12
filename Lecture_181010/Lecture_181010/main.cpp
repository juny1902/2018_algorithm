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

// Edge 관련 함수

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

// Vertex 관련 함수
int checkVertex(char v);
void addVertex(char v, char family) {
	VERTEX *NEW = make_VERTEX_node(v, family);
	if (checkVertex(v) == 1) return;
	// Vertex 가 이미 있으면 추가하지 않음.
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
	// Vertex v 가 있는지 확인.
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


// Family 관련 함수

char findFamily(char v) {
	// Vertex v 의 가족을 찾아 반환.
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return CUR->family;
		CUR = CUR->NEXT;
	}
	return 0;
}

int AreWeFamily(char v1, char v2) {
	// v1 과 v2 가 같은 가족이면 1, 아니면 0
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
	// 같은 가족이 되었기에 Family 를 같게 함.
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
	// Edge 들을 추가한다.
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

	// 1. Edge 를 오름차순으로 정렬한다.
	// bubble sort를 활용
	int n = countEdge(EDGES); // EDGE 수를 구함.

	// 복사할 배열을 만든다.
	EDGE *edgeArray = (EDGE *)malloc(sizeof(EDGE) * n);

	// SLL EDGES의 노드를 하나씩 방문하여 배열에 복사한다.
	EDGE *TEMP = EDGES;
	for (int i = 0; i < n; i++) {
		edgeArray[i].src = TEMP->src;
		edgeArray[i].dst = TEMP->dst;
		edgeArray[i].weight = TEMP->weight;
		TEMP = TEMP->NEXT;
	}

	// 복사된 배열에 대하여 Bubble Sort 를 수행하여 오름차순으로 만든다.
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
	
	// 정렬 점검
	printf("... 오름차순 정렬 점검 ...\n");
	for (i = 0; i < n; i++) {
		printf("[%c-%c] Weight : %d\n",
			edgeArray[i].src, edgeArray[i].dst, edgeArray[i].weight);
	}

	// 2. 가족 테이블을 만든다.
	// ㄴ Vertex에 대한 정보 부족(이름, 수)
	// ㄴ 배열을 뒤지면서 하나씩 찾아낸다.
	for (int i = 0; i < n; i++) {
		// Vertex를 새로운 SLL인 Vertexes에 추가한다.
		// 중복되지 않은 Vertex만 추가.
		addVertex(edgeArray[i].src, edgeArray[i].src);
		addVertex(edgeArray[i].dst, edgeArray[i].dst);
	}

	// edge들을 오름차순으로 하나씩 검사하면서
	// MST에 추가할 수 있는지를 확인
	printf("\n... MST 수행 ...\n");
	int MSTcnt = 0;
	for (int i = 0; i < n; i++) {
		// 서로 다른 가족이므로 MST에 추가.
		if (AreWeFamily(edgeArray[i].src, edgeArray[i].dst) == 0) {
			printf("Add edge %c - %c\n",edgeArray[i].src,edgeArray[i].dst);
			MSTcnt += 1;
			if (MSTcnt == (countVertex(VERTEXES) - 1)) break;
			justMarried(edgeArray[i].src, edgeArray[i].dst);
		}
	}


	return 0;
}