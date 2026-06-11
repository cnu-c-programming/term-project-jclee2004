# Mini Student Shell

C 언어로 구현한 학생 데이터 관리 셸 프로그램. 연결 리스트로 학생 정보를 관리하고 CSV 파일에 저장합니다.

## 빌드

```bash
make admin    # admin_shell 빌드 (-DADMIN_MODE)
make client   # client_shell 빌드 (-DCLIENT_MODE)
make all      # 두 프로그램 모두 빌드
make clean    # 빌드 파일 삭제
```

## 실행

```bash
./admin_shell students.csv
./client_shell students.csv

# 명령어 파일 사용 (-f 옵션)
./admin_shell students.csv -f commands.txt
./client_shell students.csv -f commands.txt
```

- CSV 파일이 없으면 빈 목록으로 시작합니다.
- `-f` 명령어 파일 처리 후 `exit` 없이 끝나면 즉시 종료합니다.
- 명세 별로  `-f command.txt students.csv` 혹은 
- `students.csv -f command.txt ` 로 나뉘어서 둘 다 가능하게
- 구현하였습니다.
- -f 뒤에 전달한 명령어 파일을 찾을 수 없거나 여는데 실패한 경우 에러 메시지를 띄운 후 즉시 종료합니다.
- ./admin_shell 처럼 명령어만 입력시, 자세한 사용법에 대해 출력 후 종료합니다.

## 명령어

| 명령어 | Admin | Client | 설명 |
|--------|-------|--------|------|
| `list` | O | O | 전체 학생 목록 출력 |
| `find <id>` | O | O | ID로 학생 검색 |
| `help` | O | O | 명령어 도움말 |
| `exit` | O | O | 프로그램 종료 |
| `reload` | O | O | CSV에서 다시 불러오기 |
| `save` | O | X | CSV에 저장 |
| `add <id> <name> <score>` | O | X | 학생 추가 |
| `delete <id>` | O | X | 학생 삭제 |
| `update <id> <score>` | O | X | 점수 수정 |
| `stats` | O | O | 학생 정보 요약 |
| `clear` | O | O | 터미널 창 청소 |

## CSV 형식

```
id,name,score
1,Alice,90
2,Bob,85
3,Charlie,95
```

- `id`: 양의 정수, 고유값
- `name`: 공백·쉼표 없음, 최대 99자
- `score`: 0~100 정수

## 명령어 파일 형식

- 한 줄에 하나의 명령어
- `#`으로 시작하는 주석줄 또는 빈 줄은 무시
- 명령어 실행 시 `[command file:N] (실행 명령어)` 형태로 줄 번호 출력
- 오류 발생 시 해당 줄 건너뛰고 다음 명령어 계속 실행

```
# 예시 commands.txt
list
add 4 David 88
update 99 70
find 4
save
exit
```

## 파일 구조

```
student/
├── main.c       - 프로그램 진입점. 매크로/커맨더/쉘 진입 분기
├── Makefile     - 빌드 자동화
├── grader.py    - 제출 전 기능 확인용 채점 스크립트
├── grader.md    - grader 사용법
├── command.c    - 사용자 명령어와 실제 명령어 구현부 매핑
├── command.h    - main.c에서 명령어 전달시 사용할 함수 제공
├── file_io.c    - 파일 불러오기/저장 함수 구현부
├── file_io.h    - 다른 파일에서 쓸 수 있도록 소스코드 함수 선언
├── student.c    - "학생" 정보 수정 관련 함수 구현부
├── student.h    - 다른 파일에서 쓸 수 있도록 소스코드 함수 선언
├── README       - 사용 명세
└── expected/    - 채점 기준 CSV 파일 모음
```

## 제출 전 기능 확인

```bash
# Linux / macOS
python3 grader.py ./admin_shell ./client_shell students.csv

# Windows (CMD)
grader.bat admin_shell.exe client_shell.exe students.csv

# Windows (PowerShell)
.\grader.ps1 admin_shell.exe client_shell.exe students.csv
```

> 최종 채점에 사용하는 test case는 변경될 수 있습니다.
