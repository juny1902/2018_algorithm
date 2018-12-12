#include <stdio.h>
#include <stdlib.h>

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

typedef struct Dijkstra {
	int found;
	int distance;
	char vertex;
	char prev;
}Dijkstra;

EDGE *EDGES = 0;
VERTEX *VERTEXES = 0;
Dijkstra *dtable = 0;

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

int isVertexInSLL(char v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}

void addVertex(char v) {
	if (isVertexInSLL(v)) return;
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

void addEdge(char v1, char v2, int weight) {
	addVertex(v1);
	addVertex(v2);

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
	EDGE *NEW = make_edge_node(0, v2->v, weight);
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
		VERTEX *v1 = findVertex(EDGE_TMP->v1);
		VERTEX *v2 = findVertex(EDGE_TMP->v2);

		addEdgeInfo(v1, v2, EDGE_TMP->weight);
		addEdgeInfo(v2, v1, EDGE_TMP->weight);

		EDGE_TMP = EDGE_TMP->NEXT;
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
	int n_v = countVertexes();

	dtable = (Dijkstra *)malloc(sizeof(Dijkstra)*n_v);

	VERTEX *CUR = VERTEXES;
	for (int i = 0; i < n_v; i++) {
		dtable[i].vertex = CUR->v;
		CUR = CUR->NEXT;
		dtable[i].found = 0;
		dtable[i].distance = 200000000;
		dtable[i].prev = 0;
	}
}

int findVertexIndexFromDTable(char v) {
	int vcnt = countVertexes();
	for (int i = 0; i < vcnt; i++) {
		if (dtable[i].vertex == v) {
			return i;
		}
	}
	return 0;
}

int nextShortestVertex() {
	int n = countVertexes();
	int shortestDist = 200000000;
	int shortestIdx = -1;
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
	int s_idx = findVertexIndexFromDTable(startVertex);
	dtable[s_idx].distance = 0;
	while (1) {
		int i = nextShortestVertex();
		if (i == -1) return;
		dtable[i].found = 1;

		EDGE *connectedOnes = findVertex(dtable[i].vertex)->CONNECTED;

		while (connectedOnes != 0) {
			int neighborIdx = findVertexIndexFromDTable(connectedOnes->v2);
			if (dtable[neighborIdx].distance > dtable[i].distance + connectedOnes->weight) {
				dtable[neighborIdx].distance = dtable[i].distance + connectedOnes->weight;
				dtable[neighborIdx].prev = dtable[i].vertex;
			}
			connectedOnes = connectedOnes->NEXT;
		}
	}
}

int main() {
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