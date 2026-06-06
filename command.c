#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "file_io.h"

//우선 만들어놓은 간단한 명령어만 구성해서
//큰 뼈대를 잡고 나머지 명령어 처리

void cmd_add(Student ** head, char *args) {
    int id,score;
    char name[100];

    sscanf(args,"%d %s %d",&id,name,&score);
    add(head,id,name,score);
}

void cmd_delete(Student ** head, char * args) {
    int id=atoi(args);
    delete(head,id);
}

void cmd_update(Student ** head, char * args) {
    int id,score;
    char name[100];

    sscanf(args,"%d %s %d",&id,name,&score);
    update(head,id,score);
}

void cmd_find(Student ** head, char * args) {
    int id = atoi(args);
    Student * student = find(head,id);
    if(student != NULL) {
        printf("%d %s %d",student->id,student->name,student->score);
    }
    else {
        printf("No student");
    }
}


void cmd_save(Student ** head, char * args) {
    save(*head,args);
}

void cmd_load(Student ** head, char * args) {
    load(head,args);
}

typedef void (*cmd)(Student ** head,char * args);

typedef struct 
{
    char *name;
    cmd function;
}CMD;

CMD table[] = {
    {"add",cmd_add},
    {"delete",cmd_delete},
    {"update",cmd_update},
    {"find",cmd_find},
    {"save",cmd_save},
    {"load",cmd_load},
};

void cmd_process(Student **head, char * input) {
    char * cmd_name = strtok(input," ");
    char * args = strtok(NULL,"");

    if (cmd_name == NULL) {
        printf("명령어를 포함하여 다시 입력하십시오.\n");
        return;
    } 

    for(int i=0;(long unsigned int)i<sizeof(table)/sizeof(table[0]);i++) {
        if(strcmp(cmd_name,table[i].name)==0) {
            table[i].function(head,args);
            return;
        }
    }
    printf("알 수 없는 명령어 : %s",cmd_name);

}