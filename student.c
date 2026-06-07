#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

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
        printf("Student added.\n");
        return;
    }
    while(curr->next!=NULL) {
        curr = curr->next;
    }
    curr->next = new;
    printf("Student added.\n");
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
        if(curr->id == id) {
            curr->score = score;
            return;
        }
        curr = curr->next;
    }
}

void list(Student ** head) {
    Student * curr = *head;
    printf("%5s %10s %10s","id","name","score\n");
    while(curr != NULL) {
        printf("%10d %10s %10d\n",curr->id,curr->name,curr->score);
        curr=curr->next;
    }
}

void stats(Student ** head) {
    Student * curr = *head;
    int count=0,min=10000,max=-10000,sum=0;
    while(curr != NULL) {
        count++;
        sum += curr->score;
        if(min>curr->score) curr->score = min;
        if(max<curr->score) curr->score = max;
        curr = curr->next;
    }
    printf("Count: %d\nAverage: %f\nMax: %d\nMin: %d\n",count,(float)sum/count,max,min);
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