#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LETTER {
	char v;
	int freq;
	LETTER *NEXT;
	LETTER *LEFT;
	LETTER *RIGHT;
}LETTER;

LETTER **HEAP;
LETTER *LETTERS;

/* 구현 전략

	* 노드는 TREE, SLL 모두 적용 가능한 범용 노드로 만들어야 한다.
	1. 파일의 모든 문자의 개수를 센 뒤 노드로 만들어 SLL로 구성.
	2. Freq 에 따라 HEAP으로 재구성.
	3. HEAP 에서 2개씩 가져와 (작은 노드 2개) 트리로 구성.
	4. 그 트리를 다시 HEAP에 넣는다. (같은 구조체 공유)
	5. 3-4 의 과정을 반복하여 최종적으로 만들어지는 트리가 Huffman Tree.
	6. Huffman Tree 의 끝 노드 (양쪽 자식이 없는) 가 바로 코딩될 대상.
	7. Inorder Traversal 을 수행하며 좌,우측 노드 방문할 때마다 0 또는 1을 스택에 push. (빠져나올땐 pop)
	8. 코딩될 대상 노드에서 STACK 을 거꾸로 읽으면 그것이 해당 문자의 코딩결과.


*/

LETTER *make_node(char v) {
	LETTER *NEW = (LETTER *)malloc(sizeof(LETTER));
	NEW->v = v;
	NEW->freq = 1;
	NEW->NEXT = 0;
	NEW->LEFT = 0;
	NEW->RIGHT = 0;
	return NEW;
}

short countLetters() {
	LETTER *CUR = LETTERS;
	int cnt = 0;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}

int isWordExist(char v) {
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		if (CUR->v == v) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}

LETTER *findWordNode(char v) {
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		if (CUR->v == v) return CUR;
		CUR = CUR->NEXT;
	}
	return 0;
}

void addWord(char v) {
	if (isWordExist(v)) {
		(findWordNode(v)->freq)++;
		return;
	}

	LETTER *NEW = make_node(v);

	if (LETTERS == 0) {
		LETTERS = NEW;
	}
	else {
		LETTER *CUR = LETTERS;
		while (CUR->NEXT != 0 != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}

void countWholeCharInStr(char *str) {
	int n = strlen(str);
	for (int i = 0; i < n; i++) {
		addWord(str[i]);
	}
}

void printCharFreqs() {
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		printf("%c : %d\n", CUR->v, CUR->freq);
		CUR = CUR->NEXT;
	}
}

LETTER *createTree(LETTER *v1, LETTER *v2) {
	LETTER *TMP = (LETTER *)malloc(sizeof(LETTER));
	TMP->v = 0;
	TMP->freq = (v1->freq + v2->freq);
	TMP->LEFT = v1;
	TMP->RIGHT = v2;
	return TMP;
}
int lastHeapIdx = 0;
void addToHeap(LETTER *CUR) {
	lastHeapIdx++;
	HEAP[lastHeapIdx] = CUR;

	int me = lastHeapIdx;
	int parent = (me >> 1);

	while (1) {
		if (parent < 1 || HEAP[me]->freq > HEAP[parent]->freq) {
			return;
		}
		LETTER *tmp = HEAP[parent];
		HEAP[parent] = HEAP[me];
		HEAP[me] = tmp;

		me = parent;
		parent = (me >> 1);
	}

}
void buildHeap() {
	short cnt = countLetters();
	HEAP = (LETTER **)calloc(cnt+1, sizeof(LETTER *));
	LETTER *CUR = LETTERS;
	for (int i = 0; i < cnt; i++) {
		addToHeap(CUR);
		CUR = CUR->NEXT;
	}
}

int getSmallerIdx(int idx) {
	int left_child = idx * 2;
	int right_child = left_child + 1;

	if (right_child > lastHeapIdx) return left_child;
	if (HEAP[right_child]->freq > HEAP[left_child]->freq) return left_child;
	else return right_child;
}
void printHeap() {
	short cnt = countLetters();
	for (int i = 0; i < cnt; i++) {
		if(HEAP[i] != 0)
			printf("(%c-%d) - ", HEAP[i]->v, HEAP[i]->freq);
	}
	printf("\n");
}
LETTER *deleteFromHeap() {
	if (lastHeapIdx < 1) return 0;
	LETTER *ret = HEAP[1];

	HEAP[1] = HEAP[lastHeapIdx];
	HEAP[lastHeapIdx] = 0;
	lastHeapIdx--;

	int me = 1;

	while (1) {

		int left_child = me * 2;
		int right_child = left_child + 1;

		if (left_child > lastHeapIdx) break;

		int smaller_idx = getSmallerIdx(me);
		if (HEAP[me]->freq < HEAP[smaller_idx]->freq) break;
		else {
			LETTER *tmp = HEAP[me];
			HEAP[me] = HEAP[smaller_idx];
			HEAP[smaller_idx] = tmp;

			me = smaller_idx;
		}


	}
	return ret;
}
LETTER *buildHuffmanTree() {
	buildHeap();
	while (1) {
		/* SLL 구현
			deleteFromHeap() - SLL 에서 가장 작은 freq를 갖는 노드를 찾아 노드의 연결을 끊고 그 노드를 반환한다.
			두 노드를 삭제하고 반환받아 이를 트리로 만들어 다시 SLL에 넣는 것을 반복한다.
		*/

		/* HEAP 구현
			addToHeap(LETTER *NODE) - NODE 의 freq에 따라 HEAP 에 추가한다.
			deleteFromHeap() - 가장 작은 (가장 위의 노드) 를 삭제하고 반환한다.
			createTree(LETTER *v1, LETTER *v2) - 두 노드를 하나의 트리로 연결한다.
			두 노드를 삭제하고 반환받아 이를 트리로 만들어 다시 힙에 넣는 것을 반복한다.
		*/
		LETTER *FIRST = deleteFromHeap();
		LETTER *SECOND = deleteFromHeap();
		if (SECOND == NULL) return FIRST;
		LETTER *TMP = createTree(FIRST, SECOND); // 두 작은 Freq에 대한 Tree를 만든다.
		addToHeap(TMP); // 만들어진 트리를다시 Heap에 넣는다.
	}
}
typedef struct NODE { // for stack
	int v;
	NODE *NEXT;
	NODE *PREV;
}NODE;
NODE *STACK;

void push(int v) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->v = v;
	NEW->NEXT = STACK;
	NEW->PREV = 0;
	if(STACK != 0 )STACK->PREV = NEW;
	STACK = NEW;
}

int pop() {
	if (STACK == 0) {
		return -999;
	}
	else {
		NODE *TMP = STACK;
		int ret = STACK->v;
		STACK = STACK->NEXT;
		
		if(STACK != 0) STACK->PREV = 0;
		free(TMP);
		return ret;
	}
}
NODE *findStackEnd() {
	NODE *CUR = STACK;
	while (CUR->NEXT != 0) {
		CUR = CUR->NEXT;
	}
	return CUR;
}
int getStackLength() {
	int cnt = 0;
	NODE *CUR = STACK;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}
void writeStack(FILE **fp) {
	NODE *CUR = findStackEnd();
	while (CUR != 0) {
		fwrite(&(CUR->v), 1, 1, *fp);
		printf("%d", CUR->v);
		CUR = CUR->PREV;
	}

}
// Stack 사용
void inorder_Traversal(LETTER *HEAD, FILE *fp) {
	if (HEAD == 0) {
		pop();
		return;
	};
	push(0);
	inorder_Traversal(HEAD->LEFT,fp);
	if (HEAD->LEFT == 0 && HEAD->RIGHT == 0) { // 양쪽 자식이 없는 노드는 어떻게 코드 되었는가? (가장 끝 노드)
		printf("%c\t%d\t", HEAD->v, HEAD->freq);
		
		short size = getStackLength();

		fwrite(&(HEAD->v), 1, 1, fp);
		fwrite(&size, sizeof(short), 1, fp);
		writeStack(&fp);

		printf("\n");

		
	}
	push(1);
	inorder_Traversal(HEAD->RIGHT,fp);
	pop();
}

void showHuffmanTree(LETTER *HEAD,FILE *fp) {
	inorder_Traversal(HEAD,fp);
}

int main() {

	FILE *fp = fopen("alice.txt", "rt");

	if (fp == 0) {
		printf("Load Failed !\n");
		return 0;

	}

	while (!feof(fp)) {
		char buf[100];
		fscanf(fp, "%s", buf);
		countWholeCharInStr(buf);
	}
	fclose(fp);

	LETTER *H_TREE = buildHuffmanTree();
	printf("-------- 허프만 트리 --------\n");
	printf("문자\t빈도\t코드\n");

	FILE *fp_out = fopen("alice.bin", "wb");
	short n_syms = countLetters();
	fwrite(&n_syms, sizeof(short), 1, fp_out);

	showHuffmanTree(H_TREE, fp_out);
	fclose(fp_out);
	return 0;
}