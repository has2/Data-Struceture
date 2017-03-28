#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef struct ElementType {
	int key;
	float value;
}ElementType;
struct Node {
	ElementType element;
	Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int isLast(Position P, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
Position Find(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
void PrintList(List L);

int main(int argc, char *argv[]) {
	char command;
	int key1, key2;
	FILE *input;
	ElementType in;
	Position header = NULL;
	Position tmp = NULL;
	if (argc == 1)
		input = fopen("input.txt", "r");
	else
		input = fopen(argv[1], "r");
	header = MakeEmpty(header);
	while (1) {
		command = fgetc(input);
		if (feof(input)) break;
		switch (command) {
		case 'i':
			fscanf(input, "%d %d", &key1, &key2);
			in.key = key1;
			//duplication check
			tmp = Find(in, header);
			if (tmp != NULL) {
				printf("There already is an element with key %d. Insertion failed\n", key1);
				break;
			}

            //hw2
			ElementType k2;
			k2.key = key2;
			tmp = Find(k2, header);
            //hw2

			Insert(in, header, tmp);
			break;
		case 'd':
			fscanf(input, "%d", &key1);
			in.key = key1;
			Delete(in, header);
			break;
		case 'f':
			fscanf(input, "%d", &key1);
			in.key = key1;
			tmp = FindPrevious(in, header);
			if (isLast(tmp, header))
				printf("Could not find %d in the list\n", key1);
			else {
				if (tmp->element.key>0)
					printf("Key of the previous node of %d is %d.\n", key1, tmp->element.key);
				else
					printf("Key of the previous node of %d is header.\n", key1);
			}
			break;
		case 'p':
			PrintList(header);
			break;
		default:
			;
		}
	}
	system("PAUSE");
	DeleteList(header);
	fclose(input);
	return 0;
}

//create header node
List MakeEmpty(List L) {
	L = (List)malloc(sizeof(struct Node));
	L->element.key = -30;
	L->element.value = -30.0;
	L->next = NULL;
	return L;
}
//check the list is empty when L == header(except error case)
int isEmpty(List L) {
	return L->next == NULL;
}

//check the position P is at the last of the list L
int isLast(Position P, List L) {
	Position cur = L;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	return P == cur;
}

//return last position when X is not in L. else, return previous position of element X exist
Position FindPrevious(ElementType X, List L) {
	Position P = NULL;
	P = L;
	while (P->next != NULL && P->next->element.key != X.key) {
		P = P->next;
	}
	return P;
}

//delete whole list
void DeleteList(List L) {
	Position P = NULL, Tmp = NULL;
	P = L->next; /* Header assumed */
	L->next = NULL;
	while (P != NULL)
	{
		Tmp = P->next;
		free(P);
		P = Tmp;
	}
}
//negative will be header
Position Find(ElementType X, List L) {
	Position P = NULL;
	if (X.key<0) return L;
	P = FindPrevious(X, L);
	return P->next;
}

//////////////HW2/////////////////
void Insert(ElementType X, List L, Position P) {
	Position Tmp = NULL;
	//input should be positive integer
	if (X.key<0) {
		printf("Please use positive input. %d cannot be inserted\n", X.key);
		return;
	}

    //hw2
	X.value = 3.14;
    //hw2

	Tmp = (Position)malloc(sizeof(struct Node));
	Tmp->element = X;
	if (P == NULL) {
		printf("Insertion(%d) Failed : cannot find the location to be inserted\n", X.key);
		free(Tmp);
		return;
	}
	Tmp->next = P->next;
	P->next = Tmp;
}


void PrintList(List L) {
	PtrToNode tmp = NULL;
	tmp = L->next;
	if (tmp == NULL) {
		printf("list is empty!\n");
		return;
	}
    
	while (tmp != NULL) {
	    //hw2
        printf("key:%d value:%.3f\t", tmp->element.key, tmp->element.value);
		tmp = tmp->next;
        //hw2
	}
	printf("\n");
}

void Delete(ElementType X, List L) {
	Position P = NULL, Tmp = NULL;

	P = FindPrevious(X, L);
	if (!isLast(P, L)) {
		//hw2
        Tmp = P->next;
		P->next = Tmp->next;
		free(Tmp);
        //hw2
	}
	else {
		printf("Deletion failed : element %d is not in the list\n", X.key);
	}
}

////////////// HW2 ///////////

