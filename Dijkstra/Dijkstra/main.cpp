#include <stdio.h>
#include <stdlib.h>

// Pseudo Code
// 1. Dijkstra ���̺��� �ʱ�ȭ�Ѵ�. (found = false, dist = inf, prev = '0')
// 2. ���� Vertex s �� ���Ͽ� table[s].dist = 0 ���� �д�.
// 3.1 table[i].found == false && minimum(table[i].distance) �� �����ϴ� Vertex �� ã�´�.
// 3.2 table[i].found = True �� �����.
// 4. Vertex[i] �� Neighbor Vertex �鿡 ���ؼ� dist�� prev�� update (�ڽ��� ���� �� ������ ���� �ִ� ���) �Ѵ�.
// 5. �� �̻� Found == False �� Vertex �� ���� �� ���� 3������ ���ư��� �ݺ��Ѵ�.

typedef struct EDGE {
	char v1;
	char v2;
	int weight;
	EDGE *NEXT;
}EDGE;

typedef struct VERTEX {
	char v;
	VERTEX *NEXT;
	EDGE *CONNECTED;
}VERTEX;

typedef struct Dijkstra { // Vertex�� ����ŭ �����.
	int found;
	int distance;
	char vertex; // vertex �� �ش��ϴ� Table ���� ���.
	char prev;
}Dijkstra;

Dijkstra *dtable = 0;
EDGE *EDGES = 0;
VERTEX *VERTEXES = 0;

EDGE *make_edge_node(char v1, char v2, int weight) {
	EDGE *NEW = (EDGE *)malloc(sizeof(EDGE));
	NEW->v1 = v1;
	NEW->v2 = v2;
	NEW->weight = weight;
	NEW->NEXT = 0;
	return NEW;
}
VERTEX *make_vertex_node(char v) {
	VERTEX *NEW = (VERTEX *)malloc(sizeof(VERTEX));
	NEW->v = v;
	NEW->CONNECTED = 0;
	NEW->NEXT = 0;
	return NEW;
}

int isVertexInSLL(char v) { // SLL�� �̹� Vertex v�� ������ 1, �ƴϸ� 0 ��ȯ.
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) { // VERTEXES �� ���ʿ� NULL �̶�� while �� �ʿ䵵 ���� while ������ �Ѿ��.
		if (CUR->v == v) return 1; // SLL ��ȸ�� ���� Vertex�� ������ 1�� ��ȯ�Ѵ�.
		CUR = CUR->NEXT;
	}
	return 0;
}



void addVertex(char v) {
	// <<<- �� ��ġ�� NODE�� �̸� �Ҵ������ �Ʊ�� ! (�Ʒ����� ������ �ɷ����� ������)
	if (isVertexInSLL(v)) return; // �̹� Vertex�� �ִٸ� �߰����� �ʴ´�.
	VERTEX *NEW = make_vertex_node(v); 
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
		return;
	}
}

void addEdge(char v1, char v2, int weight) { // ������ Edge ������ �����ϴ� �ϸ� �Ѵ�.
	addVertex(v1); // Vertex SLL �� v1 �� ������ �߰��Ѵ�.
	addVertex(v2); // Vertex SLL �� v2 �� ������ �߰��Ѵ�.

	EDGE *NEW = make_edge_node(v1, v2, weight);
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
void addEdgeInfo(VERTEX *v1, VERTEX *v2, int weight) {
	EDGE *NEW = make_edge_node(0, v2->v, weight); // edge �� v1�� ��� ����.
	EDGE *CUR = v1->CONNECTED;

	if (CUR == 0) {
		v1->CONNECTED = NEW;
	}
	else {
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
VERTEX *findVertex(char v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return CUR;
		CUR = CUR->NEXT;
	}
}
void processEdges() {
	EDGE *EDGE_TMP = EDGES;
	while (EDGE_TMP != 0) {
		// Edge �� �ϳ��� �������鼭, Graph ������ ��´�.
		VERTEX *v1 = findVertex(EDGE_TMP->v1);
		VERTEX *v2 = findVertex(EDGE_TMP->v2);
	
		addEdgeInfo(v1, v2, EDGE_TMP->weight);
		addEdgeInfo(v2, v1, EDGE_TMP->weight);
		// EDGE_TMP.v1 --> EDGE_TMP.v2 : �� edge�� �ϳ� �ְ�,
		// EDGE_TMP.v2 --> EDGE_TMP.v1 : �� edge�� �ϳ� �ִ´�.

		EDGE_TMP = EDGE_TMP->NEXT;
	}
}

void printEdges() { // ������
	printf("---- Edge ��� ----\n");
	EDGE *CUR = EDGES;
	while (CUR != 0) {
		printf("%c\t%c\t%d\n", CUR->v1, CUR->v2, CUR->weight);
		CUR = CUR->NEXT;
	}
}
int countVertexes() {
	int cnt = 0; 
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}
void initDijkstraTable() {
	// Vertex �� ���� ����.
	int n_v = countVertexes();
	// Vertex �� ��ŭ�� �ε����� ���� table�� ����.
	dtable = (Dijkstra *)malloc(sizeof(Dijkstra)*n_v);
	// �ʱ�ȭ
	VERTEX *CUR = VERTEXES;
	for (int i = 0; i < n_v; i++) {
		dtable[i].vertex = CUR->v; // Vertex �� �ش��ϴ� Table���� ���.
		CUR = CUR->NEXT;
		dtable[i].found = 0;
		dtable[i].distance = 200000000;
		dtable[i].prev = 0;
	}
}
// Vertex v�� �ش��ϴ� DTable �� �ε����� ��ȯ�Ѵ�.
int findVertexIndexFromDTable(char v) {
	int vcnt = countVertexes();
	for (int i = 0; i < vcnt; i++) {
		if (dtable[i].vertex == v) {
			return i;
		}
	}
	return 0;
}

// �������� �ִܰ�ΰ� �������� �ʾҰ�, �ּ� Dist�� ���� Vertex �� dtable index �� ��ȯ�Ѵ�.
// ����, �׷� vertex�� ������, -1�� ��ȯ�Ѵ�.
int nextShortestVertex() {
	int n = countVertexes();
	int shortestDist = 200000000; // ���� ū ��
	int shortestIdx = -1; // �ʱⰪ�� ������ ��. (�� ���Ƶ� ��ã�� ���)
	for (int i = 0; i < n; i++) {
		if (dtable[i].found == 0 &&
			dtable[i].distance < shortestDist) {
			shortestIdx = i;
			shortestDist = dtable[i].distance;
		}
	}
	return shortestIdx;
}

void runDijkstra(char startVertex) {
	// ���� Vertex s �� ���ؼ� table[s].dist = 0 ���� �����.
	int s_idx = findVertexIndexFromDTable(startVertex);
	dtable[s_idx].distance = 0;
	while (1) {
		int i = nextShortestVertex();
		if (i == -1) return; // ���̻� �ִܰŸ� ã������ �����Ƿ� ����.
		dtable[i].found = 1; // �ִܰŸ��� ã����.
		
		// Vertex[i] �� Neighbor vertex�鿡 ���Ͽ� dist�� prev�� update
		EDGE *connectedOnes = findVertex(dtable[i].vertex)->CONNECTED;

		while (connectedOnes != 0) {
			int neighborIdx = findVertexIndexFromDTable(connectedOnes->v2);
			if (dtable[neighborIdx].distance > dtable[i].distance + connectedOnes->weight) {
				// ���� ���� ���� �Ÿ�(�Ÿ� + ����VertexWeight)���� �̿� Vertex ���� ���� ���� �� ª�ٸ�?
				dtable[neighborIdx].distance = dtable[i].distance + connectedOnes->weight;
				// �� ª�� ���� �����ϵ��� ��.
				dtable[neighborIdx].prev = dtable[i].vertex;
				// �� ª�� ���� ���ϴ� ���� ����.
			}
			connectedOnes = connectedOnes->NEXT;

		}
	}

	
	
}

int main() {

	// Edge �� � ������ �𸥴�.
	// Edge �� �׸� ���� �� ���� �����ص�
	// �����ص� Edge ������ ���� Vertex ���� ����
	// �̸� ���� �׷��� ����.
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 2);
	addEdge('B', 'C', 4);
	addEdge('B', 'D', 5);
	addEdge('C', 'D', 40);
	
	processEdges();

	initDijkstraTable();
	
	runDijkstra('A');

	int c = countVertexes();
	for (int i = 0; i < c; i++) {
		printf("%c %d %d %c\n", dtable[i].vertex, dtable[i].found, dtable[i].distance, dtable[i].prev);
	}
	
}