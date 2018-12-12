// 1주차 
// 데이터 구조 정주행

// 배열과 malloc 차이 ? 
// 배열 : 정적 할당 (프로그램 실행 전 미리 할당해 둠. 메모리 해제 불가.)
// malloc : 동적 할당 (malloc 부분에서 할당됨. 메모리 해제 가능.)

/*
Array 의 단점
- 낙장불입 : 한번 정하면 나중에 크기를 수정하기 어려움.
- 어떻게 해결? -> Linked List 등장.
Linked List 의 장점
- Array 의 단점 극복
Linked List 의 단점
- High Cost - (시간, 공간...)

*/
#include "SLL.h"
SLL_NODE *HEAD = 0;

int main() {
	
	add(10, &HEAD);
	add(4, &HEAD);
	add(87, &HEAD);
	add(6,&HEAD);
	add(58,&HEAD);
	traversal(&HEAD);
	
	getchar();
	return 0;
}