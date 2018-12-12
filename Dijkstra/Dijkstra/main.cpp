#include <stdio.h>
#include <stdlib.h>

// Pseudo Code
// 1. Dijkstra 테이블을 초기화한다. (found = false, dist = inf, prev = '0')
// 2. 시작 Vertex s 에 대하여 table[s].dist = 0 으로 둔다.
// 3.1 table[i].found == false && minimum(table[i].distance) 를 만족하는 Vertex 를 찾는다.
// 3.2 table[i].found = True 로 만든다.
// 4. Vertex[i] 의 Neighbor Vertex 들에 대해서 dist와 prev를 update (자신을 통해 더 빠르게 갈수 있는 경우) 한다.
// 5. 더 이상 Found == False 인 Vertex 가 없을 때 까지 3번으로 돌아가며 반복한다.

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

typedef struct Dijkstra { // Vertex의 수만큼 만들기.
	int found;
	int distance;
	char vertex; // vertex 에 해당하는 Table 임을 명시.
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

int isVertexInSLL(char v) { // SLL에 이미 Vertex v가 있으면 1, 아니면 0 반환.
	VERTEX *CUR = VERTEXES;
	while (CUR != 0) { // VERTEXES 가 애초에 NULL 이라면 while 들어갈 필요도 없이 while 다음로 넘어간다.
		if (CUR->v == v) return 1; // SLL 순회중 같은 Vertex가 있으면 1을 반환한다.
		CUR = CUR->NEXT;
	}
	return 0;
}



void addVertex(char v) {
	// <<<- 이 위치에 NODE를 미리 할당받으면 아까움 ! (아래에서 어차피 걸러지기 때문에)
	if (isVertexInSLL(v)) return; // 이미 Vertex가 있다면 추가하지 않는다.
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

void addEdge(char v1, char v2, int weight) { // 들어오는 Edge 정보를 저장하는 일만 한다.
	addVertex(v1); // Vertex SLL 에 v1 이 없으면 추가한다.
	addVertex(v2); // Vertex SLL 에 v2 가 없으면 추가한다.

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
	EDGE *NEW = make_edge_node(0, v2->v, weight); // edge 의 v1은 사용 안함.
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
		// Edge 를 하나씩 뒤져가면서, Graph 정보를 얻는다.
		VERTEX *v1 = findVertex(EDGE_TMP->v1);
		VERTEX *v2 = findVertex(EDGE_TMP->v2);
	
		addEdgeInfo(v1, v2, EDGE_TMP->weight);
		addEdgeInfo(v2, v1, EDGE_TMP->weight);
		// EDGE_TMP.v1 --> EDGE_TMP.v2 : 이 edge를 하나 넣고,
		// EDGE_TMP.v2 --> EDGE_TMP.v1 : 이 edge도 하나 넣는다.

		EDGE_TMP = EDGE_TMP->NEXT;
	}
}

void printEdges() { // 디버깅용
	printf("---- Edge 목록 ----\n");
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
	// Vertex 의 수를 센다.
	int n_v = countVertexes();
	// Vertex 수 만큼의 인덱스를 갖는 table을 생성.
	dtable = (Dijkstra *)malloc(sizeof(Dijkstra)*n_v);
	// 초기화
	VERTEX *CUR = VERTEXES;
	for (int i = 0; i < n_v; i++) {
		dtable[i].vertex = CUR->v; // Vertex 에 해당하는 Table임을 명시.
		CUR = CUR->NEXT;
		dtable[i].found = 0;
		dtable[i].distance = 200000000;
		dtable[i].prev = 0;
	}
}
// Vertex v에 해당하는 DTable 의 인덱스를 반환한다.
int findVertexIndexFromDTable(char v) {
	int vcnt = countVertexes();
	for (int i = 0; i < vcnt; i++) {
		if (dtable[i].vertex == v) {
			return i;
		}
	}
	return 0;
}

// 아직까지 최단경로가 결정되지 않았고, 최소 Dist를 가진 Vertex 의 dtable index 를 반환한다.
// 만일, 그런 vertex가 없으면, -1을 반환한다.
int nextShortestVertex() {
	int n = countVertexes();
	int shortestDist = 200000000; // 가장 큰 값
	int shortestIdx = -1; // 초기값은 비정상 값. (다 돌아도 못찾은 경우)
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
	// 시작 Vertex s 에 대해서 table[s].dist = 0 으로 만든다.
	int s_idx = findVertexIndexFromDTable(startVertex);
	dtable[s_idx].distance = 0;
	while (1) {
		int i = nextShortestVertex();
		if (i == -1) return; // 더이상 최단거리 찾을것이 없으므로 종료.
		dtable[i].found = 1; // 최단거리를 찾았음.
		
		// Vertex[i] 의 Neighbor vertex들에 대하여 dist와 prev를 update
		EDGE *connectedOnes = findVertex(dtable[i].vertex)->CONNECTED;

		while (connectedOnes != 0) {
			int neighborIdx = findVertexIndexFromDTable(connectedOnes->v2);
			if (dtable[neighborIdx].distance > dtable[i].distance + connectedOnes->weight) {
				// 나를 통해 가는 거리(거리 + 연결VertexWeight)보다 이웃 Vertex 통해 가는 길이 더 짧다면?
				dtable[neighborIdx].distance = dtable[i].distance + connectedOnes->weight;
				// 더 짧은 길을 선택하도록 함.
				dtable[neighborIdx].prev = dtable[i].vertex;
				// 더 짧은 길을 통하는 것을 본다.
			}
			connectedOnes = connectedOnes->NEXT;

		}
	}

	
	
}

int main() {

	// Edge 가 몇개 들어올지 모른다.
	// Edge 가 그만 들어올 때 까지 저장해둠
	// 저장해둔 Edge 정보를 토대로 Vertex 정보 생성
	// 이를 토대로 그래프 생성.
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