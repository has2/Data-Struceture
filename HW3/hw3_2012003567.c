#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void init(QueueType *q);
void error(char *message);
int is_empty(QueueType *q);
int is_full(QueueType *q);
void enqueue(QueueType *q, element item);
element dequeue(QueueType *q);
element peek(QueueType *q);

int main(int argc, char *argv[])
{

	FILE *input;
	char c;			// 명령어를 받는 변수
	int key;		
	QueueType Q;
	init(&Q);		// queue 초기화

	if (argc == 1)
		input = fopen("input.txt", "r");
	else
		input = fopen(argv[1], "r");


	while (1) {
		c = fgetc(input); // 문자 한개를 읽어옴
		if (feof(input)) break; // 파일이 끝났으면 종료
		switch (c)
		{
		case 'e': // enqueue
			fscanf(input, "%d", &key);
			enqueue(&Q, key); // enqueue key
			printf("enqueue() : %d\n", key);
			printf("front : %d, rear : %d\n", Q.front, Q.rear);
			break;
		case 'd': // dequeue
			printf("dequeue() : %d\n", dequeue(&Q));
			printf("front : %d, rear : %d\n", Q.front, Q.rear);
			break;
		case 'p': // peek
			printf("peek() : %d\n", peek(&Q));
			printf("front : %d, rear : %d\n", Q.front, Q.rear);
		}
	}


	return 0;
}

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


void init(QueueType *q)
{
	q->front = 0;
	q->rear = 0;
	printf("init front = 0, rear = 0\n");
}

int is_empty(QueueType *q)
{
	//front와 rear가 같으면 empty
	return q->front == q->rear;
}

int is_full(QueueType *q)
{
	//rear의 값을 1 증가시킨 뒤에 % 연산을 했는데 front와 같으면 1 아니면 0을 반환
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front) ? 1 : 0;
}

void enqueue(QueueType *q, element item)
{
	//꽉찼을시 에러메세지 출력
	if (is_full(q))
		error("Queue is full");

	//최대 사이즈로 % 연산을 하는 이유는 rear가 마지막 index일때 0으로 넘어가기 위해서
	q->rear = (++q->rear) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q)
{
	//비어있을 시 에러
	if (is_empty(q))
		error("Queue is empty");

	//front를 1 증가시킨 뒤 그곳에 있는 값 반환
	q->front = (++q->front) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

element peek(QueueType *q)
{		
	if (is_empty(q))
		error("Queue is empty");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}
