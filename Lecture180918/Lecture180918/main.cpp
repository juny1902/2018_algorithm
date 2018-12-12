#include <stdio.h>
#include <stdlib.h>

// Graph 이론

// 범용성이 매우 높음.

// SLL,DLL 등도 그래프.
// 가계도, 조직도 등도 그래프.

// Vertex(Node)와 Edge 로 구성.

/*
	Graph의 종류
	- Edge의 종류에 따라 : 방향이 있는가 없는가 ? (Undirected graph, Directed graph, Weighted Graph)
	응용분야 - 지하철 노선도 구현

	Edge 에 가중치가 붙을 수 있음.

	예제 : 5개의 도시에 다리를 건설할때 특정 비용이 발생한다. (그림 그릴것)

	Minimum Spanning Tree : 모든 Vertex 들이 연결이 될 때 최소 비용은 ?
	ㄴ 최소 비용의 다리 우선 체크.
	ㄴ 두번째로 저렴한 비용의 다리 체크.
	ㄴ 이미 다리가 놓여있는 섬은 목적지로 고려하지 않음.


*/
// Graph 를 어떻게 나타내는가 ? 

// 1. 행렬로
// 단점, Vertex 에 비해 Edge가 적으면 공간 낭비가 매우 심함.
//	A와 연결된 Vertex 는 무엇이 있을까?
//	A->D 까지 가는 경로를 어떻게 찾을까?
#define N_VERTEX 4
int graph[N_VERTEX][N_VERTEX];

int char2num(char _c) {
	return _c - 'A';
}
int num2char(int _d) {
	return _d + 'A';
}
void showConnectedVertexes(int graph[N_VERTEX][N_VERTEX], char _v) {
	int idx_vertex = char2num(_v);
	int j;
	printf("Vertex %c 는 ", _v);
	for (j = 0; j < N_VERTEX; j++) {
		if (graph[idx_vertex][j] == 1) { // 특정 행의 어떤 열이 1인지 살펴보면 된다. 
			printf("%c ", num2char(j));
		}
	}
	printf("와 연결되어 있습니다.\n");
}
void findAllConnections(int graph[N_VERTEX][N_VERTEX]) {
	int i, j;
	for (i = 0; i < N_VERTEX; i++) {
		for (j = 0; j < N_VERTEX; j++) {
			if (graph[i][j] == 1) {
				printf("%c와 %c 는 연결되어 있습니다.\n", num2char(i), num2char(j));
			}
		}
	}
}

// 전역변수는 0으로 초기화 됨.
// Edge 가 있는곳에만 True 표시.
void addEdge(int graph[N_VERTEX][N_VERTEX], char p_A, char p_B) {
	int idx_A = char2num(p_A);
	int idx_B = char2num(p_B);
	graph[idx_A][idx_B] = 1;
	graph[idx_B][idx_A] = 1;
}

int main() {
	addEdge(graph, 'A', 'B'); // graph[0][1] = 1; graph[1][0] = 1;
	addEdge(graph, 'B', 'D');
	addEdge(graph, 'A', 'C');
	addEdge(graph, 'C', 'D');
	showConnectedVertexes(graph, 'A');
	showConnectedVertexes(graph, 'B');
	showConnectedVertexes(graph, 'C');
	showConnectedVertexes(graph, 'D');
	printf("...........\n");
	findAllConnections(graph);
	return 0;
}