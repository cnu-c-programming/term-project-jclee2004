#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

//구조체 정의는 헤더로 옮기기
//소스코드에서는 순수 동작부만 구현하면 될듯함.

Student * create(int id,char * name,int score) {
    Student * student = malloc(sizeof(Student));
    student->id = id;
    strcpy(student->name,name);
    student->score =score;
    student->next = NULL;
    return student; 
}
// 위 형태 혹시 잘못 기억해서 잘못됐거나, 더 줄일 수도 있으니,
// 내일 복습하고 제대로 한번 보기

void add(Student **head,int id,char * name,int score) {
    Student * new = create(id,name,score);
    Student * curr = * head;
    if(curr == NULL) {
        *head = new;
        return;
    }
    while(curr->next!=NULL) curr = curr->next;
    curr->next = new;
}
//이중 포인터 PDF는 일단 한번 더 보는걸로 살짝 헷갈림
//CBV 떄문에 아마 이렇게 쓰는게 맞긴 할텐데

void delete(Student ** head,int id) {
    Student * prev = NULL;
    Student * curr = *head;
    while(curr != NULL) {
        if(id == curr->id) {
            if(prev == NULL) {
                *head = curr->next;
                free(curr);
                return;
            }
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}