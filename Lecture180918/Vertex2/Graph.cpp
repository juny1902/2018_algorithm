#include "Graph.h"
// Graph 관련 코드
NODE_SLL **make_graph(int N) // N 개의 Vertex 를 가질 수 있는 그래프를 생성.
{
	// 실제론 N개의 요소를 갖는 1차원 NODE_SLL 배열을 생성하는 것.

	// NODE_SLL **NEW = (NODE_SLL **)malloc(sizeof(NODE_SLL *)*N);
	// NEW = { 0, };
	
	NODE_SLL **NEW = (NODE_SLL **)calloc(N, sizeof(NODE_SLL)); // 공간을 할당 받은 뒤
	return NEW; // 해당 그래프 반환.
}

void addEdge(NODE_SLL **graph, char v_1, char v_2, int do_reverse) { // graph 에서 Vertex v_1 과 v_2 를 잇는 Edge를 추가한다.
																	 // Vertex v_1 과 v_2 가 양쪽으로 연결되어있음을 명시하기 위해
	addToSLL(&graph[v_1 - 'A'], v_2-'A'); // v_1 과 v_2 를 연결하는 Edge를 만든다.
									  // 실제론 SLL배열의 인덱스 v_1 에 v_2 의 값을 갖는 노드를 이어 붙인다.
	if (do_reverse == 1) {
		addToSLL(&graph[v_2 - 'A'], v_1-'A'); // v_2 와 v_1 을 연결하는 Edge를 만든다.
										  // 실제론 SLL배열의 인덱스 v_2 에 v_1 의 값을 갖는 노드를 이어 붙인다.
	}
}
void connectedEdge(NODE_SLL **graph, char _v) { // Vertex _v 와 연결된 모든 Vertex를 출력한다.
	printf("Vertex %c 와 연결된 것들은 ...\n", _v);
	printSLL(graph[_v - 'A']); // SLL graph[_v-'A']의 내용물을 출력한다. 
}