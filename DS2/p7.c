#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 10

typedef struct { 
	int key; 
} element; 

typedef struct { 
	element heap[MAX_ELEMENT]; 
	int heap_size; 
} HeapType;

void init(HeapType *h) { 
	h->heap_size = 0; 
	h->heap[0].key = 987654321;
}

void insert_max_heap(HeapType *h, element item) {
	
	int i;

	for (i = ++h->heap_size; h->heap[i / 2].key < item.key; i /= 2)
		h->heap[i].key = h->heap[i / 2].key;

		h->heap[i].key = item.key; 
}

element delete_max_heap(HeapType *h) {
	int parent, child; 
	int i;
	element item, temp; 
	item = h->heap[1]; 
	parent = 1; 
	child = 2; 
	h->heap[parent] = h->heap[h->heap_size--];

	while (child <= h->heap_size) {
		
		if (child<h->heap_size && h->heap[child + 1].key > h->heap[child].key)
			child++;

		if (h->heap[parent].key > h->heap[child].key) break;

		temp = h->heap[parent];
		h->heap[parent] = h->heap[child];
		h->heap[child] = temp;
		parent = child;
		child *= 2;

	}

	return item; 
}

void print_heap(HeapType *h) {
	int i;
	int level = 1;
	printf("\n===================");
	for (i = 1; i <= h->heap_size; i++) {
		if (i == level) {
			printf("\n"); level *= 2;
		}
		printf("\t%d", h->heap[i].key);
	}
	printf("\n===================");
}

int main(void) {
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element d1;
	HeapType heap;
	init(&heap);
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	print_heap(&heap);
	d1 = delete_max_heap(&heap); 
	printf("\n <del. %d > \n", d1.key); 
	print_heap(&heap);
}
