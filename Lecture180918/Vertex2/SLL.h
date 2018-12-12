#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_SLL {
	int v; // 연결된 Vertex 를 의미한다.
	NODE_SLL *NEXT;
}NODE_SLL;

NODE_SLL *make_node(int _v);
void addToSLL(NODE_SLL **src, int dst);
void printSLL(NODE_SLL *NODE);