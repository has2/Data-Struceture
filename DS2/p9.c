#include <stdio.h>
#define MAX_SIZE 100
int n = 9;
int list[MAX_SIZE] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
//9,8,7,6,1,4,3,2,5

void print(int list[], int n) 
{ int i; 
for (i = 0; i<n; i++) 
	printf("%d ", list[i]); 
printf("\n"); 
}

int partition(int v[], int left, int right) {
	int ipivot = (left + right) / 2; //피봇은 선택 
	int store = -1;  //초기화를 위해 임의의 값 -1을 택함. 
	int i = 0;       //루프를 위해 사용한 변수 
	int swap = v[ipivot]; 
	int tmp;
	v[ipivot] = v[right]; 
	v[right] = swap; 
	store = left; 
	for(int i=left;i<right; i++ ) { 
		if (v[i] <= v[right]) { 
			/* fill in the blank */ 
			SWAP(v[i], v[store], tmp);
			store++;
		} 
	} 
	/* fill in the blank */
	SWAP(v[store],v[right], tmp);
	return store; 
}

void quick_sort(int list[], int left, int right) { 
	if (left<right) { 
		/* 리스트에 2개 이상의 레코드가 있을 경우 */ 
		int q = partition(list, left, right);
		print(list, 9); 
		quick_sort(list, left, q - 1); 
		/* 왼쪽 부분리스트를 퀵정렬 */ 
		quick_sort(list, q + 1, right);
		/* 오른쪽 부분리스트를 퀵정렬 */ 
	} 
}

int main()
{
	quick_sort(list, 0, 8);
}


