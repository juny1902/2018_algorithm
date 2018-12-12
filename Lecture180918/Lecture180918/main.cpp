#include <stdio.h>
#include <stdlib.h>

// Graph �̷�

// ���뼺�� �ſ� ����.

// SLL,DLL � �׷���.
// ���赵, ������ � �׷���.

// Vertex(Node)�� Edge �� ����.

/*
	Graph�� ����
	- Edge�� ������ ���� : ������ �ִ°� ���°� ? (Undirected graph, Directed graph, Weighted Graph)
	����о� - ����ö �뼱�� ����

	Edge �� ����ġ�� ���� �� ����.

	���� : 5���� ���ÿ� �ٸ��� �Ǽ��Ҷ� Ư�� ����� �߻��Ѵ�. (�׸� �׸���)

	Minimum Spanning Tree : ��� Vertex ���� ������ �� �� �ּ� ����� ?
	�� �ּ� ����� �ٸ� �켱 üũ.
	�� �ι�°�� ������ ����� �ٸ� üũ.
	�� �̹� �ٸ��� �����ִ� ���� �������� ������� ����.


*/
// Graph �� ��� ��Ÿ���°� ? 

// 1. ��ķ�
// ����, Vertex �� ���� Edge�� ������ ���� ���� �ſ� ����.
//	A�� ����� Vertex �� ������ ������?
//	A->D ���� ���� ��θ� ��� ã����?
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
	printf("Vertex %c �� ", _v);
	for (j = 0; j < N_VERTEX; j++) {
		if (graph[idx_vertex][j] == 1) { // Ư�� ���� � ���� 1���� ���캸�� �ȴ�. 
			printf("%c ", num2char(j));
		}
	}
	printf("�� ����Ǿ� �ֽ��ϴ�.\n");
}
void findAllConnections(int graph[N_VERTEX][N_VERTEX]) {
	int i, j;
	for (i = 0; i < N_VERTEX; i++) {
		for (j = 0; j < N_VERTEX; j++) {
			if (graph[i][j] == 1) {
				printf("%c�� %c �� ����Ǿ� �ֽ��ϴ�.\n", num2char(i), num2char(j));
			}
		}
	}
}

// ���������� 0���� �ʱ�ȭ ��.
// Edge �� �ִ°����� True ǥ��.
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