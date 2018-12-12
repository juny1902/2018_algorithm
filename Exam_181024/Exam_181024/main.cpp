

// 201503120 박준영 알고리즘 중간고사
#include <stdio.h>
#include <stdlib.h>
#define INVALID_VALUE -459

typedef struct EDGE {
	int v1;
	int v2;
	int w;
	EDGE *NEXT;
}EDGE;

typedef struct VERTEX {
	int v;
	int family;
	EDGE *CONNECTED;
	VERTEX *NEXT;
}VERTEX;

typedef struct Dijkstra {
	int v;
	int found;
	int dist;
	int prev;
}Dijkstra;

typedef struct NODE {
	int v;
	NODE *NEXT;
	NODE *LEFT;
	NODE *RIGHT;
}NODE;

EDGE *EDGES;
VERTEX *VERTEXES;
Dijkstra *DTABLE;

NODE *STACK;
NODE *QUEUE;
NODE *VISITED;

NODE *make_node(int v) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->v = v;
	NEW->LEFT = 0;
	NEW->RIGHT = 0;
	NEW->NEXT = 0;
	return NEW;
}

EDGE *make_edge_node(int v1, int v2, int w) {
	EDGE *NEW = (EDGE *)malloc(sizeof(EDGE));
	NEW->v1 = v1;
	NEW->v2 = v2;
	NEW->w = w;
	NEW->NEXT = 0;
	return NEW;
}

VERTEX *make_vertex_node(int v, int family) {
	VERTEX *NEW = (VERTEX *)malloc(sizeof(VERTEX));
	NEW->v = v;
	NEW->family = family;
	NEW->NEXT = 0;
	NEW->CONNECTED = 0;
	return NEW;
}

void push(int v) {
	NODE *NEW = make_node(v);
	NEW->NEXT = STACK;
	STACK = NEW;
}

int pop() {
	if (STACK == 0) {
		return INVALID_VALUE;
	}
	else {
		NODE *TMP = STACK;
		int v = STACK->v;
		STACK = STACK->NEXT;
		free(TMP);
		return v;
	}
}

void enQueue(int v) {
	NODE *NEW = make_node(v);
	if (QUEUE == 0) {
		QUEUE = NEW;
	}
	else {
		NODE *CUR = QUEUE;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}

int deQueue() {
	if (QUEUE == 0) {
		return INVALID_VALUE;
	}
	else {
		NODE *TMP = QUEUE;
		int v = QUEUE->v;
		QUEUE = QUEUE->NEXT;
		free(TMP);
		return v;
	}
}

void addToVisited(int v) {
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

int checkVisited(int v) {
	NODE *CUR = VISITED;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		else if (v < CUR->v) CUR = CUR->LEFT;
		else CUR = CUR->RIGHT;
	}
	return 0;
}

VERTEX *findVertex(int v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return CUR;
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
int isThereVertex(int v) {
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}
void addVertex(int v, int family) {
	if (isThereVertex(v)) return;
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
void addEdge(int v1, int v2, int w) {
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
		DTABLE[i].dist = 2000000000;
		DTABLE[i].found = 0;
		DTABLE[i].prev = 0;
		DTABLE[i].v = CUR->v;
		CUR = CUR->NEXT;
	}
}
int findIndexFromDTABLE(int v) {
	int n = countVertex();
	for (int i = 0; i < n; i++) {
		if (DTABLE[i].v == v) return i;
	}
	return -1;
}
int findShortestIndexFromDTABLE() {
	int n = countVertex();

	int shortest = 200000000;
	int idx_shortest = -1;

	for (int i = 0; i < n; i++) {
		if (DTABLE[i].found == 0 && DTABLE[i].dist < shortest) {
			shortest = DTABLE[i].dist;
			idx_shortest = i;
		}
	}
	return idx_shortest;
}
void printDijkstra() {
	int n = countVertex();
	for (int i = 0; i < n; i++) {
		printf("%d %d %d %d\n", DTABLE[i].v, DTABLE[i].found, DTABLE[i].dist, DTABLE[i].prev);
	}
}
void runDijkstra(int start, int end) {
	int idx_start = findIndexFromDTABLE(start);
	DTABLE[idx_start].dist = 0;

	while (1) {
		int idx_shortest = findShortestIndexFromDTABLE();
		if (idx_shortest == -1) { 
			int idx_end = findIndexFromDTABLE(end);
			printDijkstra();
			printf("question4:%d\n", DTABLE[idx_end].dist); 
			return;
		}
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

void pushAdjacentVertexes(int v) {
	EDGE *CUR = findVertex(v)->CONNECTED;
	while (CUR != 0) {
		push(CUR->v2);
		CUR = CUR->NEXT;
	}
}

void enQueueAdjacentVertexes(int v) {
	EDGE *CUR = findVertex(v)->CONNECTED;
	while (CUR != 0) {
		enQueue(CUR->v2);
		CUR = CUR->NEXT;
	}
}

void doDFS(int v) {
	VISITED = 0;
	int visit_cnt = 0; // 방문 횟수 카운트를 위한 공간.
	push(v);
	while (1) {
		int x = pop();
		if (x == INVALID_VALUE) {
			printf("question1:%d\n", visit_cnt); // 종료시 출력
			return;
		}
		if (checkVisited(x)) continue;
		if (x != v) visit_cnt++; // 꺼낸 것이 시작 Vertex 가 아닌 경우에만 카운트 셈.
		printf("DFS visited %d\n", x);
		addToVisited(x);
		pushAdjacentVertexes(x);
	}
}

void doBFS(int v) {
	VISITED = 0;
	int sum = 0; // 방문 Vertex 합을 위한 공간.
	enQueue(v);
	while (1) {
		int x = deQueue();
		if (x == INVALID_VALUE) {
			printf("question2:%d\n", sum); // 종료시 출력
			return;
		}
		if (checkVisited(x)) continue;
		printf("BFS visited %d\n", x);
		addToVisited(x);
		if (x != v) sum += x; 
		// 꺼낸 것이 시작 Vertex 가 아닌 경우에만 Vertex 번호 누적.
		enQueueAdjacentVertexes(x);
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

int findFamily(int v) {
	return findVertex(v)->family;
}

int AreWeFamily(int v1, int v2) {
	return findFamily(v1) == findFamily(v2) ? 1 : 0;
}

void WeAreFamily(int v1, int v2) {
	char familyMark_v1 = findFamily(v1);
	char familyMark_v2 = findFamily(v2);

	char newFamilyMark;
	char toBeChanged;

	if (familyMark_v1 < familyMark_v2)
	{
		newFamilyMark = familyMark_v1;
		toBeChanged = familyMark_v2;
	}
	else
	{
		newFamilyMark = familyMark_v2;
		toBeChanged = familyMark_v1;
	}

	VERTEX *CUR = VERTEXES;
	while (CUR != 0) {
		if (CUR->family == toBeChanged) CUR->family = newFamilyMark;
		CUR = CUR->NEXT;
	}
}

void doMST() {
	int i, j;
	int n = countEdge();
	EDGE *edgeArray = (EDGE *)malloc(sizeof(EDGE)*n);

	EDGE *CUR = EDGES;
	for (i = 0; i < n; i++) {
		edgeArray[i].v1 = CUR->v1;
		edgeArray[i].v2 = CUR->v2;
		edgeArray[i].w = CUR->w;
		CUR = CUR->NEXT;
	}

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
	int w_sum = 0; // 가중치 합을 저장할 공간.

	for (i = 0; i < n; i++) {
		if (cntMST == countVertex() - 1) {
			printf("question3:%d\n", w_sum); // 탈출하기 전 답 출력
			return;
		}

		if (AreWeFamily(edgeArray[i].v1, edgeArray[i].v2) == 0) {
			cntMST++;
			printf("가중치 %d의 Edge %d 와 %d 를 연결.\n", edgeArray[i].w, edgeArray[i].v1, edgeArray[i].v2);
			w_sum += edgeArray[i].w; // MST가 생성될 때의 가중치의 합을 계산.
			WeAreFamily(edgeArray[i].v1, edgeArray[i].v2);
		}
	}
	
}

int main() {
	FILE *fp = fopen("D:\\data.txt", "rt");
	int input_mode = 1; // 입력 모드부터 시작.
	if (fp == 0) return 0;
	while (!feof(fp)) {
		if (input_mode) { // 입력 모드
			int v1_t = 0, v2_t = 0, w_t = 0;
			fscanf(fp, "%d %d %d\n", &v1_t, &v2_t, &w_t);

			if (v1_t == -1 && v2_t == -1 && w_t == -1) { 
				// 입력 종료와 함께
				processEdge(); // Edge 처리
				initDijkstraTable(); // 테이블 초기화
				input_mode = 0; // 입력모드 종료
				continue;
			}

			addEdge(v1_t, v2_t, w_t);
		}
		else { // 퀴즈 모드
			int arg1 = 0, arg2 = 0;
			printf("----------------\n");
			fscanf(fp, "%d\n", &arg1); 
			doDFS(arg1); // 문제 1
			printf("----------------\n");
			fscanf(fp, "%d\n", &arg1);
			doBFS(arg1); // 문제 2
			printf("----------------\n");
			fscanf(fp, "%d\n", &arg1);
			doMST();	 // 문제 3
			printf("----------------\n");
			fscanf(fp, "%d %d\n", &arg1, &arg2);
			runDijkstra(arg1, arg2);  // 문제 4 (Argument 2개)
			printf("----------------\n");
		}
	}
	fclose(fp);
	return 0;
}