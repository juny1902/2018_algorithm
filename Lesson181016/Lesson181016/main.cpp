#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ���� : | �� ��ȣ | �� �̸� | �뼱 |
// 707�� �ٺ��� Distance (Weight) - Directed Graph
// ���� ���� : | ���ۿ� | ������ | ����ġ |
// ȯ�¿��� ��� �ϳ�? (�� �� �̻��� ������ ��ġ�� ��)
// ���� ���� : ���� �� �̸�, �ٸ� �� ��ȣ/�뼱�� ������ �ٸ� ������ ����.

int main() {
	
	FILE *f = fopen("seoul.txt", "rt"); // ������ �������� �ּҸ� ��ȯ����.
	
	if (f == 0) {
		printf("���� �б� ����.\n");
		fclose(f);
		return 0;
	}

	char buffer[100];
	char *token;
	char lists[3][100];

	while (1) // f�� EOF �� �������� ���� ����.
	{
		if (feof(f) != 0) break;
		fgets(buffer, 99, f); // f �� ���� 99�ڸ� �� �� �д´�. - ���� NULL �����͸� ������ �ϹǷ�.

		token = strtok(buffer, " ");
		while (token != 0) {
			printf("��ȣ : %s, ���� : %s, �뼱 : %s\n", token);
		}
		buffer[0] = '\0';
		
	}

	

	

	fclose(f);

	return 0;
	
}