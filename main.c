const char * csv_path;

#ifdef ADMIN_MODE // 전처리기 문법인데, 2주 뒤에나 배움. 맨 위 컴파일 옵션에 따라 분기
/* Admin shell: supports add, delete, update, save, load, sort, list, find, help, exit */
    #define MODE "admin> "

#elif defined(CLIENT_MODE)
    #define MODE "client> "
#else
    #error "Define either -DADMIN_MODE or -DCLIENT_MODE when compiling."
#endif

/*
 * main.c  –  Mini Student Shell
 *
 * TODO: Implement admin_shell and client_shell.
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

/* TODO: Add your own header includes here */
/* #include "student.h"  */
/* #include "file_io.h"  */
/* #include "command.h"  */

#include "student.h"
#include "file_io.h"
#include "command.h"

/* ---------------------------------------------------------------
 * TODO: Implement the interactive shell loop.
 *   - Print a prompt and read a line from stdin.
 *   - Parse the line into a command and arguments.
 *   - Dispatch to the appropriate handler function.
 *   - Loop until the user types "exit" or EOF.
 * --------------------------------------------------------------- */
void run_shell(const char *csv_path)
{
    char input[100];
    Student *head = NULL;
    int stu_num = load(&head, (char *)csv_path);

#ifdef ADMIN_MODE
    printf("[Admin Program]\n");
    printf("Loaded %d students from %s\n",stu_num,csv_path);
#elif defined CLIENT_MODE
    printf("[CLIENT Program]\n");
    printf("Loaded %d students from %s\n",stu_num,csv_path);
#endif
    
    while (1)
    {
        printf("%s", MODE);
        fgets(input, 100, stdin);

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0)
            break;
        cmd_process(&head, input);
    }
    free_student(&head);
}

/* ---------------------------------------------------------------
 * TODO: Implement batch mode – read commands from a file.
 *   - Open cmd_file for reading.
 *   - Execute each line as a command (same logic as run_shell).
 *   - Close the file when done.
 * --------------------------------------------------------------- */
void run_command_file(const char *cmd_file, const char *csv_path)
{
    char input[100];
    Student *head = NULL;

    load(&head, (char *)csv_path);

    FILE *fp = fopen(cmd_file, "r");
    if (fp == NULL)
    {
        printf("Error 파일 읽기 실패\n");
        return;
    }

    while (fgets(input, sizeof(input), fp) != NULL)
    {
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0)
            break;
        cmd_process(&head, input);
    }
    free_student(&head);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    //전역으로 넘겨서 save,load 명령어 인자로 넘겨야할듯함,
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
