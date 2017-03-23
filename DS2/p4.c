#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

void init(StackType *s)
{
	s->top = -1;
}

int is_full(StackType *s)
{
	if (s->top == MAX_STACK_SIZE - 1) {
		
		return 1;
	}
	return 0;
}

int is_empty(StackType *s)
{
	if (s->top == -1) {
		return 1;
	}
	return 0;
}
void push(StackType *s, element item)
{
	if (is_full(s)) {
		printf("Stack is full\n");
		return;
	}
	s->top++;
	s->stack[s->top] = item;
}

element pop(StackType *s)
{
	if (is_empty(s)) {
		printf("Stack is empty\n");
        exit(1);
		
	}
	int item = s->stack[s->top];
	s->top--;
	return item;
}

element peek(StackType *s)
{
	if (is_empty(s)) {
		printf("stack empty\n");
		exit(1);
	}

	return s->stack[s->top];
}

int main(void)
{
	StackType s;
	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", peek(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", is_empty(&s));
}
