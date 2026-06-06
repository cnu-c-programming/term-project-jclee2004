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

Student * find(Student ** head, int id) {
    Student * curr = *head;

    while(curr != NULL) {
        if(curr-> id == id) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
} 

void update(Student ** head, int id, int score) {
    Student * curr = *head;
    
    while(curr!= NULL) {
        // curr->id == id ? curr->score = score; return; : curr = curr->next;
        // 위가 멋있는데.. body 안에 ; 콜론 못 넣는다함.
        if(curr->id == id) {
            curr->score = score;
            return;
        }
        curr = curr->next;
    }
}

void free_student(Student ** head) {
    Student * prev = NULL;
    Student * curr = *head;
    while(curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    *head = NULL;
    prev = NULL;
    curr = NULL;
}