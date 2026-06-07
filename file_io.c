#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

extern const char * csv_path;

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

#ifdef ADMIN_MODE
    printf("[Admin Program]\n");
#elif defined CLIENT_MODE
    printf("[CLIENT Program]\n");
#endif

#ifdef RELOAD
    printf("Reloaded %d students from %s.",count,csv_path);
#else
    printf("Loaded %d students from %s.",count,csv_path);
#endif
    return count;
}

int save(Student * head, const char * filename) {
    int count = 0;

    FILE * fp = fopen(filename,"w");
    if(fp == NULL) {
        printf("Error: save fail.");
        return 0;
    }
    fprintf(fp,"id, name, score");

    Student * curr = head;
    while(curr != NULL) {
        fprintf(fp,"%d,%s,%d\n",curr->id,curr->name,curr->score);
        count++;
        curr = curr->next;
    }
    fclose(fp);

    printf("Saved %d students to %s.\n",count,csv_path);
    return count;
}