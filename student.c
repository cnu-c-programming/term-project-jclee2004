#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

extern int is_save;

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
    while(curr->next!=NULL) {
        curr = curr->next;
    }
    curr->next = new;
    is_save=0;
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
    is_save=0;
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
        if(curr->id == id) {
            curr->score = score;
            return;
        }
        curr = curr->next;
    }
    is_save=0;
}

void list(Student ** head) {
    Student * curr = *head;
    printf("%-5s %-10s %-10s\n","ID","Name","Score");
    while(curr != NULL) {
        printf("%-5d %-10s %-10d\n",curr->id,curr->name,curr->score);
        curr=curr->next;
    }
}

void stats(Student ** head) {
    Student * curr = *head;
    int count=0,min=10000,max=-10000,sum=0;
    while(curr != NULL) {
        count++;
        sum += curr->score;
        if(min>curr->score) min=curr->score;
        if(max<curr->score) max=curr->score;
        curr = curr->next;
    }
    printf("Count: %d\nAverage: %.1f\nMax: %d\nMin: %d\n",count,(float)sum/count,max,min);
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

// Node 직접 바꾸려다가 조금 어려워서
// 꼼수같긴 한데 그냥 내부 데이터를 옮기기
void sort_name(Student ** head) {
    Student * curr = *head;
    Student * target;
    while(curr != NULL) {
        target = curr->next;
        while(target != NULL) {
            if(strcmp(curr->name,target->name) > 0) {
                int temp_id= curr->id;
                char temp_name[32];
                strcpy(temp_name,curr->name);
                int temp_score = curr->score;

                curr->id = target->id;
                strcpy(curr->name,target->name);
                curr->score = target->score;

                target->id = temp_id;
                strcpy(target->name,temp_name);
                target->score = temp_score;
            }
            target = target->next;
        }
        curr = curr->next;
    } 
}

void sort_score(Student ** head) {
    Student * curr = *head;
    Student * target;
    while(curr != NULL) {
        target = curr->next;
        while(target != NULL) {
            if(curr->score > target->score) {
                int temp_id= curr->id;
                char temp_name[32];
                strcpy(temp_name,curr->name);
                int temp_score = curr->score;

                curr->id = target->id;
                strcpy(curr->name,target->name);
                curr->score = target->score;

                target->id = temp_id;
                strcpy(target->name,temp_name);
                target->score = temp_score;
            }
            target = target->next;
        }
        curr = curr->next;
    } 
}