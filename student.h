#pragma once

typedef struct Student
{
    int id;
    char name[32];
    int score;
    struct Student *next;
} Student;

Student * create(int id,char * name,int score);

void add(Student **head,int id,char * name,int score);
void delete(Student ** head,int id);

Student * find(Student ** head, int id);

void update(Student ** head, int id, int score);

void free_student(Student ** head);

void list(Student ** head);

void stats(Student ** head);

void sort_name(Student ** head);

void sort_score(Student ** head);
