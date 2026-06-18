#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

extern const char * csv_path;
extern int is_reload;
extern int is_save;

int reload(Student **head, const char * filename) {
    free_student(head);
    int count = 0;

    FILE * fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("Error: fail to load the file.");
        return 0;
    }

    char buffer[500];

    if (fgets(buffer,sizeof(buffer),fp) == NULL) {
        printf("Error : invalid header. check the file.");
        fclose(fp);
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

    is_save = 1;

    if(is_reload==1) printf("Reloaded %d students from %s.\n",count,csv_path);
    else printf("Loaded %d students from %s.\n",count,csv_path);
    return count;
}

int save(Student * head, const char * filename) {
    int count = 0;
    
    FILE * fp = fopen(filename,"w");
    if(fp == NULL) {
        printf("Error: save fail.");
        return 0;
    }
    fprintf(fp,"id,name,score\n");
    
    Student * curr = head;
    while(curr != NULL) {
        fprintf(fp,"%d,%s,%d\n",curr->id,curr->name,curr->score);
        count++;
        curr = curr->next;
    }
    fclose(fp);
    
    is_save = 1;
    
    printf("Saved %d students to %s.\n",count,csv_path);
    if(count==0) return 1;
    return count;
}