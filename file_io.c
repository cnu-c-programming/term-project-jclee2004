#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

int load(Student **head, const char * filename) {
    int count = 0;

    FILE * fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("파일 읽기 실패\n");
        return 0;
    }

    char buffer[500];

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
    fclose(fp);
    return count;
}

int save(Student * head, const char * filename) {
    int count = 0;

    FILE * fp = fopen(filename,"w");
    if(fp == NULL) {
        printf("저장 실패, 다시 시도해주세요.\n");
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