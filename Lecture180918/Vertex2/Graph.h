#pragma once
#include "SLL.h"

NODE_SLL **make_graph(int N);
void addEdge(NODE_SLL **graph, char v_1, char v_2, int do_reverse);
void connectedEdge(NODE_SLL **graph, char _v);