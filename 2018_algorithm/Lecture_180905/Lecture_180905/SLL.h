#include <stdio.h>
#include <stdlib.h>

typedef struct SLL_NODE {
	int i;
	SLL_NODE *NEXT;
}SLL_NODE;

SLL_NODE *make_node(int v);
void add(int v, SLL_NODE **HEAD);
void remove(int v, SLL_NODE **HEAD);
void insert(int w, int v, SLL_NODE **HEAD);
void destroy(SLL_NODE **HEAD);
void traversal(SLL_NODE **HEAD);
