#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include <string.h>
#define MAX_STACK_SIZE 20
typedef long long element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;
char tmp[MAX_STACK_SIZE] = "";

// 스택 초기화 함수
void init(StackType *s) {
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType *s) {
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType *s, element item) {
	if (is_full(s)) {
		fprintf(stderr, " \n");
		return;
	}
	else s->stack[++(s->top)] = item;

}
// 삭제함수
element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// 피크함수
element peek(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[s->top];
}

// 연산자의 우선순위를 반환한다.
int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

//infix to postfix
void infix_to_postfix(char infix[], char postfix[])
{
	StackType s;
	char x, token;
	int i, j;    //i-index of infix, j-index of postfix
	init(&s);
	j = 0;

	for (i = 0; infix[i] != '\0'; i++)
	{
		token = infix[i];
		if (isalnum(token))
			postfix[j++] = token;
		else
			if (token == '(')
				push(&s, '(');
			else
				if (token == ')')
					while ((x = pop(&s)) != '(')
						postfix[j++] = x;
				else
				{
					while (!is_empty(&s) && (prec(token) <= prec(peek(&s))))
					{
						x = pop(&s);
						postfix[j++] = x;
					}
					push(&s, token);
				}
	}

	while (!is_empty(&s))
	{
		x = pop(&s);
		postfix[j++] = x;
	}

	postfix[j] = '\0';
	printf("\npostfix_to_infix expression: %s", postfix);
}

char* postfix_to_infix(char expression[])
{
	printf("\ninfix_to_postfix expression: ");
	/* fill in the blank */
	StackType s;
	init(&s);
	char token;
	char* res;	// infix로 변환된 문자열
	element oper1, oper2; 
	int len, i;

	// 문자열의 처음부터 끝까지 
	for (i = 0; expression[i] != '\0'; i++) {
		token = expression[i];

		// token이 operand일 때 
		if (isalnum(token)) {
			push(&s, token - '0'); // stack에 숫자로 변형해서 push
		}

		// token이 operator일 때
		// stack에서 pop한 operand1,operand2 사이에 operator 넣어주고 다시 stack에 넣어줌
		else {

			char* tmp = (char*)malloc(sizeof(char) * 42); // "{operand1}{operator}{operand2}" 문자열을 저장하는 공간

			tmp[0] = '(';  tmp[1] = '\0'; // 앞쪽에 여는 괄호를 넣어줌

			oper2 = (element)pop(&s);
			oper1 = (element)pop(&s);

			// oper1이 1~9까지의 숫자가 아니라 조합된 문자열이라면 tmp의 주소값을 것이므로 1보다 작거나 9보다 큼
			if (oper1 < 1 || oper1 > 9){
				strcat(tmp, (char*)oper1); // 여는 괄호 뒤에 oper1을 이어줌
            }
                

			// oper1이 1~9까지의 숫자일 경우
			else {
				tmp[1] = oper1 + '0'; // 문자로 변환
				tmp[2] = '\0';
			}

			len = strlen(tmp);
			// operator 이어붙혀줌
			tmp[len] = token;
			tmp[len + 1] = '\0';

			// oper2가 1~9까지의 숫자가 아니라 조합된 문자열이라면 tmp의 주소값을 것이므로 1보다 작거나 9보다 큼
			if (oper2 < 1 || oper2 > 10)
				strcat(tmp, (char*)oper2); // oper2를 operator 뒤에 붙혀줌

			// oper2가 1~9까지의 숫자일 경우
			else {
				len = strlen(tmp);
				tmp[len] = oper2 + '0'; // 문자로 변환 뒤 붙혀줌
				tmp[len + 1] = '\0';
			}

			len = strlen(tmp);	
			tmp[len] = ')'; tmp[len + 1] = '\0'; // 닫는 괄호

			push(&s, (element)tmp); // stack에 push
		}

	}
	res = (char*)pop(&s);
	printf("%s\n", res);
	return res;
}

element postfixEval(char exp[])
{
	/* fill in the blank */
	StackType s; //연산에 이용할 stack
	init(&s);
	char token;
	element res, oper1, oper2;

	int i;

	//문자열의 처음부터 끝까지 
	for (i = 0; exp[i] != '\0'; i++) {
		token = exp[i];

		// token이 operand일 때 
		if (isalnum(token)) {
			push(&s, token - '0'); // stack에 숫자로 변형해서 push
		}

		// token이 operator일 때 
		else {
			oper2 = pop(&s); // operand2
			oper1 = pop(&s); // operand1

			// stack에서 pop한 operand 두개를 operator에 맞는 연산
			switch (token) {
			case '+':
				res = oper1 + oper2; 
				break;
			case '-':
				res = oper1 - oper2;
				break;
			case '*':
				res = oper1 * oper2;
				break;
			case '/':
				res = oper1 / oper2;
			}
			// 연산 결과를 다시 push
			push(&s, res);
		}
	}

	return pop(&s);
}

int main() {

	FILE *f;
	char postfix[30];
	char* tmp = (char*)malloc(sizeof(char) * 20);

	f = fopen("input1.txt", "r");
	fscanf(f, "%s", tmp);
	infix_to_postfix(tmp, postfix);
	printf("\neval: %lld \n", postfixEval(postfix));

	f = fopen("input2.txt", "r");
	fscanf(f, "%s", tmp);
	postfix_to_infix(tmp);
	printf("eval: %lld \n", postfixEval(tmp));

	return 0;
}
