#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct SLL_NODE {
	char *name;
	int age;
	struct SLL_NODE *NEXT;
};

typedef struct SLL_NODE SLL_NODE;

SLL_NODE *HEAD = 0;

SLL_NODE *make_node(char *name, int age) {
	SLL_NODE *NEW = (SLL_NODE *)malloc(sizeof(SLL_NODE));
	NEW->name = (char *)malloc(sizeof(char) * 80);

	strcpy(NEW->name, name);
	NEW->age = age;

	return NEW;
}
void addToSLL(char *name, int age) {
	SLL_NODE *NEW = make_node(name, age);
	NEW->NEXT = 0;
	if (HEAD == 0) {
		HEAD = NEW;
		return;
	}
	else {
		SLL_NODE *CUR = HEAD;
		while (CUR->NEXT != 0) {
			CUR = CUR->NEXT;
		}
		CUR->NEXT = NEW;
	}
}

SLL_NODE *findOldest() {
	int age = 0;
	SLL_NODE *CUR = HEAD;
	SLL_NODE *RET = 0;
	char *name;
	while (CUR != 0) {
		if (CUR->age > age) {
			age = CUR->age;
			RET = CUR;
		}
		CUR = CUR->NEXT;
	}
	return RET;
}

SLL_NODE *findYoungest() {
	int age = 100;
	SLL_NODE *CUR = HEAD;
	SLL_NODE *RET = 0;
	char *name;
	while (CUR != 0) {
		if (CUR->age < age) {
			age = CUR->age;
			RET = CUR;
		}
		CUR = CUR->NEXT;
	}
	return RET;
}

int getMean() {
	int sum = 0;
	int cnt = 0;
	SLL_NODE *CUR = HEAD;
	while (CUR != 0) {
		sum += CUR->age;
		cnt++;
		CUR = CUR->NEXT;
	}
	return sum / cnt;
}

int getNearest(int mean) {
	SLL_NODE *CUR = HEAD;
	int distance;
	int nearest=100;
	while (CUR != 0) {
		distance = abs(CUR->age - mean);
		if (distance < nearest) {
			nearest = CUR->age;
		}
		CUR = CUR->NEXT;
	}
	return nearest;
}
void printNearests(){
	SLL_NODE *CUR = HEAD;
	int nearest = getNearest(getMean());
	while (CUR != 0) {
		if (CUR->age == nearest) {
			printf("%s\n", CUR->name);
		}
		CUR = CUR->NEXT;
	}
}
int main() {
	int n, i;
	scanf("%d", &n);
	char name_t[80];
	int age_t;
	for (i = 0; i < n; i++) {
		scanf("%s %d", name_t, &age_t);
		addToSLL(name_t, age_t);
	}
	printNearests();
	return 0;
}