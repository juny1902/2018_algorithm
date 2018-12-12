#include <stdio.h>
#include <stdlib.h>

typedef struct EDGE {
	char v1;
	char v2;
	int w;
	EDGE *NEXT;
}EDGE;

typedef struct VERTEX {
	char v;
	char family;
	EDGE *CONNECTED;
	VERTEX *NEXT;
}VERTEX;

typedef struct Dijkstra {
	char v;
	int found;
	int dist;
	char prev;
}Dijkstra;

typedef struct NODE {
	char v;
	NODE *NEXT;
	NODE *RIGHT;
	NODE *LEFT;
}NODE;

NODE *STACK;
NODE *QUEUE;
NODE *VISITED;

NODE *make_node(char v) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->v = v;
	NEW->LEFT = 0;
	NEW->RIGHT = 0;
	NEW->NEXT = 0;
	return NEW;
}

void push(char v) {
	NODE *NEW = make_node(v);
	NEW->NEXT = STACK;
	STACK = NEW;
}

char pop() {
	if (STACK == 0) {
		return '-';
	}
	else {
		NODE *TMP = STACK;
		char v = STACK->v;
		STACK = STACK->NEXT;
		free(TMP);
		return v;
	}
}

void enQueue(char v) {
	NODE *NEW = make_node(v);
	if (QUEUE == 0) {
		QUEUE = NEW;
	}
	else {
		NODE *CUR = QUEUE;
		while(CUR->NEXT != 0){
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}

char deQueue() {
	if (QUEUE == 0) {
		return '-';
	}
	else {
		NODE *TMP = QUEUE;
		char v = QUEUE->v;
		QUEUE = QUEUE->NEXT;
		free(TMP);
		return v;
	}
}

void addToVisited(char v){
	NODE *NEW = make_node(v);
	if (VISITED == 0) {
		VISITED = NEW;
	}
	else {
		NODE *CUR = VISITED;
		while (CUR != 0) {
			if (v < CUR->v) {
				if (CUR->LEFT == 0) {
					CUR->LEFT = NEW;
					return;
				}
				else {
					CUR = CUR->LEFT;
				}
			}
			else {
				if (CUR->RIGHT == 0) {
					CUR->RIGHT = NEW;
					return;
				}
				else {
					CUR = CUR->RIGHT;
				}
			}
		}
	}
}
int checkVisited(char v) {
	NODE *CUR = VISITED;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		else if (v < CUR->v) CUR = CUR->LEFT;
		else CUR = CUR->RIGHT;
	}
	return 0;
}

EDGE *EDGES;
VERTEX *VERTEXES;
Dijkstra *DTABLE;

EDGE *make_edge_node(char v1, char v2, int w) {
	EDGE *NEW = (EDGE *)malloc(sizeof(EDGE));
	NEW->v1 = v1;
	NEW->v2 = v2;
	NEW->w = w;
	NEW->NEXT = 0;
	return NEW;
}

VERTEX *make_vertex_node(char v, char family) {
	VERTEX *NEW = (VERTEX *)malloc(sizeof(VERTEX));
	NEW->v = v;
	NEW->family = family;
	NEW->CONNECTED = 0;
	NEW->NEXT = 0;
	return NEW;
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
int isVertexThere(char v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}
VERTEX *findVertex(char v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) {
			return CUR;
		}
		CUR = CUR->NEXT;
	}
	return 0;
}
void addVertex(char v, char family) {
	if (isVertexThere(v)) return;
	VERTEX *NEW = make_vertex_node(v, family);
	if (VERTEXES == 0) {
		VERTEXES = NEW;
	}
	else {
		VERTEX *CUR = VERTEXES;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
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
void addEdge(char v1, char v2, int w) {
	addVertex(v1, v1);
	addVertex(v2, v2);
	EDGE *NEW = make_edge_node(v1, v2, w);
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
void addEdgeInfo(VERTEX *v1, VERTEX *v2, int w) {
	EDGE *NEW = make_edge_node(0, v2->v, w);
	if (v1->CONNECTED == 0) {
		v1->CONNECTED = NEW;
	}
	else {
		EDGE *CUR = v1->CONNECTED;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
void processEdge() {
	EDGE *CUR = EDGES;
	while (CUR != 0) {
		addEdgeInfo(findVertex(CUR->v1), findVertex(CUR->v2), CUR->w);
		addEdgeInfo(findVertex(CUR->v2), findVertex(CUR->v1), CUR->w);
		CUR = CUR->NEXT;
	}
}
void initDijkstraTable() {
	int n = countVertex();
	DTABLE = (Dijkstra *)malloc(sizeof(Dijkstra)*n);

	VERTEX *CUR = VERTEXES;

	for (int i = 0; i < n; i++) {
		DTABLE[i].v = CUR->v;
		DTABLE[i].found = 0;
		DTABLE[i].dist = 2000000000;
		DTABLE[i].prev = 0;
		CUR = CUR->NEXT;
	}
}
int findIndexFromDTABLE(char v) {
	int n = countVertex();
	for (int i = 0; i < n; i++) {
		if (DTABLE[i].v == v) return i;
	}
	return -1;
}
int findShortestIndexFromDTABLE() {
	int n = countVertex();
	int shortest = 2000000000;
	int idx_shortest = -1;
	for (int i = 0; i < n; i++) {
		if (DTABLE[i].found == 0 && DTABLE[i].dist < shortest) {
			shortest = DTABLE[i].dist;
			idx_shortest = i;
		}
	}
	return idx_shortest;

}
void runDijkstra(char start) {
	int idx_start = findIndexFromDTABLE(start);
	DTABLE[idx_start].dist = 0;

	int n = countVertex();

	for (int i = 0; i < n; i++) {
		int idx_shortest = findShortestIndexFromDTABLE();
		DTABLE[idx_shortest].found = 1;

		EDGE *NEIGHBOR = findVertex(DTABLE[idx_shortest].v)->CONNECTED;
		while (NEIGHBOR != 0) {
			int idx_neighbor = findIndexFromDTABLE(NEIGHBOR->v2);
			if (DTABLE[idx_neighbor].dist > DTABLE[idx_shortest].dist + NEIGHBOR->w) {
				DTABLE[idx_neighbor].dist = DTABLE[idx_shortest].dist + NEIGHBOR->w;
				DTABLE[idx_neighbor].prev = DTABLE[idx_shortest].v;
			}
			NEIGHBOR = NEIGHBOR->NEXT;
		}
	}
}
void printDijkstra() {
	int n = countVertex();
	for (int i = 0; i < n; i++) {
		printf("%c %d %d %c\n", DTABLE[i].v, DTABLE[i].found, DTABLE[i].dist, DTABLE[i].prev);
	}
}
char findFamily(char v) {
	return findVertex(v)->family;
}
int areWeFamily(char v1, char v2) {
	return findFamily(v1) == findFamily(v2) ? 1 : 0;
}
void weAreFamily(char v1, char v2) {
	char family = 0;
	if (v1 < v2) {
		family = findFamily(v2);
	}
	else {
		family = findFamily(v1);
	}
	findVertex(v1)->family = family;
	findVertex(v2)->family = family;
}
void pushAdjacentVertexes(char v) {
	EDGE *CUR = findVertex(v)->CONNECTED;
	while (CUR != 0) {
		push(CUR->v2);
		CUR = CUR->NEXT;
	}
}
void enQueueAdjacentVertexes(char v) {
	EDGE *CUR = findVertex(v)->CONNECTED;
	while (CUR != 0) {
		enQueue(CUR->v2);
		CUR = CUR->NEXT;
	}
}

void doDFS(char start) {
	VISITED = 0;
	push(start);
	while (1) {
		char x = pop();
		if (x == '-') return;
		if (checkVisited(x)) continue;
		printf("Visited vertex %c\n", x);
		addToVisited(x);
		pushAdjacentVertexes(x);
	}

}

void doBFS(char start) {
	VISITED = 0;
	enQueue(start);
	while (1) {
		char x = deQueue();
		if (x == '-') return;
		if (checkVisited(x)) continue;
		printf("Visited vertex %c\n", x);
		addToVisited(x);
		enQueueAdjacentVertexes(x);
	}
}
void findMST() {
	int n = countEdge();

	EDGE *edgeArray = (EDGE *)malloc(sizeof(EDGE)*n);

	EDGE *CUR = EDGES;

	for (int i = 0; i < n; i++) {
		edgeArray[i].v1 = CUR->v1;
		edgeArray[i].v2 = CUR->v2;
		edgeArray[i].w = CUR->w;
		CUR = CUR->NEXT;
	}

	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (edgeArray[j].w > edgeArray[j + 1].w) {
				EDGE TMP = edgeArray[j];
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = TMP;
			}
		}
	}

	int cntMST = 0;
	
	for (i = 0; i < n; i++) {
		if (cntMST == countVertex() - 1) return;
		if (areWeFamily(edgeArray[i].v1, edgeArray[i].v2) == 0) {
			printf("Add Edge %c - %c : %d\n", edgeArray[i].v1, edgeArray[i].v2,edgeArray[i].w);
			weAreFamily(edgeArray[i].v1, edgeArray[i].v2);
			cntMST++;
		}
	}
}


int main() {
	FILE *fp = fopen("D:\\djikstra.txt", "rt");

	if (fp == 0) {
		return 0;
	}

	while (!feof(fp)) {
		char v1_t = 0, v2_t = 0;
		int w_t = 0;

		fscanf(fp, "%c %c %d\n", &v1_t, &v2_t, &w_t);
		if (v1_t == 'Z' && v2_t == 'Z' && w_t == -1) break;

		addEdge(v1_t, v2_t, w_t);
	}
	processEdge();

	initDijkstraTable();

	runDijkstra('A');

	printDijkstra();

	findMST();

	doDFS('A');

	doBFS('A');

}