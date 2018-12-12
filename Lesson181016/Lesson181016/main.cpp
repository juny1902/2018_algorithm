#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 파일 포맷 : | 역 번호 | 역 이름 | 노선 |
// 707번 줄부터 Distance (Weight) - Directed Graph
// 파일 포맷 : | 시작역 | 도착역 | 가중치 |
// 환승역은 어떻게 하나? (두 개 이상의 라인이 겹치는 것)
// 파일 포맷 : 같은 역 이름, 다른 역 번호/노선을 가지는 다른 라인이 있음.

int main() {
	
	FILE *f = fopen("seoul.txt", "rt"); // 파일이 열린곳의 주소를 반환받음.
	
	if (f == 0) {
		printf("파일 읽기 실패.\n");
		fclose(f);
		return 0;
	}

	char buffer[100];
	char *token;
	char lists[3][100];

	while (1) // f가 EOF 에 도달하지 않은 동안.
	{
		if (feof(f) != 0) break;
		fgets(buffer, 99, f); // f 로 부터 99자를 한 줄 읽는다. - 끝에 NULL 포인터를 가져야 하므로.

		token = strtok(buffer, " ");
		while (token != 0) {
			printf("번호 : %s, 역명 : %s, 노선 : %s\n", token);
		}
		buffer[0] = '\0';
		
	}

	

	

	fclose(f);

	return 0;
	
}