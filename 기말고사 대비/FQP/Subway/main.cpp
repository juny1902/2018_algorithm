#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct StationInfo {
	char *s_id;
	char *s_name;
	char *s_line;
	StationInfo *NEXT;
}StationInfo;

typedef struct ConnectedStation {
	char *s_id;
	int distance;
	ConnectedStation *NEXT;
}ConnectedStation;

typedef struct Station {
	char *s_id;
	ConnectedStation *CONNECTED;
	Station *NEXT;
}Station;

StationInfo *STATIONS = 0;
Station *GRAPH = 0;

void addStationInfo(char *s_id, char *s_name, char *s_line) {
	StationInfo *NEW = (StationInfo *)malloc(sizeof(StationInfo));
	NEW->s_id = (char *)malloc(strlen(s_id) + 1);
	strcpy(NEW->s_id, s_id);
	NEW->s_name = (char *)malloc(strlen(s_name) + 1);
	strcpy(NEW->s_name, s_name);
	NEW->s_line = (char *)malloc(strlen(s_line) + 1);
	strcpy(NEW->s_line, s_line);

	NEW->NEXT = 0;
	
	if (STATIONS == 0) {
		STATIONS = NEW;
	}
	else {
		StationInfo *CUR = STATIONS;
		while (CUR != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}

}

Station *findStation(char *s_id) {
	Station *CUR = GRAPH;
	while (CUR != 0) {
		if (strcmp(CUR->s_id, s_id) == 0) {
			return CUR;
		}
		CUR = CUR->NEXT;
	}
	return 0;
}

void addEdge(char *from, char *to, int distance) {

}

int main() {
	FILE *fp = fopen("d:\\seoul.txt", "rt");
	if (fp == 0) return 0;
	char buf[100] = { 0, };
	while (!feof(fp)) {
		
		fgets(buf, 99, fp);
		if (buf[0] == '\n') break;
		char s_id[100], s_name[100], s_line[100];
		sscanf(buf,"%s %s %s\n", s_id, s_name, s_line);
		addStationInfo(s_id, s_name, s_line);
		
	}

	while (!feof(fp)) {
		fgets(buf, 99, fp);
		if (buf[0] == '\n') break;
		char from_id[100], to_id[100];
		int distance[100];
		sscanf(buf, "%s %s %d\n", from_id, to_id, distance);
		addEdge(from_id to_id, distance);
	}
}