// 파일 입출력 배운거 여기서 쓰면 될 듯함
// CSV 파일 불러서 write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_io.h>

int load(Student **head, char * filename) {
    int count = 0;

    FILE * fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("파일 읽기 실패");
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

}