#include <stdio.h>
#include <stdlib.h>

#define SZ_GRAPH 6

//SLL과 BST 구현을 위한 범용 노드 생성
typedef struct NODE {
	char v;
	NODE *NEXT;
	NODE *LEFT;
	NODE *RIGHT;
}NODE;

NODE *QUEUE; // QUEUE 시작노드.

NODE **make_graph(int size) {
	NODE **NEW = (NODE **)calloc(size, sizeof(NODE));
	return NEW;
}
NODE *make_node(char v) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->NEXT = NEW->RIGHT = NEW->LEFT = 0;
	NEW->v = v;
	return NEW;
}
void add_edge_mini(NODE **GRAPH, char v1, char v2) {
	NODE *NEW = make_node(v2);

	if (GRAPH[v1 - 'A'] == 0) {
		GRAPH[v1 - 'A'] = NEW;
		return;
	}
	else {
		NODE *CUR = GRAPH[v1 - 'A'];
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
void add_edge(NODE **GRAPH, char v1, char v2) {
	add_edge_mini(GRAPH, v1, v2);
	add_edge_mini(GRAPH, v2, v1);
}
void push(NODE **STACK, char v) {
	NODE *NEW = make_node(v);
	NEW->NEXT = *STACK;
	*STACK = NEW;
}
char pop(NODE **STACK) {
	if (STACK == 0) {
		return '-';
	}
	else {
		NODE *TMP = *STACK;
		char v = (*STACK)->v;
		*STACK = (*STACK)->NEXT;
		free(TMP);
		return v;
	}
}
void enQueue(char v) {
	NODE *NEW = make_node(v);
	NODE *CUR = QUEUE;
	if (QUEUE == 0) {
		QUEUE = NEW;
	}
	else {
		while (CUR->NEXT != 0) {
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
		return v;
	}
}

void addToVisited(NODE **VISITED, char v) {
	NODE *NEW = make_node(v);

	if (*VISITED == 0) {
		*VISITED = NEW;
		return;
	}
	else {
		NODE *CUR = *VISITED;

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

int checkVisited(NODE *VISITED, char v) {
	NODE *CUR = VISITED;
	while (CUR != 0) {
		if (CUR->v == v) {
			return 1;
		}
		else if (v < CUR->v) {
			CUR = CUR->LEFT;
		}
		else {
			CUR = CUR->RIGHT;
		}
	}
	return 0;
}
void addAdjacentVertexes(NODE **GRAPH, NODE *VISITED, char v) {
	NODE *CUR = GRAPH[v - 'A'];
	while (CUR != 0) {
		if (checkVisited(VISITED, CUR->v) == 0) push(&VISITED, CUR->v);
		CUR = CUR->NEXT;
	}
}



void doDFS(NODE **GRAPH, char v) {
	NODE *VISITED = 0;
	NODE *STACK = 0;
	push(&STACK, v);
	while (1) {
		char x = pop(&STACK);
		if (x == '-') return;
		if (checkVisited(VISITED, x) == 1) continue;
		printf("%c 를 방문했습니다.\n", x);
		addToVisited(&VISITED, x);
		addAdjacentVertexes(GRAPH, VISITED, x);
	}
}


int main(void) {
	NODE **GRAPH = make_graph(6);
	add_edge(GRAPH, 'A', 'C');
	add_edge(GRAPH, 'C', 'B');
	add_edge(GRAPH, 'C', 'F');
	add_edge(GRAPH, 'B', 'E');
	add_edge(GRAPH, 'D', 'B');
	add_edge(GRAPH, 'D', 'F');
	doDFS(GRAPH,'A');
	//doBFS('A');
	return 0;

}