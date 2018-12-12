#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_SLL {
	int v; // ����� Vertex �� �ǹ��Ѵ�.
	NODE_SLL *NEXT;
}NODE_SLL;

NODE_SLL *make_node(int _v);
void addToSLL(NODE_SLL **src, int dst);
void printSLL(NODE_SLL *NODE);