#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "command.h"
#include "file_io.h"

extern int command_count;

//우선 만들어놓은 간단한 명령어만 구성해서
//큰 뼈대를 잡고 나머지 명령어 처리

extern const char * csv_path;

//에러 체킹과 출력 담당을 함수 내부가 아니라
//command 단에서 하는걸로 짜야 나중에 디버깅할 때 편할듯

int add_check(char * args) {
    char * id_s = strtok(args, " ");
    char * name = strtok(NULL, " ");
    char * score_s = strtok(NULL, " ");

    if(id_s==NULL || name == NULL || score_s ==NULL) {
        printf("Error: missing arguments.\n");
        return 1;
    }
    if(!(isdigit(id_s) && isdigit(score_s))) {
        printf("Error: there is non-numeric argument for numeric argument.\n")
        return 1;
    }

    int id = atoi(id_s);
    int score = atoi(score_s);

    if(id == 0 || id<0 || score > 100 || score < 0) {
        printf("Error: id must be over 0 and score must be in the range from 0 to 100.\n")
        return 1;
    }
    return 0;
}

int update_check(char * args) {
    char * id_s = strtok(args, " ");
    char * score_s = strtok(NULL, " ");

    if(id_s==NULL || score_s ==NULL) {
        printf("Error: missing arguments.\n");
        return 1;
    }
    if(!(isdigit(id_s) && isdigit(score_s))) {
        printf("Error: there is non-numeric argument for numeric argument.\n")
        return 1;
    }

    int id = atoi(id_s);
    int score = atoi(score_s);

    if(id == 0 || id<0 || score > 100 || score < 0) {
        printf("Error: id must be over 0 and score must be in the range from 0 to 100.\n")
        return 1;
    }
    return 0;
}

void cmd_add(Student ** head, char * args) {
    if(add_check(args)) return;
    int id,score;
    char name[100];
    sscanf(args,"%d %s %d",&id,name,&score);
    
    add(head,id,name,score);
}

void cmd_delete(Student ** head, char * args) {
    int id=atoi(args);
    //얘는 오류 검사 하는 조건이 없네 일단 보류
    if(find(head,id)==NULL) {
        printf("Error: student not found.\n")
        return;
    }
    delete(head,id);
    printf("Student deleted.\n");
}

void cmd_update(Student ** head, char * args) {
    if(update_check(args)) return;
    int id,score;
    char name[100];

    sscanf(args,"%d %s %d",&id,name,&score);
    if(find(head,id)==NULL) {
        printf("Error: student not found.\n");
        return;
    }
    update(head,id,score);
}

void cmd_find(Student ** head, char * args) {
    int id = atoi(args);
    Student * student = find(head,id);
    if(student != NULL) {
        printf("ID: %d\nName: %s\nScore: %d",student->id,student->name,student->score);
    }
    else {
        printf("Error: student not found.\n");
    }
}

void cmd_save(Student ** head, char * args) {
    (void)args;
    save(*head,csv_path);
}

void cmd_reload(Student ** head, char * args) {
    (void)args;
    reload(head,csv_path);
}

void cmd_list(Student ** head,char * args) {
//정보 없으면 No students found
}


void cmd_stats(Student ** head,char * args) {
//정보 없으면 No student data available
}

void cmd_help(Student ** head,char * args) {
    (void)args;
    (void)head;
    printf("Commands:\n");
    for(int i=0;(long unsigned int)i<sizeof(table)/sizeof(table[0]);i++) {
        printf("%30s %30s\n",h_table[i].fun_args,h_table[i].description);
    }
}

void cmd_clear(Student ** head,char * args) {
    (void)args;
    (void)head;
    printf("\033[2J\033[H");
}

typedef void (*cmd)(Student ** head,char * args);

typedef struct 
{
    char *name;
    cmd function;
}CMD;

typedef struct {
    char * fun_args;
    char * description;
}HELP;

//윗부분만 읽으면서 짰는데..
//아랫부분에 해당 구조체를 예시로 주셨었네...
//하...

#ifdef ADMIN_MODE
CMD table[] = {
    {"add",cmd_add},
    {"delete",cmd_delete},
    {"update",cmd_update},
    {"find",cmd_find},
    {"save",cmd_save},
    {"reload",cmd_reload},
    {"list",cmd_list},
    {"stats",cmd_stats},
    {"clear",cmd_clear},
};

HELP h_table[] = {
    {"save", "Save students to CSV"},
    {"reload", "Reload students from CSV"},
    {"add <id> <name> <score>", "Add a student"},
    {"delete <id>", "Delete a student"},
    {"update <id> <score>", "Update student score"},
    {"find <id>", "Find student by ID"},
    {"list", "List all students"},
    {"stats", "Show statistics"},
    {"clear", "Clear screen"},
    {"exit", "Exit program"}
}

#elif defined CLIENT_MODE
CMD table[] = {
    {"find",cmd_find},
    {"reload",cmd_reload},
    {"list",cmd_list},
    {"stats",cmd_stats},
    {"clear",cmd_clear},
};

HELP h_table[] = {
    {"reload", "Reload students from CSV"},
    {"find <id>", "Find student by ID"},
    {"list", "List all students"},
    {"stats", "Show statistics"},
    {"clear", "Clear screen"},
    {"exit", "Exit program"}
}

#endif

void cmd_process(Student **head, char * input) {
    char * cmd_name = strtok(input," ");
    char * args = strtok(NULL,""); 

    for(int i=0;(long unsigned int)i<sizeof(table)/sizeof(table[0]);i++) {
        if(strcmp(cmd_name,table[i].name)==0) {
            table[i].function(head,args);
            return;
        }
    }
    printf("Unknown command or permission deined.");

}