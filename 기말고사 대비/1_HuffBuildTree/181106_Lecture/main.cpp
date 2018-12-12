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

/* ���� ����

	* ���� TREE, SLL ��� ���� ������ ���� ���� ������ �Ѵ�.
	1. ������ ��� ������ ������ �� �� ���� ����� SLL�� ����.
	2. Freq �� ���� HEAP���� �籸��.
	3. HEAP ���� 2���� ������ (���� ��� 2��) Ʈ���� ����.
	4. �� Ʈ���� �ٽ� HEAP�� �ִ´�. (���� ����ü ����)
	5. 3-4 �� ������ �ݺ��Ͽ� ���������� ��������� Ʈ���� Huffman Tree.
	6. Huffman Tree �� �� ��� (���� �ڽ��� ����) �� �ٷ� �ڵ��� ���.
	7. Inorder Traversal �� �����ϸ� ��,���� ��� �湮�� ������ 0 �Ǵ� 1�� ���ÿ� push. (�������ö� pop)
	8. �ڵ��� ��� ��忡�� STACK �� �Ųٷ� ������ �װ��� �ش� ������ �ڵ����.


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
		/* SLL ����
			deleteFromHeap() - SLL ���� ���� ���� freq�� ���� ��带 ã�� ����� ������ ���� �� ��带 ��ȯ�Ѵ�.
			�� ��带 �����ϰ� ��ȯ�޾� �̸� Ʈ���� ����� �ٽ� SLL�� �ִ� ���� �ݺ��Ѵ�.
		*/

		/* HEAP ����
			addToHeap(LETTER *NODE) - NODE �� freq�� ���� HEAP �� �߰��Ѵ�.
			deleteFromHeap() - ���� ���� (���� ���� ���) �� �����ϰ� ��ȯ�Ѵ�.
			createTree(LETTER *v1, LETTER *v2) - �� ��带 �ϳ��� Ʈ���� �����Ѵ�.
			�� ��带 �����ϰ� ��ȯ�޾� �̸� Ʈ���� ����� �ٽ� ���� �ִ� ���� �ݺ��Ѵ�.
		*/
		LETTER *FIRST = deleteFromHeap();
		LETTER *SECOND = deleteFromHeap();
		if (SECOND == NULL) return FIRST;
		LETTER *TMP = createTree(FIRST, SECOND); // �� ���� Freq�� ���� Tree�� �����.
		addToHeap(TMP); // ������� Ʈ�����ٽ� Heap�� �ִ´�.
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
// Stack ���
void inorder_Traversal(LETTER *HEAD, FILE *fp) {
	if (HEAD == 0) {
		pop();
		return;
	};
	push(0);
	inorder_Traversal(HEAD->LEFT,fp);
	if (HEAD->LEFT == 0 && HEAD->RIGHT == 0) { // ���� �ڽ��� ���� ���� ��� �ڵ� �Ǿ��°�? (���� �� ���)
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
	printf("-------- ������ Ʈ�� --------\n");
	printf("����\t��\t�ڵ�\n");

	FILE *fp_out = fopen("alice.bin", "wb");
	short n_syms = countLetters();
	fwrite(&n_syms, sizeof(short), 1, fp_out);

	showHuffmanTree(H_TREE, fp_out);
	fclose(fp_out);
	return 0;
}