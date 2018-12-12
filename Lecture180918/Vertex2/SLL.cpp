#include "SLL.h"

NODE_SLL *make_node(int _v) // Vertex _v 와 연결된 Edge를 생성.
{
	NODE_SLL *NEW = (NODE_SLL *)malloc(sizeof(NODE_SLL)); // 공간을 할당 받은 뒤
	NEW->NEXT = 0; NEW->v = _v; // Edge 로 연결된 Vertex 가 _v 임을 저장.
	return NEW; // 해당 Edge 반환
}
// 구현에는 다양한 방법이 있을 수 있음.
void addToSLL(NODE_SLL **src, int dst) // 주어진 Vertex src 와 dst 를 연결하는 Edge를 생성한다.
{
	// 실제론 SLL 배열의 v1에 해당하는 인덱스에 v2 값을 갖는 노드를 추가하는 것.
	NODE_SLL *NEW = make_node(dst); // v2 와 연결될 새로운 Edge를 생성.
	if (*src == 0) { // Vertex v1 이 다른 Vertex 와 전혀 연결되어있지 않다면?
		*src = NEW; // Vertex v1 의 가장 앞단이 새로운 Edge로 시작. 
		return;
	}
	else { // 기존에 이미 Edge 가 존재한다면 ?
		NODE_SLL *CUR = *src;  // 해당 Vertex에 첫번째로 연결된 Vertex 부터 ...
		while (CUR->NEXT != 0) { // 이미 존재하는 Edge를 모두 지나
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW; // 맨 마지막에 새로운 Edge를 삽입.
		return;
	}
}

void printSLL(NODE_SLL *NODE) { // SLL의 모든 노드를 출력한다.
	NODE_SLL *CUR = NODE;
	while (CUR != 0) {
		printf("ㄴ %c 가 연결되어 있습니다.\n", CUR->v + 'A');
		CUR = CUR->NEXT;
	}
}