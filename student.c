#include <stdio.h>

extern char * student_name;
extern int student_score;

int main() {
    typedef struct Student {
    int id;
    char name[32];
    int score;
    struct Student* next;
    } Student;

    return 0;
}