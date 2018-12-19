#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EDGE {
	char *name;
	int distance;
	EDGE *NEXT;
}EDGE;

typedef struct VERTEX {
	char *name;
	VERTEX *NEXT;
	EDGE *CONNECTED;
}VERTEX;

typedef struct Dijkstra {
	char *name;
	int found;
	int dist;
	char *prev;
}Dijkstra;

typedef struct NODE {
	char *name;
	NODE *NEXT;
}NODE;

VERTEX *GRAPH = 0;
Dijkstra *DTABLE = 0;
NODE *STACK = 0;

VERTEX *findVertexByName(char *name);
int findIndexFromDTABLE(char *name);

NODE *make_node(char *name) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->name = name;
	NEW->NEXT = 0;
	return NEW;
}

void push(char *name) {
	NODE *NEW = make_node(name);
	NEW->NEXT = STACK;
	STACK = NEW;
}

char *pop() {
	if (STACK == 0) {
		return 0;
	}
	else {
		NODE *TMP = STACK;
		char *ret = STACK->name;
		STACK = STACK->NEXT;
		free(TMP);
		return ret;
	}
}

void pushPathways(char *start, char *end) {
	int cur_idx = findIndexFromDTABLE(end);
	int end_idx = findIndexFromDTABLE(start);
	while (cur_idx != end_idx) {
		push(DTABLE[cur_idx].name);
		cur_idx = findIndexFromDTABLE(DTABLE[cur_idx].prev);
	}
	push(DTABLE[end_idx].name);
}

void printPathway() {
	NODE *CUR = STACK;
	printf("----------- 경로 안내 -----------\n");
	while (CUR != 0) {
		printf("%10s 를 경유합니다. | 운항거리누적 : %d\n", CUR->name, DTABLE[findIndexFromDTABLE(CUR->name)].dist);
		CUR = CUR->NEXT;
	}
	printf("---------------------------------\n");
}

int countVertexes() {
	int cnt = 0;
	VERTEX *CUR = GRAPH;
	while (CUR != 0) {
		cnt++;
		CUR = CUR->NEXT;
	}
	return cnt;
}

int findShortestIndexFromDTABLE() {
	int size = countVertexes();
	int shortest = 2000000000;
	int shortest_idx = -1;
	
	for (int i = 0; i < size; i++) {
		if (DTABLE[i].found == 0 && DTABLE[i].dist < shortest) {
			shortest = DTABLE[i].dist;
			shortest_idx = i;
		}
	}
	return shortest_idx;
}

int findIndexFromDTABLE(char *name) {
	int size = countVertexes();
	for (int i = 0; i < size; i++){
		if (strcmp(DTABLE[i].name, name) == 0) return i;
	}
	return -1;
}

void runDijkstra(char *start, char *end) {
	int start_idx = findIndexFromDTABLE(start);
	int end_idx = findIndexFromDTABLE(end);
	DTABLE[start_idx].dist = 0;
	while (1) {
		int shortest_idx = findShortestIndexFromDTABLE();

		if (shortest_idx == -1) {
			printf("---------------------------------\n");
			printf("-> %s 부터 %s 까지의 최단거리는 %d 입니다.\n",
				DTABLE[start_idx].name, DTABLE[end_idx].name, DTABLE[end_idx].dist);
			break;
		}
		if (DTABLE[end_idx].found == 1) {
			printf("---------------------------------\n");
			printf("-> %s 부터 %s 까지의 최단거리는 %d 입니다.\n",
				DTABLE[start_idx].name, DTABLE[end_idx].name, DTABLE[end_idx].dist);
			break;
		}
		DTABLE[shortest_idx].found = 1;


		EDGE *NEIGHBOR = findVertexByName(DTABLE[shortest_idx].name)->CONNECTED;
		while (NEIGHBOR != 0) {
			int neighbor_idx = findIndexFromDTABLE(NEIGHBOR->name);
			if (DTABLE[neighbor_idx].dist > DTABLE[shortest_idx].dist + NEIGHBOR->distance) {
				DTABLE[neighbor_idx].dist = DTABLE[shortest_idx].dist + NEIGHBOR->distance;
				DTABLE[neighbor_idx].prev = DTABLE[shortest_idx].name;
			}
			NEIGHBOR = NEIGHBOR->NEXT;
		}
	}
}

void initDijkstraTable() {
	int size = countVertexes();
	DTABLE = (Dijkstra *)malloc(sizeof(Dijkstra)*size);
	VERTEX *CUR = GRAPH;
	for (int i = 0; i < size; i++) {
		DTABLE[i].dist = 2000000000;
		DTABLE[i].found = 0;
		DTABLE[i].prev = 0;
		DTABLE[i].name = CUR->name;
		CUR = CUR->NEXT;
	}
}

VERTEX *make_vertex_node(char *name) {
	VERTEX *NEW = (VERTEX *)malloc(sizeof(VERTEX));
	NEW->name = (char *)malloc(strlen(name) + 1);
	strcpy(NEW->name, name);
	NEW->NEXT = 0;
	NEW->CONNECTED = 0;
	return NEW;
}

EDGE *make_edge_node(char *name, int distance) {
	EDGE *NEW = (EDGE *)malloc(sizeof(EDGE));
	NEW->name = (char *)malloc(strlen(name) + 1);
	strcpy(NEW->name, name);
	NEW->distance = distance;
	NEW->NEXT = 0;
	return NEW;
}
VERTEX *findVertexByName(char *name) {
	VERTEX *CUR = GRAPH;
	while (CUR != 0) {
		if (strcmp(CUR->name, name) == 0) return CUR;
		CUR = CUR->NEXT;
	}
	return 0;
}
void addEdge(char *from, char *to, int dist) {
	VERTEX *CUR = findVertexByName(from);
	if (CUR == 0) {
		CUR = make_vertex_node(from);
		if (GRAPH == 0) {
			GRAPH = CUR;
		}
		else {
			VERTEX *TMP = GRAPH;
			while (TMP->NEXT != 0) {
				TMP = TMP->NEXT;
			}
			TMP->NEXT = CUR;
		}
	}

	EDGE *NEW = make_edge_node(to, dist);
	if (CUR->CONNECTED == 0) {
		CUR->CONNECTED = NEW;
	}
	else {
		EDGE *TMP = CUR->CONNECTED;
		while (TMP->NEXT != 0) {
			TMP = TMP->NEXT;
		}
		TMP->NEXT = NEW;
	}
}

void addEdgeBidirectional(char *from, char *to,int dist) {
	addEdge(from, to, dist);
	addEdge(to, from, dist);
}

void printDijkstra() {
	int size = countVertexes();
	for (int i = 0; i < size; i++) {
		printf("%s\t%d\t%d\t%s\n", DTABLE[i].name, DTABLE[i].found, DTABLE[i].dist, DTABLE[i].prev);
	}
}

void printCityList() {
	int cnt = 0;
	VERTEX *CUR = GRAPH;
	while (CUR != 0) {
		cnt++;
		printf("City #%d: %s\n", cnt, CUR->name);
		CUR = CUR->NEXT;
	}
}

int isCityThere(char *name) {
	VERTEX *CUR = GRAPH;
	while (CUR != 0) {
		if (strcmp(CUR->name, name) == 0) return 1;
		CUR = CUR->NEXT;
	}
	return 0;
}

int main() {
	// Edge 22개 추가 (12개 도시)
	addEdgeBidirectional((char *)"SALTLAKE",(char *)"LOSANGELES", 581);
	addEdgeBidirectional((char *)"SALTLAKE",(char *)"OKCITY", 864);
	addEdgeBidirectional((char *)"SALTLAKE",(char *)"DENVER", 378);
	addEdgeBidirectional((char *)"LOSANGELES",(char *)"LASVEGAS", 231);
	addEdgeBidirectional((char *)"LOSANGELES",(char *)"TUCSON", 455);
	addEdgeBidirectional((char *)"TUCSON", (char *)"OKCITY", 800);
	addEdgeBidirectional((char *)"TUCSON", (char *)"DALLAS", 824);
	addEdgeBidirectional((char *)"DALLAS", (char *)"LASVEGAS", 1075);
	addEdgeBidirectional((char *)"DALLAS", (char *)"KANSASCITY", 454);
	addEdgeBidirectional((char *)"LASVEGAS", (char *)"OKCITY", 992);
	addEdgeBidirectional((char *)"LASVEGAS", (char *)"DENVER", 615);
	addEdgeBidirectional((char *)"OKCITY", (char *)"DESMOINES", 472);
	addEdgeBidirectional((char *)"OKCITY", (char *)"KANSASCITY", 300);
	addEdgeBidirectional((char *)"DENVER", (char *)"MADISON", 833);
	addEdgeBidirectional((char *)"DENVER", (char *)"DESMOINES", 602);
	addEdgeBidirectional((char *)"MADISON", (char *)"DESMOINES", 240);
	addEdgeBidirectional((char *)"MADISON", (char *)"CHICAGO", 122);
	addEdgeBidirectional((char *)"DESMOINES", (char *)"CHICAGO", 301);
	addEdgeBidirectional((char *)"DESMOINES", (char *)"KANSASCITY", 177);
	addEdgeBidirectional((char *)"DESMOINES", (char *)"STLOUIS", 270);
	addEdgeBidirectional((char *)"KANSASCITY", (char *)"STLOUIS", 244);
	addEdgeBidirectional((char *)"CHICAGO", (char *)"STLOUIS", 259);

	// printCityList(); // For Debug

	// printf("Vertex의 수는 %d개.\n", countVertexes()); // For Debug

	initDijkstraTable();
	
	char start[100], end[100];
	while (1) {
		printf("출발 도시를 입력하세요 : ");
		scanf("%s", start);
		if (isCityThere(start)) {
			break;
		}
		else {
			printf("%s 를 찾을 수 없습니다. 철자를 확인해주세요.\n", start);
			continue;
		}
	}
	
	while (1) {
		printf("도착 도시를 입력하세요 : ");
		scanf("%s", end);
		if (isCityThere(end)) {
			break;
		}
		else {
			printf("%s 를 찾을 수 없습니다. 철자를 확인해주세요.\n", end);
			continue;
		}
	}
	

	runDijkstra(start, end);

	// printDijkstra(); // For Debug

	pushPathways(start, end);
	printPathway();

	char TMP[100];
	printf("종료하려면 아무 글자나 입력 후 Enter 키를 누르십시오.\n");
	scanf("%s", TMP);

	return 0;

}