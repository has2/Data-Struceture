#include <stdio.h>
#include <string.h>

void swap(int** a, int** b)
{
	int *temp;
	temp = *b;
	int temp2;
	temp2 = *temp;
	**b = **a;
	**a = temp2;
}


int main(void)
{
	int A, B;
	int *pA, *pB;
	pA = &A; pB = &B;
	scanf("%d%d", &A,&B);
	printf("before : %d,%d\n", *pA, *pB);
	swap(&pA, &pB);
	printf("after  : %d,%d\n", *pA, *pB);
}
