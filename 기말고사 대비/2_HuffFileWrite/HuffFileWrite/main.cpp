#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SZ_BUF 100

typedef struct LETTER {
	char v;
	int freq;
	LETTER *NEXT;
	LETTER *PREV;
	LETTER *LEFT;
	LETTER *RIGHT;
} LETTER;

LETTER **HEAP;
int heapend = 0;

LETTER *LETTERS;

LETTER *make_letter_node(char v) {
	LETTER *NEW = (LETTER *)malloc(sizeof(LETTER));
	NEW->v = v;
	NEW->freq = 1; // 글자가 추가되는 순간 첫 카운트는 1.
	NEW->LEFT = NEW->RIGHT = NEW->NEXT = NEW->PREV = 0;
	return NEW;
}

LETTER *findLetterNode(char v) {
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		if (CUR->v == v) {
			return CUR;
		}
		CUR = CUR->NEXT;
	}
	return 0;
}

int countLetterSLL() {
	int cnt = 0;
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}

void printLetterSLL() {
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		printf("%c - %d\n", CUR->v, CUR->freq);
		CUR = CUR->NEXT;
	}
}

int checkLetterExists(char v) {
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		if (CUR->v == v) {
			return 1;
		}
		CUR = CUR->NEXT;
	}
	return 0;


}
void addToLetter(char v) {
	if (checkLetterExists(v) == 1) {
		(findLetterNode(v)->freq)++;
		return;
	}

	LETTER *NEW = make_letter_node(v);

	if (LETTERS == 0) {
		LETTERS = NEW;
	}
	else {
		LETTER *CUR = LETTERS;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}

void getCharCountFromBuffer(char *buf) {
	int n = strlen(buf);
	for (int i = 0; i < n; i++) {
		addToLetter(buf[i]);
	}
}


void addToHeap(LETTER *CUR) {
	int n = countLetterSLL();
	if (heapend == n - 1) return;

	heapend++;
	HEAP[heapend] = CUR;

	int me = heapend;
	int parent = me / 2;

	while (1) {
		if (parent < 1 || HEAP[me]->freq > HEAP[parent]->freq) return;
		LETTER *TMP = HEAP[me];
		HEAP[me] = HEAP[parent];
		HEAP[parent] = TMP;

		me = parent;
		parent = me / 2;
	}
}

int getSmallerHeapIndex(int v) {
	int left = v * 2;
	int right = left + 1;
	if (right > heapend)return left;
	else if (HEAP[left]->freq < HEAP[right]->freq) return left;
	else {
		return right;
	}
}
void initHeap() {
	int n = countLetterSLL();
	HEAP = (LETTER **)calloc(n+1, sizeof(LETTER *));
	
	LETTER *CUR = LETTERS;
	while (CUR != 0) {
		addToHeap(CUR);
		CUR = CUR->NEXT;
	}
}

LETTER *deleteFromHeap() {
	if (heapend < 0) return 0;
	
	LETTER *ret = HEAP[1];
	HEAP[1] = HEAP[heapend];
	HEAP[heapend] = 0;
	heapend--;

	int me = 1;
	

	while (1) {
		int left = me * 2;
		int right = left + 1;

		if (left > heapend) break;

		int idx_smaller = getSmallerHeapIndex(me);
		if (HEAP[me]->freq < HEAP[idx_smaller]->freq) break;
		else {
			LETTER *TMP = HEAP[idx_smaller];
		HEAP[idx_smaller] = HEAP[me];
		HEAP[me] = TMP;

		me = idx_smaller;
		}
		
	}
	return ret;
}
LETTER *make_tree(LETTER *FIRST, LETTER *SECOND) {
	LETTER *NEW = make_letter_node(0);
	NEW->freq = FIRST->freq + SECOND->freq;
	NEW->LEFT = FIRST;
	NEW->RIGHT = SECOND;
	return NEW;
}

LETTER *make_huffman_tree() {
	initHeap();
	while (1) {
		LETTER *FIRST = deleteFromHeap();
		LETTER *SECOND = deleteFromHeap();
		if (SECOND == 0) return FIRST;
		LETTER *TREE = make_tree(FIRST, SECOND);
		addToHeap(TREE);
	}
}

LETTER *STACK;

void push(int v) {
	LETTER *NEW = make_letter_node(v);
	NEW->NEXT = STACK;
	if (STACK != 0) STACK->PREV = NEW;
	STACK = NEW;
}

int pop() {
	if (STACK == 0) {
		return 0;
	}
	else {
		LETTER *TMP = STACK;
		int ret = STACK->v;
		STACK = STACK->NEXT;
		free(TMP);
		if (STACK != 0) STACK->PREV = 0;
	}
}

LETTER *findStackBottom() {
	LETTER *CUR = STACK;
	while (CUR->NEXT != 0) {
		CUR = CUR->NEXT;
	}
	return CUR;
}

void readStackFromBottom() {
	LETTER *CUR = findStackBottom();
	int cnt = 0;
	while (CUR != 0) {
		cnt++;
		printf("%d", CUR->v);
		CUR = CUR->PREV;
	}
}

void showAllCodes(LETTER *HEAD) {
	if (HEAD == 0) {
		pop();
		return;
	}
	push(0);
	showAllCodes(HEAD->LEFT);
	if (HEAD->LEFT == 0 && HEAD->RIGHT == 0) {
		printf("%c\t%d\t", HEAD->v, HEAD->freq);
		readStackFromBottom();
		printf("\n");
	}
		
	push(1);
	showAllCodes(HEAD->RIGHT);
	pop();
}

void writeHuffmanBinary(FILE *stream) {
	LETTER *CUR = findStackBottom();
	char bin;
	while (CUR != 0) {
		bin = CUR->v;
		fwrite(&bin, sizeof(char), 1, stream);
		CUR = CUR->PREV;
	}
}
int getCodeLength() {
	LETTER *CUR = STACK;
	char cnt = 0;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}

void writeHTableToFile(LETTER *HEAD,FILE *stream) {
	if (HEAD == 0) {
		pop();
		return;
	}

	push(0);

	writeHTableToFile(HEAD->LEFT,stream);
	if (HEAD->LEFT == 0 && HEAD->RIGHT == 0) {
		char h_length = getCodeLength();
		
		fwrite(&(HEAD->v), 1, 1, stream);
		fwrite(&h_length, sizeof(char), 1, stream);
		printf("%c\t%d\t", HEAD->v, HEAD->freq);
		readStackFromBottom();
		printf("\t\t\n");
		writeHuffmanBinary(stream);
	}

	push(1);
	writeHTableToFile(HEAD->RIGHT, stream);
	pop();
}

int main() {
	FILE *f_in = fopen("D:/alice.txt", "rt");
	FILE *f_out = fopen("D:/alice.bin", "wb");

	while (!feof(f_in)) {
		char buf[SZ_BUF];
		fscanf(f_in, "%s", buf);
		getCharCountFromBuffer(buf);
	}

	LETTER *HTREE = make_huffman_tree();
	char n_sym = countLetterSLL();
	fwrite(&n_sym, 1, 1, f_out);
	writeHTableToFile(HTREE, f_out);
	fclose(f_in);
	fclose(f_out);

	return 0;
}