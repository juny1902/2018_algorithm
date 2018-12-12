#include <stdio.h>
#include <stdlib.h>

#define SZ 6

struct node
{
	char v;
	struct node *next;
	struct node *left;
	struct node *right;
};

struct node *visited = 0;

struct node *graph[SZ];

struct node *stack = 0;

struct node *queue = 0;

// SLL의 맨 뒤에 붙인다.
void enqueue(char v)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v;
	new_one->next = 0;

	if (queue == 0)
	{
		queue = new_one;
		return;
	}

	struct node *temp = queue;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;

}

// SLL의 앞에서 dequeue
char dequeue(void)
{
	if (queue == 0)
	{
		return '-';
	}
	char v = queue->v;
	struct node *temp = queue;
	queue = queue->next;
	free(temp);
	return v;
}


void addToVisited(char v)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v;
	new_one->left = new_one->right = 0;

	if (visited == 0)
	{
		visited = new_one;
		return;
	}
	struct node *temp = visited;

	while (1)
	{
		if (temp->v > v)
		{
			if (temp->left == 0)
			{
				temp->left = new_one;
				return;
			}
			temp = temp->left;
		}
		else
		{
			if (temp->right == 0)
			{
				temp->right = new_one;
				return;
			}
			temp = temp->right;
		}
	}
}

//
// 만약 v가 visited에 있으면 1을 반환,
// 없으면 0을 반환
//
int checkVisited(char v)
{
	struct node *temp = visited;

	while (temp != 0)
	{
		if (temp->v == v)
		{
			return 1;
		}
		if (temp->v > v)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return 0;
}


void push(char v)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v;
	new_one->next = 0;

	new_one->next = stack;
	stack = new_one;
	return;
}

char pop(void)
{
	if (stack == 0)
	{
		return '-';  // stack이 비었다는 표시
	}
	struct node *temp = stack;
	char v = stack->v;
	stack = stack->next;
	free(temp);
	return v;
}



void addEdgeMini(char src, char dst)
{
	int idx = src - 'A';

	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = dst;
	new_one->next = 0;

	if (graph[idx] == 0)
	{
		graph[idx] = new_one;
		return;
	}

	//
	// 기존에 노드들이 있어서 끝을 찾아서 붙이는 과정
	//
	struct node *temp = graph[idx];
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;
}

void addEdge(char src, char dst)
{
	addEdgeMini(src, dst);
	addEdgeMini(dst, src);
}

void performDFS(char v)
{
	//1.단계
	push(v);

	//2.단계
	while (1)
	{
		char x = pop();
		if (x == '-')
		{
			return;
		}
		if (checkVisited(x) == 1)
		{
			continue;
		}
		printf("-----> %c\n", x);
		addToVisited(x);

		struct node *temp = graph[x - 'A'];

		while (temp != 0)
		{
			if (checkVisited(temp->v) == 0)
			{
				push(temp->v);
			}
			temp = temp->next;
		}
	}
}

void performBFS(char v)
{
	//1.단계
	enqueue(v);

	//2.단계
	while (1)
	{
		char x = dequeue(); // 하나를 꺼낸다.
		if (x == '-') // 비어있다면 ? 
		{
			return; // 그대로 종료
		}
		if (checkVisited(x) == 1) // 꺼낸게 이미 방문한거라면 ?
		{
			continue; // 무시하고 다음거 꺼냄 (루프 시작점으로 돌아가기)
		}
		printf("-----> %c\n", x); // 방문했다고 표시
		addToVisited(x); // 방문햇다고 표시

		struct node *temp = graph[x - 'A']; 

		while (temp != 0)
		{
			if (checkVisited(temp->v) == 0)
			{
				enqueue(temp->v);
			}
			temp = temp->next;
		}
	}
}

int main(void)
{
	addEdge('A', 'C');
	addEdge('C', 'B');
	addEdge('C', 'F');
	addEdge('B', 'E');
	addEdge('D', 'B');
	addEdge('D', 'F');

	printf("DFS result\n");
	performDFS('C');

	visited = 0;

	printf("BFS result\n");
	performBFS('C');

	return 0;
}