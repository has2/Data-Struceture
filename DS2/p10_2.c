#include <stdio.h> 
#include <stdlib.h>
#define max_vertices 4 
#define max_queue_size 10 

int adj_mat[max_vertices][max_vertices]={ {0,1,0,1}, {1,0,1,1}, {0,1,0,1}, {1,1,1,0} }; 
int visited[max_vertices]; 
int n=4; 
typedef int element; 

typedef struct { 
	element queue[max_queue_size]; 
	int front, rear; 
} queuetype;

void error(char *message)
{
	printf("%s\n", message);
	exit(1);
}
// 초기화 함수
void init(queuetype *q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(queuetype *q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(queuetype *q)
{
	return ((q->rear + 1) % max_queue_size == q->front);
}
// 삽입 함수
void enqueue(queuetype *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % max_queue_size;
	q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(queuetype *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % max_queue_size;
	return q->queue[q->front];
}

void graph_bfs_mat(int v) {
	int w; 
	queuetype q; 
	init(&q); /* 큐 초기화 */ 
	visited[v] = 1; // 정점 v 방문 표시 
	printf("%d ", v); 
	enqueue(&q, v);// 시작 정점을 큐에 저장 
	while(!is_empty(&q)){ 
		//fill in the blank
		v = dequeue(&q);
		for(w=0; w<n; w++){
			// w에 인접한 정점 탐색 
			if( adj_mat[v][w] && !visited[w] ){ 
				//fill in the blank
				enqueue(&q, w);
				visited[w] = 1;
				printf("%d ", w);
			} 
		} 
	} 
}

void main()
{
	graph_bfs_mat(0);
}

