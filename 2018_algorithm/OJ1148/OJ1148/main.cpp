#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALE 1
#define FEMALE 2

#define MAX_STACK_SIZE 50

struct node {
	int age;
	int sex;
	char *name;
	char *hometown;
	struct node *NEXT;
};

typedef struct node NODE;

NODE *HEAD = 0;

NODE *make_node(char *name, int age, int sex, char *hometown) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->NEXT = 0;
	NEW->age = age; NEW->sex = sex;
	NEW->name = (char *)malloc(sizeof(char) * 80);
	NEW->hometown = (char *)malloc(sizeof(char) * 80);
	strcpy(NEW->name, name);
	strcpy(NEW->hometown, hometown);
	return NEW;
}

void addToSLL(char *name, int age, int sex, char *hometown) {
	NODE *NEW = make_node(name, age, sex, hometown);
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
int getCountOfCity(char *city) {
	int count = 0;
	NODE *CUR = HEAD;
	while (CUR != 0) {
		if (strcmp(city, CUR->hometown) == 0) {
			count++;
		}
		CUR = CUR->NEXT;
	}
	return count;
}
char *Cities[100] = { 0, };
int top = -1;

int isExist(char *v, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (strcmp(v, Cities[i]) == 0) return 1;
	}
	return 0;
}

int push(char *v) {
	if (top == 99) {
		return 0;
	}
	else {
		if (isExist(v, 100)) {
			return 0;
		}
		else {
			Cities[top] = v;
			top++;
			return 1;
		}

	}
}
void addCities() {
	NODE *CUR = HEAD;
	while (CUR != 0) {
		push(CUR->hometown);
		CUR = CUR->NEXT;
	}

}


int main() {
	int i, n, age, sex;
	char name[80];
	char hometown[80];
	char city[80];

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s %d %d %s", name, &age, &sex, hometown);
		addToSLL(name, age, sex, hometown);
	}
	scanf("%s", city);
	printf("n_of_seoul : %d", getCountOfCity(city));
	return 0;
}