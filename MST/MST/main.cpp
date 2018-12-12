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

EDGE *EDGES;
VERTEX *VERTEXES;

EDGE *make_EDGE_node(char src, char dst, int weight) {
	EDGE *NEW = (EDGE *)malloc(sizeof(EDGE));
	NEW->src = src;
	NEW->dst = dst;
	NEW->weight = weight;
	NEW->NEXT = 0;
	return NEW;
}

VERTEX *make_VERTEX_node(char v, char family) {
	VERTEX *NEW = (VERTEX *)malloc(sizeof(VERTEX));
	NEW->v = v;
	NEW->family = family;
	NEW->NEXT = 0;
	return NEW;
}
int countEdge() {
	int cnt = 0;
	EDGE *CUR = EDGES;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}
void addEdge(char src, char dst, int weight) {
	EDGE *NEW = make_EDGE_node(src, dst, weight);
	if (EDGES == 0) {
		EDGES = NEW;
	}
	else {
		EDGE *CUR = EDGES;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
int isThereVertex(char v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}
int countVertex() {
	int cnt = 0;
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}
void addVertex(char v, char family) {
	if (isThereVertex(v)) return;
	VERTEX *NEW = make_VERTEX_node(v, family);
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
char findFamily(char v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return CUR->family;
		CUR = CUR->NEXT;
	}
	return 0;
}
int AreTheyFamily(char v1, char v2) {
	if (findFamily(v1) == findFamily(v2)) {
		return 1;
	}
	else {
		return 0;
	}
}
void justMarried(char v1, char v2) {
	char family = findFamily(v2);
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v1) CUR->family = family;
		if (CUR->v == v2) CUR->family = family;
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

	int n_edge = countEdge();
	
	EDGE *edgeArray = (EDGE *)malloc(sizeof(EDGE)*n_edge);

	int i, j;

	EDGE *CUR = EDGES;
	for (i = 0; i < n_edge; i++) {
		edgeArray[i].src = CUR->src;
		edgeArray[i].dst = CUR->dst;
		edgeArray[i].weight = CUR->weight;
		CUR = CUR->NEXT;
	}

	for (i = 0; i < n_edge; i++) {
		for (j = 0; j < n_edge - i - 1; j++) {
			if (edgeArray[j].weight > edgeArray[j + 1].weight) {
				EDGE TMP = edgeArray[j];
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = TMP;
			}
		}
	}

	for (i = 0; i < n_edge; i++) {
		addVertex(edgeArray[i].src, edgeArray[i].src);
		addVertex(edgeArray[i].dst, edgeArray[i].dst);
	}

	int mstCNT = 0;
	int weightSum = 0;
	for (i = 0; i < n_edge; i++) {
		if (AreTheyFamily(edgeArray[i].src, edgeArray[i].dst) == 0) {
			printf("%c - %c edge connected [weight = %d]\n", edgeArray[i].src, edgeArray[i].dst,edgeArray[i].weight);
			weightSum += edgeArray[i].weight;
			mstCNT++;
			if (mstCNT == countVertex() - 1) break;
			justMarried(edgeArray[i].src, edgeArray[i].dst);
		}
	}
	printf("--- Total Cost : %d\n", weightSum);
	return 0;
}