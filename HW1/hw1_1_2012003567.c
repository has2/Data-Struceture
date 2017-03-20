#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 31
//구조체 선언
typedef struct studentT {
	char *name;
	int literature;
	int math;
	int science;
} studentT;

int main(int argc, char* argv[])
{
	int N;
	studentT* list = NULL; // student 구조체 배열을 저장하는 구조체 포인터 선언
	FILE *fp_input; // 입력 파일 포인터 선언 및 초기화
	fp_input = fopen(argv[1], "r");
	FILE *fp_output; // 입력 파일 포인터 선언 및 초기화
	fp_output = fopen(argv[2], "w");
	
	fscanf(fp_input, "%d",&N); //학생의 숫자를 받아옴
	list = (studentT*)malloc(sizeof(studentT)*N); //학생의 수만큼 구조체를 할당
    // 학생의 이름을 30자만큼 할당
	for (int i = 0; i < N; i++) {
		list[i].name = (char*)malloc(sizeof(char)*MAX_LEN);
	}

    //파일로부터 학생의 성적 정보를 읽어와서 구조체에 저장
	for (int i = 0; i < N; i++) {
		fscanf(fp_input, "%s %d %d %d", list[i].name, &list[i].literature, &list[i].math, &list[i].science);
	}

	fprintf(fp_output, "Name\tLiterature\tMath\tScience\tAve\n");
    
    //list 의 정보를 파일에 출력함
	for (int i = 0; i < N; i++) {
        float avg =(float) (list[i].literature+list[i].math+list[i].science)/3;
		fprintf(fp_output, "%s\t    %d\t\t %d\t   %d    %.2f\n", list[i].name,list[i].literature, list[i].math, list[i].science,avg);
	}
    
    //메모리를 해제
    for(int i=0;i<N;i++){
        free(list[i].name);
    }
    free(list);
}
