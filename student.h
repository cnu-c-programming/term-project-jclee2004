#pragma once
//흐흐 배운거 써보기

typedef struct Student
{
    int id;
    char name[32];
    int score;
    struct Student *next;
} Student;
//포맷 기능 쓰니까 위처럼 맞춰줌.
//연구소에서 js 쓸때도 이렇게 중괄호를 넣었는지는 모르겠음
//내 맘에는 안 드네ㅔ

Student * create(int id,char * name,int score);

void add(Student **head,int id,char * name,int score);
void delete(Student ** head,int id);

Student * find(Student ** head, int id);

void update(Student ** head, int id, int score);

void free_student(Student ** head);
