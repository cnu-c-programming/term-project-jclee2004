// 파일 입출력 배운거 여기서 쓰면 될 듯함
// CSV 파일 불러서 write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

int load(Student **head, char * filename) {
    int count = 0;

    FILE * fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("파일 읽기 실패");
        return 0;
    }

    char buffer[500];
    //fgets가 가장 만만해서 쓰긴했는데
    //여러 함수가 존재했던걸로 기억함.
    //일단 이거 쓰고 가고 텀프랑 무관하게
    //다른 함수도 찾아보면 공부에 도움될듯함.
    if (fgets(buffer,sizeof(buffer),fp) == NULL) {
        fclose(fp);
        printf("Error : Invalid Header. Check the FIle.\n");
        return 0;
    }

    while(fgets(buffer,sizeof(buffer),fp)) {
        int id = atoi(strtok(buffer,","));
        char *name = strtok(NULL,",");
        int score = atoi(strtok(NULL,","));
        count++;

        add(head,id,name,score);
    }
    fclose(fp;)
    return count;
}

//얘는 굳이 이중 포인터 안 써도 될 듯
int save(Student * head, char * filename) {
    int count = 0;

    FILE * fp = fopen(filename,"w");
    if(fp == NULL) {
        printf("저장 실패, 다시 시도해주세요.");
        return 0;
    }
    fprintf(fp,"id, name, score\n");

    Student * curr = head;
    while(curr != NULL) {
        fprintf(fp,"%d,%s,%d\n",curr->id,curr->name,curr->score);
        count++;
        curr = curr->next;
    }

    fclose(fp);
    return count;
}