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

// ������ Ʈ��,,,
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

// �����ؾ� �� ���ĺ��� ������ �˾Ƴ���.
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

// ��Ʈ��Ʈ�� ������ ���, ���� ������ �о��
// �ڵ� ��Ʈ���� ���
int main(void)
{
	FILE *f = fopen("alice.bit", "rb");

	// �� ��Ʈ�� �о�� �Ǵ����� ����,,,
	int numOfBits = 0;
	fread(&numOfBits, sizeof(int), 1, f);

	printf("���� ��Ʈ ��: %d\n", numOfBits);

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

	// ��Ʈ������ ���Ͽ� ���
	FILE *f = fopen("alice.bit", "wb");

	// ��Ʈ ������ ����� ���� (4byte)�� ����д�.
	fseek(f, 4, SEEK_SET);

	char oneByteBuffer = 0;  // �ʱⰪ�� 0
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
			numOfBits += 1; // ��ϵ� ��Ʈ ������ ����

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
	// ������ �� ó������ ���ư���,
	// ��Ʈ�� ������ ����Ѵ�.
	fseek(f, 0, SEEK_SET);
	fwrite(&numOfBits, sizeof(int), 1, f);

	fclose(f);
	return 0;
}



int main3333(void)
{
	FILE *f = fopen("alice.encoded", "rb");

	// encoded ������ �о ������ Ʈ���� ����

	// 1 �ܰ�... �� ���� ���ĺ��� �ִ��� �ľ�
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("There are %d alphabets\n", num);

	root = (struct hnode *)malloc(sizeof(struct hnode));
	root->left = root->right = 0;

	// 2 �ܰ�... �� ���ĺ��� �����Ͽ� ������ �ڵ带 �ٷ�..
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
				// ���� ���ߵǴµ�,,
				if (temp->left == 0)
				{
					temp->left = (struct hnode *)malloc(sizeof(struct hnode));
					temp->left->left = temp->left->right = 0;
				}
				temp = temp->left;

			}
			else
			{
				// ������ ���ߵǴµ�,,
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

	// encoded ������ �о ������ Ʈ���� ����

	// 1 �ܰ�... �� ���� ���ĺ��� �ִ��� �ľ�
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("There are %d alphabets\n", num);

	// 2 �ܰ�... �� ���ĺ��� �����Ͽ� ������ �ڵ带 �ٷ�..
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

	// ������ �ڵ带 ���Ͽ� �� ���ô�.
	FILE *f = fopen("alice.encoded", "wb");

	// 1�ܰ�. �� �� ���� ���ĺ������� 1����Ʈ�� ���
	char numOfChars = (char)getNumOfCodes();
	fwrite(&numOfChars, sizeof(char), 1, f);

	// 2�ܰ�. �� ���ĺ���, '���ĺ�' + '����' + '�ڵ�'�� ���
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