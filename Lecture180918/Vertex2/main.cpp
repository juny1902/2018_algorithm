/*
	Graph 2��° ���.
	SLL �� �׷��� �����ϱ�
	�� Ʈ���� ���� �ʴ°�? : �����ϰ� Edge�� �ʹ� ������ ����.

	Graph 2���� ����� �����
	Edge ������ ���� : Matrix �� ȿ����, SLL ��� �ʹ� ������.
	Edge ������ ���� : SLL�� ȿ����, Matrix �� �ʹ� ���� ����.

	1���� SLL �迭�� �ϳ� �����. �׸��� �ش��ϴ� ���� �ڿ� ����� Vertex �� �̾� ���δ�.
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
	// v �� ����� Vertex��, �������� �湮���� ���� Vertex�� ��ȯ.
	// ���ǿ� �´� Vertex �� ������ -1 ��ȯ.
	NODE_SLL *CUR = graph[v];
	while (CUR != 0) {
		if (visited[CUR->v] == 0) {
			return CUR->v;
		}
		CUR = CUR->NEXT;
	}
	return -1;
}
void DFS(NODE_SLL **graph, char node) { // ��� ���� ���� -> ��ٸ� ���ؽ� �ݺ�
	// 1. ���� Vertex�� Stack �� �ִ´�.
	int v = node - 'A';
	printf("%c �湮\n", v + 'A');
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
			printf("%c �湮\n", next_vertex+'A');
			visited[next_vertex] = 1;
			push(next_vertex);
		}
	}
	// 3. v �� visited �� �ƴϸ� �߰��Ѵ�.
	// 4. v�� ����� vertex�� push �Ѵ�. (�湮�Ѱ��� Push�� �ʿ� ����).
	// 5. 2������ ���ư���.
}
void BFS(NODE_SLL **graph) { // �а� ���� ���� -> �� ���ؽ��� ���Ͽ� ��� ����. 
	// 1. ���� Vertex�� Queue �� �ִ´�.
	// 2. v = queue.deque();
	// 3. v �� visited �� �ƴϸ� �߰��Ѵ�.
	// 4. v�� ����� vertex�� enqueue �Ѵ�. (�湮�Ѱ��� enqueue�� �ʿ� ����).
	// 5. 2������ ���ư���.
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