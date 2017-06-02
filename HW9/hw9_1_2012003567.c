#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x, y, t) {t=x; x=y; y=t;}
#define MAX_SIZE 10
#define NAME_SIZE 32

int tmplist[MAX_SIZE];
/* i는 정렬된 왼쪽리스트에 대한 인덱스
j는 정렬된 오른쪽리스트에 대한 인덱스
k는 정렬될 리스트에 대한 인덱스 */
void merge(int list[], int left, int mid, int right)
{
	int i, j, k;
	i = left;  j = mid + 1;  k = left;

	//fill in the blank
	while (i <= mid && j <= right)	// 왼쪽리스트나 오른쪽 리스트를 전부 복사할 때까지
		tmplist[k++] = (list[i] <= list[j]) ? list[i++] : list[j++]; // 왼쪽 list의 현재 값이 더 작으면왼쪽 list의 현재 값을 복사해주고 i증가, 반대의 경우 오른쪽 리스트를 복사후 j증가

	if (i > mid) memcpy(tmplist + k, list + j, sizeof(int)*(right - j + 1)); // 남은 오른쪽 list의 j부터 right까지를 tmplist의 k부터 복사
	else         memcpy(tmplist + k, list + i, sizeof(int)*(mid - i + 1));   // 남은 왼쪽 list의 i부터 mid까지를 tmplist의 k부터 복사

	memcpy(list + left, tmplist + left, sizeof(int)*(right - left + 1));	 // tmplist의 left부터 right까지를 원본 list에 복사
}

void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left<right) {
		mid = (left + right) / 2;     /* 리스트의 균등 분할 */
		merge_sort(list, left, mid);    /* 부분 리스트 정렬 */
		merge_sort(list, mid + 1, right); /* 부분 리스트 정렬 */
		merge(list, left, mid, right);    /* 합병 */
	}
}

void main()
{
	FILE *f;
	int i;
	int list1[MAX_SIZE];
	f = fopen("input1.txt", "r");
	fscanf(f, "%d %d %d %d %d %d %d %d %d %d",
		&list1[0], &list1[1], &list1[2], &list1[3], &list1[4],
		&list1[5], &list1[6], &list1[7], &list1[8], &list1[9]);

	//합병정렬
	merge_sort(list1, 0, MAX_SIZE - 1); /* 선택정렬 호출 */
	printf("merge_sort: \n");
	for (i = 0; i<MAX_SIZE; i++) printf("%d \t", list1[i]);
	fclose(f);
	printf("\n");
}
