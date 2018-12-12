#include "Graph.h"
// Graph ���� �ڵ�
NODE_SLL **make_graph(int N) // N ���� Vertex �� ���� �� �ִ� �׷����� ����.
{
	// ������ N���� ��Ҹ� ���� 1���� NODE_SLL �迭�� �����ϴ� ��.

	// NODE_SLL **NEW = (NODE_SLL **)malloc(sizeof(NODE_SLL *)*N);
	// NEW = { 0, };
	
	NODE_SLL **NEW = (NODE_SLL **)calloc(N, sizeof(NODE_SLL)); // ������ �Ҵ� ���� ��
	return NEW; // �ش� �׷��� ��ȯ.
}

void addEdge(NODE_SLL **graph, char v_1, char v_2, int do_reverse) { // graph ���� Vertex v_1 �� v_2 �� �մ� Edge�� �߰��Ѵ�.
																	 // Vertex v_1 �� v_2 �� �������� ����Ǿ������� ����ϱ� ����
	addToSLL(&graph[v_1 - 'A'], v_2-'A'); // v_1 �� v_2 �� �����ϴ� Edge�� �����.
									  // ������ SLL�迭�� �ε��� v_1 �� v_2 �� ���� ���� ��带 �̾� ���δ�.
	if (do_reverse == 1) {
		addToSLL(&graph[v_2 - 'A'], v_1-'A'); // v_2 �� v_1 �� �����ϴ� Edge�� �����.
										  // ������ SLL�迭�� �ε��� v_2 �� v_1 �� ���� ���� ��带 �̾� ���δ�.
	}
}
void connectedEdge(NODE_SLL **graph, char _v) { // Vertex _v �� ����� ��� Vertex�� ����Ѵ�.
	printf("Vertex %c �� ����� �͵��� ...\n", _v);
	printSLL(graph[_v - 'A']); // SLL graph[_v-'A']�� ���빰�� ����Ѵ�. 
}