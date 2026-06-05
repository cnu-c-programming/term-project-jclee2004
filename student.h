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

//아마 여기서 함수 선언만 해서 가져와서
//main으로 넘겨서 main 구조 그때까서 조금 더 생각하면 될 듯
//일단 소스코드 먼저 짜자!


