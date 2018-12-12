#include "SLL.h"

SLL_NODE *make_node(int v) {
	SLL_NODE *NEW = (SLL_NODE *)malloc(sizeof(SLL_NODE));
	NEW->i = v; NEW->NEXT = 0;
	return NEW;
}
void add(int v, SLL_NODE **HEAD) {
	SLL_NODE *NEW = make_node(v);
	if (*HEAD == 0) {
		*HEAD = NEW;
		return;
	}
	else {
		SLL_NODE *LAST = *HEAD;
		while (LAST->NEXT != 0) {
			LAST = LAST->NEXT;
		}
		LAST->NEXT = NEW;
		return;
	}
}
void remove(int v, SLL_NODE **HEAD) {

}
void insert(int w, int v, SLL_NODE **HEAD) {

}
void destroy(SLL_NODE **HEAD) {

}
void traversal(SLL_NODE **HEAD) {
	SLL_NODE *CUR = *HEAD;
	while (CUR != 0) {
		printf("%d\n", CUR->i);
		CUR = CUR->NEXT;
	}
}