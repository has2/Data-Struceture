#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) {t=x; x=y; y=t;}
#define MAX_SIZE 10
#define NAME_SIZE 32

//adjust 함수의 구현은 수업시간에 다루었고 동일한 알로기즘으로 구현되어 있음
void adjust(int heap[], int root, int n)
{
	int rootkey = heap[root]; // root의 key
	int child = 2 * root;	  // left child

	// leaf에 도달할 때까지
	while (child <= n) {
		if ((child < n) && (heap[child]) < heap[child + 1]) child++; // 두 child중 큰 것을 선택
		if (rootkey > heap[child]) break;  
		else {
			heap[child / 2] = heap[child]; // parent로 올려줌
			child *= 2;
		}
	}

	heap[child / 2] = rootkey;

}

void heap_sort(int list[], int n)
{
	//fill in the balnk
	int i,temp;

	// child가 존재하는 모든 node를 순회하면서 adjust
	for (i = n / 2; i > 0; i--)
		adjust(list, i, n);

	// 최댓값(list[1])과 이미 뽑힌 key를 제외한 제일 뒷쪽 key(list[i+1])을 바꿔주고 adjust 하는 과정을 반복 
	for (i = n - 1; i > 0; i--) {
		SWAP(list[1], list[i + 1], temp);
		adjust(list, 1, i);
	}

}

void main()
{
	FILE *f;
	int i;
	int list1[MAX_SIZE+1];
	f = fopen("input2.txt", "r");
	fscanf(f, "%d %d %d %d %d %d %d %d %d %d",
		&list1[1], &list1[2], &list1[3], &list1[4], &list1[5],
		&list1[6], &list1[7], &list1[8], &list1[9], &list1[10]);
	//힙정렬
	heap_sort(list1, MAX_SIZE); /* 선택정렬 호출 */
	printf("heap_sort: \n");
	for (i = 1; i <= MAX_SIZE; i++) printf("%d \t", list1[i]);
	printf("\n");
}
