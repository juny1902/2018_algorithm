#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALE 1
#define FEMALE 2

struct node {
	int age;
	int sex;
	char *name;
	struct node *NEXT;
};

typedef struct node NODE;

NODE *HEAD = 0;

NODE *make_node(int age, int sex, char *name) {
	NODE *NEW = (NODE *)malloc(sizeof(NODE));
	NEW->NEXT = 0;
	NEW->age = age; NEW->sex = sex;
	NEW->name = (char *)malloc(sizeof(char) * 80);
	strcpy(NEW->name, name);
	return NEW;
}

void addToSLL(int age, int sex, char *name) {
	NODE *NEW = make_node(age, sex, name);

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

char *findOldestMale() {
	int max_age = 0;
	char *ret = (char *)malloc(80);
	NODE *CUR = HEAD;
	while (CUR != 0) {
		if (CUR->sex == MALE && CUR->age > max_age) {
			strcpy(ret, CUR->name);
			max_age = CUR->age;
		}
		else {
			CUR = CUR->NEXT;
		}

	}
	return ret;
}

char *findYoungestFemale() {
	int min_age = 1000;
	char *ret = (char *)malloc(80);
	NODE *CUR = HEAD;
	while (CUR != 0) {
		printf("CUR->name = %d\n", CUR->name);
		if (CUR->sex == FEMALE && CUR->age < min_age) {
			strcpy(ret, CUR->name);
			min_age = CUR->age;
		}
		else {
			CUR = CUR->NEXT;
		}

	}
	printf("min_age = %d\n", min_age);
	return ret;
}

int main() {
	int i, n, age, sex;
	char name[80];

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s %d %d", name, &age, &sex);
		addToSLL(age, sex, name);
	}
	printf("%s %s", findOldestMale(), findYoungestFemale());
	return 0;
}