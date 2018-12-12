/*
	Graph 2번째 방법.
	SLL 로 그래프 구현하기
	왜 트리로 하지 않는가? : 복잡하고 Edge가 너무 많으면 복잡.

	Graph 2가지 방법의 장단점
	Edge 개수가 많다 : Matrix 가 효율적, SLL 노드 너무 많아짐.
	Edge 개수가 적다 : SLL이 효율적, Matrix 는 너무 공간 낭비.

	1차원 SLL 배열을 하나 만든다. 그리고 해당하는 셀의 뒤에 연결된 Vertex 를 이어 붙인다.
*/

#include "Graph.h"

const int NUM_VERTEX = 30;
int top = -1;
int *stack = (int *)malloc(sizeof(int)*NUM_VERTEX);
int *visited = (int *)malloc(sizeof(int)*NUM_VERTEX);
int isStackEmpty() {
	return top == -1 ? 1 : 0;
}
int isStackFull() {
	return top == NUM_VERTEX - 1 ? 1 : 0;
}
void push(int v) {
	if (isStackFull()) {
		return;
	}
	else {
		top++;
		stack[top] = v;
		return;
	}
}
int pop() {
	if (isStackEmpty()) {
		return -999;
	}
	else {
		int tmp = stack[top];
		top--;
		return tmp;
	}
}
int findNextVertex(NODE_SLL **graph, int v) {
	// v 와 연결된 Vertex중, 아직까지 방문하지 않은 Vertex를 반환.
	// 조건에 맞는 Vertex 가 없으면 -1 반환.
	NODE_SLL *CUR = graph[v];
	while (CUR != 0) {
		if (visited[CUR->v] == 0) {
			return CUR->v;
		}
		CUR = CUR->NEXT;
	}
	return -1;
}
void DFS(NODE_SLL **graph, char node) { // 깊게 먼저 가고 -> 곁다리 버텍스 반복
	// 1. 시작 Vertex를 Stack 에 넣는다.
	int v = node - 'A';
	printf("%c 방문\n", v + 'A');
	visited[v] = 1;
	push(v);
	// 2. v = stack.pop();
	while (isStackEmpty() == 0) {
		int next_vertex = -1;
		next_vertex = findNextVertex(graph,stack[top]);
		if (next_vertex == -1) {
			pop();
		}
		else {
			printf("%c 방문\n", next_vertex+'A');
			visited[next_vertex] = 1;
			push(next_vertex);
		}
	}
	// 3. v 가 visited 가 아니면 추가한다.
	// 4. v에 연결된 vertex를 push 한다. (방문한것은 Push할 필요 없음).
	// 5. 2번으로 돌아간다.
}
void BFS(NODE_SLL **graph) { // 넓게 먼저 가고 -> 각 버텍스에 대하여 깊게 나감. 
	// 1. 시작 Vertex를 Queue 에 넣는다.
	// 2. v = queue.deque();
	// 3. v 가 visited 가 아니면 추가한다.
	// 4. v에 연결된 vertex를 enqueue 한다. (방문한것은 enqueue할 필요 없음).
	// 5. 2번으로 돌아간다.
}



int main() {
	NODE_SLL **graph = make_graph(6);
	addEdge(graph, 'A', 'B', 1);
	addEdge(graph, 'A', 'C', 1);
	addEdge(graph, 'B', 'D', 1);
	addEdge(graph, 'B', 'E', 1);
	addEdge(graph, 'A', 'D', 1);
	addEdge(graph, 'D', 'E', 1);
	addEdge(graph, 'E', 'G', 1);
	addEdge(graph, 'C', 'G', 1);
	DFS(graph, 'B');
	return 0;
}