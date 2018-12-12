#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct StationInfo {
	char *id; // ������ �ʿ��� ����� �Ҵ��ϱ� ���� ���� �����ͷ� ����.
	char *name;
	char *lineNumber;
	StationInfo *NEXT;
}StationInfo;

typedef struct ConnectedStation { // EDGE
	char *stationId;
	int distance;
	ConnectedStation *NEXT;
}ConnectedStation;

typedef struct Station { // VERTEX
	char *stationID;
	ConnectedStation *CONNECTED;
	Station *NEXT;
}Station;

typedef struct Dijikstra {
	char *v; // ID
	int found;
	int dist;
	char *prev; // ID
}Dijikstra;

Station *GRAPH = 0;
StationInfo *STATIONS = 0;
Dijikstra *DTABLE = 0;
Station *findStation(char *fromStation);

typedef struct NODE {
	char *v;
	NODE *NEXT;
	NODE *LEFT;
	NODE *RIGHT;
}NODE;

NODE *STACK = 0;
NODE *VISITED = 0;

NODE *make_node(char *v) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->v = (char *)malloc(strlen(v) + 1);
	strcpy(NEW->v, v);
	NEW->NEXT = NEW->LEFT = NEW->RIGHT = 0;
	return NEW;
}

char *findNameFromID(char *ID) {
	StationInfo *CUR = STATIONS;
	while (CUR != 0) {
		if (strcmp(CUR->id, ID) == 0) {
			return CUR->name;
		}
		CUR = CUR->NEXT;
	}
	return 0;
}

char *findLineFromID(char *ID) {
	StationInfo *CUR = STATIONS;
	while (CUR != 0) {
		if (strcmp(CUR->id, ID) == 0) {
			return CUR->lineNumber;
		}
		CUR = CUR->NEXT;
	}
	return 0;
}

void addToVisited(char *v) {
	NODE *NEW = make_node(v);

	if (VISITED == 0) {
		VISITED = NEW;
		return;
	}
	else {
		NODE *CUR = VISITED;

		while (CUR != 0) {
			if (strcmp(v,CUR->v) == -1) {
				if (CUR->LEFT == 0) {
					CUR->LEFT = NEW;
					return;
				}
				else {
					CUR = CUR->LEFT;
				}
			}
			else {
				if (CUR->RIGHT == 0) {
					CUR->RIGHT = NEW;
					return;
				}
				else {
					CUR = CUR->RIGHT;
				}
			}
		}
	}
}

void push(char *v) {
	NODE *NEW = make_node(v);
	NEW->NEXT = STACK;
	STACK = NEW;
}

char *pop() {
	if (STACK == 0) {
		return 0;
	}
	else {
		NODE *TMP = STACK;
		char *v = (STACK)->v;
		STACK = (STACK)->NEXT;
		free(TMP);
		return v;
	}
}

int checkVisited(char *v) {
	NODE *CUR = VISITED;
	while (CUR != 0) {
		if (strcmp(CUR->v,v) == 0) {
			return 1;
		}
		else if (strcmp(v,CUR->v) == - 1) {
			CUR = CUR->LEFT;
		}
		else {
			CUR = CUR->RIGHT;
		}
	}
	return 0;
}

void addAdjacentVertexes(char *v) {
	ConnectedStation *CUR = findStation(v)->CONNECTED;
	while (CUR != 0) {
		if (checkVisited(CUR->stationId) == 0) push(CUR->stationId);
		CUR = CUR->NEXT;
	}
}



void doDFS(char *v) {
	printf("%s ���� ��ȸ�մϴ�.\n", v);
	int cnt = 0;
	push(v);
	while (1) {
		char *x = pop();
		if (x == 0) { 
			printf("�湮 ������ �� : %d\n", cnt);
			return; }
		if (checkVisited(x) == 1) continue;
		printf("%sȣ�� %s �� �湮�߽��ϴ�.\n", findLineFromID(x), findNameFromID(x));
		cnt++;
		addToVisited(x);
		addAdjacentVertexes(x);
	}
}

int countStations() {
	Station *CUR = GRAPH;
	int n = 0;
	while (CUR != 0) {
		n++;
		CUR = CUR->NEXT;
	}
	return n;
}

void initDijikstraTable() {
	int n = countStations();
	
	DTABLE = (Dijikstra *)malloc(sizeof(Dijikstra) * n);
	printf("�� ������ ���� %d ��.\n", n);


	StationInfo *CUR = STATIONS;
	for (int i = 0; i < n; i++) {
		DTABLE[i].found = 0;
		DTABLE[i].prev = 0;
		DTABLE[i].dist = 2000000000;
		DTABLE[i].v = CUR->id;
		CUR = CUR->NEXT;
	}
}

int findNextShortestIndex() {
	int n = countStations();
	int shortest = 2000000000;
	int shortest_idx = -1;
	for (int i = 0; i < n; i++) {
		if (DTABLE[i].found == 0 && DTABLE[i].dist < shortest) {
			shortest = DTABLE[i].dist;
			shortest_idx = i;
		}
	}
	return shortest_idx;
}

int findVertexIndexFromDtable(char *name) {
	int n = countStations();
	for (int i = 0; i < n; i++) {
		if (strcmp(DTABLE[i].v, name) == 0) {
			return i;
		}
	}
	return -1;
}
void printDijikstra() {
	int n = countStations();
	for (int i = 0; i < n; i++) {
		printf("%s %d %s %d\n", DTABLE[i].v, DTABLE[i].found, DTABLE[i].prev, DTABLE[i].dist);
	}
}
void runDijkstra(char *start,char *end) {
	int idx_start = findVertexIndexFromDtable(start);
	int idx_end = findVertexIndexFromDtable(end);
	DTABLE[idx_start].dist = 0;
	while (1) {
		int idx_shortest = findNextShortestIndex();
		DTABLE[idx_shortest].found = 1;
		if (DTABLE[idx_end].found == 1) {
			printf("%s(%s) ���� %s(%s) ���� �ҿ�ð� : %d��\n",findNameFromID(start),start,findNameFromID(end),end, DTABLE[idx_end].dist);
			return;
		}

		ConnectedStation *NEIGHBORS = findStation(DTABLE[idx_shortest].v)->CONNECTED;
		while (NEIGHBORS != 0) {
			int idx_neighbor = findVertexIndexFromDtable(NEIGHBORS->stationId);
			if (DTABLE[idx_neighbor].dist > DTABLE[idx_shortest].dist + NEIGHBORS->distance) {
				DTABLE[idx_neighbor].dist = DTABLE[idx_shortest].dist + NEIGHBORS->distance;
				DTABLE[idx_neighbor].prev = DTABLE[idx_shortest].v;
			}
			NEIGHBORS = NEIGHBORS->NEXT;
		}
	}
}

NODE *STACK_VISITED;
void visit_station(char *v) {
	NODE *NEW = make_node(v);
	NEW->NEXT = STACK_VISITED;
	STACK_VISITED = NEW;
}
void print_visited_station() {
	NODE *CUR = STACK_VISITED;
	printf("--------------- ���� ��� --------------\n");
	while (CUR != 0) {
		printf("%sȣ�� %s(%s)�� �湮.\n", findLineFromID(CUR->v), findNameFromID(CUR->v), CUR->v);
		if (CUR->NEXT != 0) {
			if (strcmp(findNameFromID(CUR->v), findNameFromID(CUR->NEXT->v)) == 0) {
				printf("%s ���� %s ���� ȯ��.\n", findLineFromID(CUR->v), findLineFromID(CUR->NEXT->v));
			}
		}
		CUR = CUR->NEXT;
	}
}
void findLocationsFromDTABLE(char *start, char *end) {
	int idx_start = findVertexIndexFromDtable(start);
	int idx_end = findVertexIndexFromDtable(end);
	int cur_idx = idx_end;
	visit_station(DTABLE[cur_idx].v);
	while (cur_idx != idx_start) {
		cur_idx = findVertexIndexFromDtable(DTABLE[cur_idx].prev);
		visit_station(DTABLE[cur_idx].v);
	}
	print_visited_station();
}

ConnectedStation *make_connected_station(char *toStation, int distance) {
	ConnectedStation *NEW = (ConnectedStation *)malloc(sizeof(ConnectedStation));
	NEW->stationId = (char *)malloc(strlen(toStation) + 1);
	strcpy(NEW->stationId, toStation);
	NEW->distance = distance;
	NEW->NEXT = 0;
	return NEW;
}

Station *make_station(char *stationID, int distance) {
	Station *NEW = (Station *)malloc(sizeof(Station));
	NEW->stationID = (char *)malloc(strlen(stationID) + 1);
	strcpy(NEW->stationID, stationID);
	NEW->CONNECTED = 0;
	NEW->NEXT = 0;
	return NEW;
}

StationInfo *make_station_info(char *id, char *name, char *lineNumber) {
	StationInfo *NEW = (StationInfo *)malloc(sizeof(StationInfo));

	NEW->id = (char *)malloc(strlen(id) + 1); // ���� ���� + Null ���� ��ŭ ���� �Ҵ�
	NEW->name = (char *)malloc(strlen(name) + 1);
	NEW->lineNumber = (char *)malloc(strlen(lineNumber) + 1);

	strcpy(NEW->id, id);			// NEW->id �� �ٷ� �����ϸ� �ȵǴ� ������ ?
	strcpy(NEW->name, name);		// ������ �ϱ⶧����, �ּҰ� ����Ű�� ���� �ٲ�� �ش� �������� �������� ���󰡰Ե�.
	strcpy(NEW->lineNumber, lineNumber);

	NEW->NEXT = 0;
	return NEW;
}

Station *findStation(char *fromStation) {
	Station *CUR = GRAPH;
	while (CUR != 0) {
		if (strcmp(fromStation, CUR->stationID) == 0) return CUR;
		CUR = CUR->NEXT;
	}
	return 0;
}
void addEdge(char *fromStation, char *toStation, int distance) {
	Station *CUR = findStation(fromStation);
	if (CUR == 0) {
		CUR = make_station(fromStation, distance);
		if (GRAPH == 0) {
			GRAPH = CUR;
		}
		else {
			Station *TMP = GRAPH;
			while (TMP->NEXT != 0) {
				TMP = TMP->NEXT;
			}
			TMP->NEXT = CUR;
		}
	}

	ConnectedStation *NEW = make_connected_station(toStation, distance);
	if (CUR->CONNECTED == 0) {
		CUR->CONNECTED = NEW;
	}
	else {
		ConnectedStation *TMP = CUR->CONNECTED;
		while (TMP->NEXT != 0) {
			TMP = TMP->NEXT;
		}
		TMP->NEXT = NEW;
	}
}
void addStationInfo(char *stationID, char *stationName, char *lineNumber) {
	StationInfo *NEW = make_station_info(stationID, stationName, lineNumber);
	if (STATIONS == 0) {
		STATIONS = NEW;
		return;
	}
	else {
		StationInfo *CUR = STATIONS;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}

void printStations() {
	StationInfo *CUR = STATIONS;
	while (CUR != 0) {
		printf("%s %s %s\n", CUR->id, CUR->name, CUR->lineNumber);
		CUR = CUR->NEXT;
	}
}

void showConnectedStationID(char *ID) {
	ConnectedStation *CUR = findStation(ID)->CONNECTED;
	printf("%s : ", ID);
	while (CUR != 0) {
		printf("%s - ",CUR->stationId);
		CUR = CUR->NEXT;
	}
	printf("\n");
}


void addTransferStations() {
	StationInfo *CUR = STATIONS;
	while (CUR != 0) {
		if (CUR->NEXT != 0) {
			StationInfo *to_compare = CUR->NEXT;
			while (to_compare != 0) {
				if (strcmp(to_compare->name, CUR->name) == 0) {
					// printf("%s �� ȯ�¿� �Դϴ�\n", to_compare->name);
					addEdge(to_compare->id, CUR->id, 0);
					addEdge(CUR->id, to_compare->id, 0);
					// printf("������ %s �� %s �� ������.\n\n", CUR->id, to_compare->id);
				}
				to_compare = to_compare->NEXT;
			}
		}
		CUR = CUR->NEXT;
	}
}

char *findIDfromStations(char *name,char *line) {
	StationInfo *CUR = STATIONS;
	while (CUR != 0) {
		if (strcmp(CUR->name, name) == 0 && strcmp(CUR->lineNumber,line) == 0) {
			return CUR->id;
		}
		CUR = CUR->NEXT;
	}
}

int main() {
	FILE *fp = fopen("d:\\seoul.txt", "rt");
	if (fp == 0) { 
		printf("���� �б� ����\n");
		return 0;
	}
	char buf[100];
	while (!feof(fp)) {
		fgets(buf, 99, fp);
		if (buf[0] == '\n') { // ù��° ���� �������� �а� �ϴ� Ż��.
			break;
		}
		else {
			// buf = "100 �ҿ�� 1"
			char id[100], name[100], line[100];
			sscanf(buf, "%s %s %s\n", id, name, line);
			addStationInfo(id, name, line); // Station ����Ʈ�� ��� �ϳ� �߰�.
		}
		buf[0] = '\0';
	}
	while (!feof(fp)) {
		fgets(buf, 99, fp);
		if (buf[0] == '\n') { // ù��° ���� �������� �а� �ϴ� Ż��.
			break;
		}
		else {
			// buf = "src dst weight"
			char from_Station[100], to_Station[100];
			;			int distance;
			sscanf(buf, "%s %s %d\n", from_Station, to_Station, &distance);
			addEdge(from_Station, to_Station, distance);
		}
		buf[0] = '\0';
	}
	fclose(fp);

	addTransferStations();
	char start[50], end[50], start_line[50], end_line[50];
	printf("���ۿ� : ");
	scanf("%s", start);
	printf("���ۿ� �뼱��ȣ : ");
	scanf("%s", start_line);
	
	char *start_station = findIDfromStations(start, start_line);
	printf("���ۿ� ID�� : %s\n", start_station);

	printf("������ : ");
	scanf("%s", end);
	printf("������ �뼱��ȣ : ");
	scanf("%s", end_line);

	char *end_station = findIDfromStations(end, end_line);
	printf("������ ID�� : %s\n", end_station);
	printf("------------------------------------------------\n");
	printf("%s ȣ�� %s ��(%s) ���� %s ȣ�� %s ��(%s) ������ ��θ� Ž���մϴ�.\n", start_line, start,start_station, end_line, end,end_station);

	// doDFS(start_station);

	initDijikstraTable();

	runDijkstra(start_station, end_station);
	
	findLocationsFromDTABLE(start_station, end_station);

	return 0;
}