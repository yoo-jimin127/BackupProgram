#include <stdio.h> 
#include <stdlib.h> //system() 함수 사용 위한 헤더파일
#include <string.h>
#include <pthread.h> // 스레드 함수 사용 위한 헤더파일
#include <unistd.h> // 표준 심볼 상수 및 자료형 정의 헤더파일
#include <sys/types.h> 
#include <sys/stat.h> // stat 구조체 사용 위한 헤더파일
#include <dirent.h> // 디렉토리 정보 읽어오기 위한 헤더파일

#define MAX_SIZE 99999

/*
typedef struct fileInfo {
   char absPath[256]; // 파일의 절대경로를 저장하기 위한 문자열 배열
   int filePeriod; // 해당 파일의 백업 주기
//char fileOption[30]; //파일의 백업 옵션
}FileInfo; */

//파일명으로 연결된 리스트의 노드
typedef struct node {
    char absPath[256];
    char fileName[256]; // 명세 : 백업할 파일명 길이 제한 255bytes
    int filePeriod; // 해당 파일의 백업 주기

	pid_t pid;
	pthread_t tid;

    struct node *next;
    struct node *prev;
}Node;

/*
typedef struct backupNode {
    pid_t pid;
    pthread_t tid;
    char fileName[256];
    int period;
    int backup_time;
    int file_size;
    char file_content[MAX_SIZE];

    struct backupNode *next;
    struct backupNode *prev;
}BackupNode;
*/

//백업할 파일들을 연결해놓은 이중 연결리스트 (백업리스트)
typedef struct linkedList {
    Node *head; //연결리스트의 head 노드
    Node *tail; //연결리스트의 tail 노드
    int fileCnt; //백업할 파일들의 개수를 세기위한 카운트
}LinkedList;

/*
typedef struct backupContentList {
    BackupNode *head;
    BackupNode *tail;
    int backup_perform_cnt;
}BackupContentList;
*/

//================================함수 선언부=======================================
void initList (LinkedList *linkedList);
Node *makeNode (char *fileName);
Node *findNode (LinkedList *linkedList, char *fileName);
void addNode (LinkedList *linkedList, Node *node);
void removeNode (LinkedList *linkedList, char *fileName);
void addFileToList (char *dirName, Node *node);
void listFunc(LinkedList *linkedList);

char *checkAccessDir(int argc, char **argv);
void printPrompt (char *absPath);
int calcFileCnt (LinkedList *linkedList);
void addFunc(LinkedList *linkedList, char *dirPath, char *fileName, int period);
void removeFunc(LinkedList *linkedList, char *fileName);
void compareFunc(char *fileName1, char *fileName2);
static size_t getFileSize(const char *fileName);
void recoverFunc(LinkedList *linkedList, char *dirName, char *fileName);
void lsFunc();

void write_log(char *msg);

void *thread_function(void *addFile, int period);


