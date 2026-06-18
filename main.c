const char * csv_path;
int is_reload=0;
int is_save=1;
#ifdef ADMIN_MODE 
    #define MODE "admin> "

#elif defined(CLIENT_MODE)
    #define MODE "client> "
#else
    #error "Define either -DADMIN_MODE or -DCLIENT_MODE when compiling."
#endif

// 아래가 그냥 주석인가? Swagger 쓸 때랑 비슷하게 생겼는데
/*
 *
 * Build:
 *   make admin   →  admin_shell  (compiled with -DADMIN_MODE)
 *   make client  →  client_shell (compiled with -DCLIENT_MODE)
 *
 * Usage:
 *   ./admin_shell [students.csv]
 *   ./admin_shell -f commands.txt [students.csv]
 *   ./client_shell [students.csv]
 *   ./client_shell -f commands.txt [students.csv]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "file_io.h"
#include "command.h"

void run_shell(const char *csv_path)
{    
    char input[100];
    Student *head = NULL;
    reload(&head, (char *)csv_path);
    printf("\n");
    is_reload = 1;

    while (1)
    {
        printf("%s", MODE);
        if (fgets(input, 100, stdin)==NULL) break;

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            if(is_save == 0) {
                printf("Waring. You din't save the process.\n");
                is_save=1;
            }
            else break;
        }
        if(cmd_process(&head, input) != 0) printf("\n");
        printf("\n");
    }
    free_student(&head);
    printf("Goodbye.\n");
}

void run_command_file(const char *cmd_file, const char *csv_path)
{
    char input[100];
    Student *head = NULL;

    reload(&head, (char *)csv_path);
    printf("\n");
    is_reload = 1;

    FILE *fp = fopen(cmd_file, "r");
    if (fp == NULL)
    {
        printf("Error: failed to load the command file.\n");
        return;
    }
    
    int count = 0;
    
    while (fgets(input, sizeof(input), fp) != NULL)
    {
        input[strcspn(input, "\n")] = 0;
        if (input[0] == '\0' || input[0] == '#') {
            continue; 
        }
        printf("[command file:%d] %s\n",++count,input);

        //보너스 기능 구현

        if (strcmp(input, "exit") == 0) {
            if(is_save == 0) {
                printf("Waring. You din't save the process.\n");
                is_save=1;
            }
            else break;
        }
        if(cmd_process(&head, input) != 0) {
            printf(" Skipped line %d.\n",count);
        }
        printf("\n");
    }
    free_student(&head);
    fclose(fp);
    printf("Goodbye.\n");
    //보고서 작성 시 유의, 커맨드 파일 읽고 끝냄
}

int main(int argc, char *argv[])
{
    #ifdef ADMIN_MODE
    printf("[Admin Program]\n");
    #elif defined CLIENT_MODE
    printf("[Client Program]\n");
    #endif
    // const char *csv_path = NULL; // Default 삭제하고 NULL로, 조건에 무조건 파일 쓰고, 없으면 사용법 출력이였음.
    const char *cmd_file = NULL; /* -f <file> argument */

    /* TODO: Parse command-line arguments.
     *   Supported flags:
     *     -f <file>   run commands from <file> instead of stdin
     *   Remaining positional argument (if any): path to students CSV.
     *
     *   Example parsing skeleton:
     *
     *   for (int i = 1; i < argc; i++) {
     *       if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
     *           cmd_file = argv[++i];
     *       } else {
     *           csv_path = argv[i];
     *       }
     *   }
     */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {                         // i+1... -> -f 까지만 치고 뒤에 입력안했을 경우의 대비
            cmd_file = argv[++i]; // -f 뒤에 오면 명령어 파일이니 이를 cmd file 변수로 연결
        }
        else
        {
            csv_path = argv[i]; // 파일 이름이 다를수도 있으니, 일단 기본으로 student.csv 받고, 혹시 모르니 재할당
        }
    }

    if (csv_path == NULL)
    {
        printf("Usage: %s <csv_file> [-f command_file]\n", argv[0]);
        return 1;
    }
    /* Client shell: supports find, list, help, exit  (read-only) */
    if (cmd_file)
    {
        run_command_file(cmd_file, csv_path);
    }
    else
    {
        run_shell(csv_path);
    }

    return 0;
}
