#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
	char c;
	char *code;
	NODE *NEXT;

}NODE;
NODE *HEAD = 0;

void addHuffCode(char c, const char* code) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->NEXT = 0;
	NEW->c = c;
	NEW->code = (char *)malloc(strlen(code) + 1);
	strcpy(NEW->code, code);

	if (HEAD == 0) {
		HEAD = NEW;
		return;
	}
	else {
		NODE *CUR = HEAD;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}
char getNumChar() {
	char cnt = 0;
	NODE *CUR = HEAD;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}
void writeByte(FILE *fp) {
	NODE *CUR = HEAD;
	while (CUR != 0) {
		fwrite(&(CUR->c), sizeof(char), 1, fp);
		char code_length = (char)strlen(CUR->code);
		fwrite(&code_length, 1, 1, fp);
		for (int i = 0; i < code_length; i++) {
			char v;
			if (CUR->code[i] == '0') {
				v = 0;
			}
			else {
				v = 1;
			}
			fwrite(&v, 1, 1, fp);
		}
		CUR = CUR->NEXT;
	}
}

// 허프만 트리 만들기
typedef struct H_NODE {
	char c;
	H_NODE *LEFT;
	H_NODE *RIGHT;
}H_NODE;

H_NODE *ROOT;

H_NODE *make_huff_node(char c) {
	H_NODE *NEW = (H_NODE *)malloc(sizeof(H_NODE));
	NEW->c = c;
	NEW->LEFT = NEW->RIGHT = 0;
	return NEW;
}

void inorderTraversal(H_NODE *ROOT) {
	if (ROOT == 0)return;
	inorderTraversal(ROOT->LEFT);
	printf("Char : %d\n", ROOT->c);
	inorderTraversal(ROOT->RIGHT);
}

char *make_char_array(const char *msg) {
	char *out = (char *)malloc(strlen(msg));
	strcpy(out, msg);
	return out;
}

char *codeTable[4];

int main(void) {
	FILE *fp = fopen("alice.bit", "rb");
	if (fp == 0) return 0;

	// 몇 비트를 읽어야 하는가?
	int n_bits = 0;
	fread(&n_bits, sizeof(int), 1, fp);
	printf("Bits to read : %d\n", n_bits);
	
	while (1) {
		char bitBuffer = 0;
		int bitMask = 0x80;
		
		int n = fread(&bitBuffer, sizeof(char), 1, fp);
		if (n <= 0) break; // 더 읽을 파일이 없으면 끝.

		while(1){
			if ((bitBuffer & bitMask) == 0) {
				printf("0");
			}
			else {
				printf("1");
			}
			n_bits--;
			
			bitBuffer <<= 1;
			if (bitBuffer == 0 || n_bits <= 0) {
				break;
			}
			/*
				bitMask = (bitMask >> 1) & 0x7F; // 산술 쉬프트이므로 오른쪽 Shift 에 Sign bit 유지. 따라서 부호와 관련 없는 왼쪽 Shift 사용.
				if (bitMask == 0 || n_bits <= 0) {
					bitMask = 0x80;
					break;
				}
			*/
		}
	}

	return 0;
}

int main_encode(void) {
	char *strToWrite = make_char_array("abbccdccbba");
	codeTable[0] = make_char_array("100");
	codeTable[1] = make_char_array("11");
	codeTable[2] = make_char_array("101");
	codeTable[3] = make_char_array("0");

	FILE *fp = fopen("alice.bit", "wb");
	char byteBuffer = 0;
	int shl_cnt = 7;
	int n_bits = 0;
	fseek(fp, sizeof(int), SEEK_SET); // fseek(stream,offset,origin) : 
	for (int i = 0; i < strlen(strToWrite); i++) {
		char c = strToWrite[i];
		char *code = codeTable[c - 'a'];

		for (int j = 0; j < strlen(code); j++) {
			char bitValue = 0;
			if (code[j] == '1') {
				bitValue = 1;
				bitValue = (bitValue << shl_cnt);
			}
			byteBuffer |= bitValue;
			shl_cnt--;
			n_bits++;
			if (shl_cnt < 0) {
				fwrite(&byteBuffer, sizeof(char), 1, fp);
				shl_cnt = 7;
				byteBuffer = 0;
			}
		}
	}
	if(shl_cnt < 7) fwrite(&byteBuffer, sizeof(char), 1, fp);
	fseek(fp, 0, SEEK_SET);
	fwrite(&n_bits, sizeof(int), 1, fp);
	printf("Wrote %d bits !\n", n_bits);
	return 0;
}

int main_recover() {
	FILE *fp = fopen("alice.encoded", "rb");
	// encode된 파일을 읽어서 허프만 트리를 복구.
	char num;
	// 1. 알파벳 개수 파악
	fread(&num, sizeof(char), 1, fp);
	printf("#. of alphabets : %d\n", num);

	ROOT = make_huff_node(0);

	// 2. 각 알파벳을 복구하여 허프만 트리 복구.
	for (int i = 0; i < num; i++) {
		char c;
		fread(&c, sizeof(char), 1, fp); // 문자 읽음
		char code_length;
		fread(&code_length, sizeof(char), 1, fp); // 코드 길이 읽음

		H_NODE *CUR = ROOT;
		for (int j = 0; j < code_length; j++) {

			char v;
			fread(&v, sizeof(char), 1, fp); // 코드의 각 비트 읽음.

			if (v == 0) {
				if (CUR->LEFT == 0) {
					CUR->LEFT = make_huff_node(0); // 왼쪽 가야하는데 막혀있으면 왼쪽 만듬.
				}
				else {
					CUR = CUR->LEFT; // 있으면 타고 내려감.
				}
			}
			else if (v == 1) {
				if (CUR->RIGHT == 0) {
					CUR->RIGHT = make_huff_node(1); // 오른쪽 가야하는데 막혀있으면 오른쪽 만듬.
				}
				else {
					CUR = CUR->RIGHT; // 있으면 타고 내려감.
				}
			}
			CUR->c = c; // 트리가 구축되면 마지막 도착지에 내 문자 추가.

		}
	}

	fclose(fp);

	return 0;
}

int main_encode_1() {
	addHuffCode('a', "0");
	addHuffCode('b', "10");
	addHuffCode('c', "11");

	// 허프만 코드를 파일에 쓰자

	FILE *fp = fopen("alice.encoded", "wb");
	if (fp == 0) return 0;

	// 1단계. 총 몇 개의 알파벳인지를 1바이트로 기록
	char n_char = getNumChar();
	fwrite(&n_char, sizeof(char), 1, fp);
	// 2단계. 각 알파벳을, '알파벳' + '길이' + '코드' 로 기록
	writeByte(fp);
	// 2단계 반복.

	inorderTraversal(ROOT);

	fclose(fp);
	return 0;
}