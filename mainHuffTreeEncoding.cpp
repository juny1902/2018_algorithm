#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	char c;
	char *code;
	struct node *next;
};
struct node *head = 0;

// 허프만 트리,,,
struct hnode
{
	char c;
	struct hnode *left;
	struct hnode *right;
};
struct hnode *root = 0;


void addHuffCode(char c, char* code)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->next = 0;
	new_one->c = c;
	new_one->code = (char *)malloc(strlen(code) + 1);
	strcpy(new_one->code, code);

	if (head == 0)
	{
		head = new_one;
		return;
	}
	struct node *temp = head;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
}

// 저장해야 할 알파벳의 개수를 알아낸다.
int getNumOfCodes()
{
	struct node *temp = head;
	int cnt = 0;

	while (temp != 0)
	{
		cnt++;
		temp = temp->next;
	}
	return cnt;

}

// 비트스트림 파일을 열어서, 파일 내용을 읽어내어
// 코드 스트링을 출력
int main(void)
{
	FILE *f = fopen("alice.bit", "rb");

	// 몇 비트를 읽어야 되는지를 결정,,,
	int numOfBits = 0;
	fread(&numOfBits, sizeof(int), 1, f);

	printf("읽을 비트 수: %d\n", numOfBits);

	char andMask = 0x80;

	while (1)
	{
		char readBuf;
		int n = fread(&readBuf, sizeof(char), 1, f);
		if (n <= 0)
		{
			break;
		}

		while (1)
		{
			if ((readBuf & andMask) == 0)
			{
				printf("0");
			}
			else
			{
				printf("1");
			}
			numOfBits -= 1;
			andMask = (andMask >> 1) & 0x7f;
			if (andMask == 0 || numOfBits <= 0)
			{
				andMask = 0x80;
				break;
			}
		}

	}

	fclose(f);

	return 0;
}




// a: 100
// b: 11
// c: 101
// d: 0
char *codeTable[4] = { "100", "11", "101", "0" };

int main92(void)
{
	char *strToWrite = "abbccdccbba";

	// 비트단위로 파일에 기록
	FILE *f = fopen("alice.bit", "wb");

	// 비트 개수를 기록할 공간 (4byte)을 비워둔다.
	fseek(f, 4, SEEK_SET);

	char oneByteBuffer = 0;  // 초기값은 0
	int shiftCnt = 7;
	int numOfBits = 0;

	for (int i = 0; i < strlen(strToWrite); i++)
	{
		char c = strToWrite[i];
		char *code = codeTable[c - 'a'];

		for (int j = 0; j < strlen(code); j++)
		{
			char bitValue = 0;
			if (code[j] == '1')
			{
				bitValue = 1;
				bitValue = bitValue << shiftCnt;
				oneByteBuffer = oneByteBuffer | bitValue;
			}
			shiftCnt -= 1;
			numOfBits += 1; // 기록된 비트 개수를 저장

			if (shiftCnt < 0)
			{
				fwrite(&oneByteBuffer, sizeof(char), 1, f);
				shiftCnt = 7;
				oneByteBuffer = 0;
			}
		}
	}
	if (shiftCnt < 7)
	{
		fwrite(&oneByteBuffer, sizeof(char), 1, f);
	}
	//
	// 파일의 맨 처음으로 돌아가서,
	// 비트의 개수를 기록한다.
	fseek(f, 0, SEEK_SET);
	fwrite(&numOfBits, sizeof(int), 1, f);

	fclose(f);
	return 0;
}



int main3333(void)
{
	FILE *f = fopen("alice.encoded", "rb");

	// encoded 파일을 읽어서 허프만 트리를 복구

	// 1 단계... 몇 개의 알파벳이 있는지 파악
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("There are %d alphabets\n", num);

	root = (struct hnode *)malloc(sizeof(struct hnode));
	root->left = root->right = 0;

	// 2 단계... 각 알파벳을 복수하여 허프만 코드를 줄력..
	for (int i = 0; i < num; i++)
	{
		struct hnode *temp = root;

		char c;
		fread(&c, sizeof(char), 1, f);

		char len;
		fread(&len, sizeof(char), 1, f);

		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, f);
			if (v == 0)
			{
				// 왼쪽 가야되는데,,
				if (temp->left == 0)
				{
					temp->left = (struct hnode *)malloc(sizeof(struct hnode));
					temp->left->left = temp->left->right = 0;
				}
				temp = temp->left;

			}
			else
			{
				// 오른쪽 가야되는데,,
				if (temp->right == 0)
				{
					temp->right = (struct hnode *)malloc(sizeof(struct hnode));
					temp->right->left = temp->right->right = 0;
				}
				temp = temp->right;
			}
		}
		temp->c = c;
	}
	fclose(f);
	return 0;
}


int main999(void)
{
	FILE *f = fopen("alice.encoded", "rb");

	// encoded 파일을 읽어서 허프만 트리를 복구

	// 1 단계... 몇 개의 알파벳이 있는지 파악
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("There are %d alphabets\n", num);

	// 2 단계... 각 알파벳을 복수하여 허프만 코드를 줄력..
	for (int i = 0; i < num; i++)
	{
		char c;
		fread(&c, sizeof(char), 1, f);
		printf("%c: ", c);

		char len;
		fread(&len, sizeof(char), 1, f);

		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, f);
			if (v == 0)
			{
				printf("0");
			}
			else
			{
				printf("1");
			}
		}
		printf("\n");
	}

	fclose(f);
	return 0;
}

int main1(void)
{
	addHuffCode('a', "0");
	addHuffCode('b', "10");
	addHuffCode('c', "11");

	// 허프만 코드를 파일에 써 봅시다.
	FILE *f = fopen("alice.encoded", "wb");

	// 1단계. 총 몇 개의 알파벳인지를 1바이트로 기록
	char numOfChars = (char)getNumOfCodes();
	fwrite(&numOfChars, sizeof(char), 1, f);

	// 2단계. 각 알파벳을, '알파벳' + '길이' + '코드'로 기록
	struct node *temp = head;
	while (temp != 0)
	{
		char c = temp->c;
		fwrite(&c, sizeof(char), 1, f);
		
		char len = (char)strlen(temp->code);
		fwrite(&len, sizeof(char), 1, f);

		for (int i = 0; i < len; i++)
		{
			char v;
			if (temp->code[i] == '0')
			{
				v = 0;
			}
			else
			{
				v = 1;
			}
			fwrite(&v, sizeof(char), 1, f);
		}
		temp = temp->next;
	}
	fclose(f);

	return 0;
}