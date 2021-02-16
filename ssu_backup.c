#include <stdio.h> 
#include <stdlib.h> //system() 함수 사용 위한 헤더파일
#include <string.h>
#include <pthread.h> // 스레드 함수 사용 위한 헤더파일
#include <unistd.h> // 표준 심볼 상수 및 자료형 정의 헤더파일
#include <sys/types.h> 
#include <sys/stat.h> // stat 구조체 사용 위한 헤더파일
#include <dirent.h> // 디렉토리 정보 읽어오기 위한 헤더파일

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //쓰레드 초기화
int ncount; //쓰레드간 공유되는 자원

//==========================구조체 선언부================================

//백업할 파일의 정보를 저장할 구조체
/*
typedef struct fileInfo {
	char absPath[256]; // 파일의 절대경로를 저장하기 위한 문자열 배열
	int filePeriod; // 해당 파일의 백업 주기
	//char fileOption[30]; //파일의 백업 옵션
}FileInfo; */

//파일명으로 연결된 리스트의 노드
typedef struct node {
	char fileName[256]; // 명세 : 백업할 파일명 길이 제한 255bytes
	int filePeriod; // 해당 파일의 백업 주기

	struct node *next;
	struct node *prev;
}Node;

//백업할 파일들을 연결해놓은 이중 연결리스트 (백업리스트)
typedef struct linkedList {
	Node *head; //연결리스트의 head 노드
	Node *tail; //연결리스트의 tail 노드
	int fileCnt; //백업할 파일들의 개수를 세기위한 카운트
}LinkedList;

//================================함수 선언부=======================================


int main (int argc, char* argv[]) {
	char *backupdir; //백업디렉토리를 생성할 절대경로 값 저장 위한 문자열

	backupdir = (char *)malloc(sizeof(char) * 256); //절대경로 저장을 위해 메모리 동적할당

	/* for (int i = 0; i < argc; i++) {
		printf("argv[%d] : %s \n", i, argv[i]);
	}

	printf("argc 개수 : %d\n", argc); */

	//main 함수 : 입력받은 경로 존재, 접근 여부 확인 (별도 함수로 처리)
	backupdir = checkAccessDir(argc, argv);

	//제대로 열 수 있으면 경로 프롬프트 실행 함수에 넘겨 백업 프로그램 시작
	printPrompt(backupdir);

	return 0;
}

//================================연결리스트 관련 함수 정의부=======================================

// 연결리스트 초기화 함수
void initList (LinkedList *linkedList) {
	linkedList -> head = (Node*)malloc(sizeof(Node));
	linkedList -> tail = (Node*)malloc(sizeof(Node)); //연결리스트의 head, tail에 동적할당

	linkedList -> head -> next = linkedList -> tail;
	linkedList -> tail -> prev = linkedList -> head; //head와 tail 연결

	linkedList -> tail -> next = NULL;
	linkedList -> head -> prev = NULL;//tail->next와 head->prev 초기화

	linkedList -> fileCnt = 0; //백업할 파일 개수 카운트 0으로 초기화
}

//연결리스트에서 노드 찾는 함수
Node *findNode (LinkedList *linkedList, char *fileName) {
	Node *curr; //리스트 순회하며 찾는 노드와 같은 노드 반환

	curr = linkedList -> head -> next; //curr노드 : 연결리스트의 head의 next위치로 초기화

	while (curr -> next != NULL) { //curr의 next가 연결리스트의 tail이 될 때까지 순회
		if (!strcmp(curr->fileName, fileName)) { //비교하여 같으면 curr 리턴
			return curr;
		}

		curr = curr -> next;
	}
}

//연결리스트에 노드를 추가하는 함수
void addNode (LinkedList *linkedList, Node *node) {
	//리스트가 비어있는 경우
	if (linkedList -> head -> next == linkedList -> tail) { //head -> next  == tail
		linkedList -> head -> next = node; //head --> node
		node -> next = linkedList -> tail; //노드 next = tail
		node -> prev = linkedList -> hear; //노드 prev = head
		linkedList -> tail -> prev = node;
	}

	//리스트가 비어있지 않은 경우
	else {
		linkedList -> tail -> prev -> next = node; //node : 추가, tail->prev : 기존노드
		node -> next = linkedLIst -> tail;

		node -> prev = linkedList -> tail -> prev;
		linkedList -> tail -> prev = node;
	}
	
	linkedList -> fileCnt++; //연결리스트에 저장된 백업해야할 파일의 개수 카운트 ++
}

//연결리스트에 노드를 삭제하는 함수
void removeNode (LinkedList *linkedList, char *fileName) {
	Node *curr; //리스트를 순회하며 찾는 노드와 같은 노드 삭제

	curr = linkedList -> head -> next; // curr노드의 위치를 head 노드의 next 위치로 초기화시키는 작업
	
	while (curr -> next != NULL) {
		if (!strcmp(curr -> fileName, fileName)) {
			curr -> prev -> next = curr -> next; //curr의 이전노드의 next를 curr의 다음 노드에 연결
			curr -> next -> prev = curr -> prev; //curr의 다음노드의 prev를 curr의 이전 노드에 연결
		
			linkedList -> fileCnt--; //연결리스트에 연결되어있는 노드의 수 -1
		}

		curr = curr -> next;
	} 
}

// list 기능을 위해 모든 백업 리스트를 출력하는 함수
void printBackupList(LinkedList *linkedList) {
	Node *curr;

	curr = linkedList -> head -> next; //curr 노드 초기화
	
	while (curr -> next != NULL) {
		printf("%s \t %d\n", curr -> fileName, curr -> filePeriod);

		curr = curr -> next;
	}
}

//================================디렉토리 관련 함수 정의부===================================

//main에서 인자로 입력받은 절대경로의 접근 권한 확인 함수
char *checkAccessDir(int argc, char **argv) {
	char *backupdir; //반환할 경로 저장할 배열
	struct dirent dir; //dirent 구조체
	struct stat buf; //stat 구조체
	DIR *dirptr; //dirent 포인터
	
	backupdir = (char *)malloc(sizeof(char) * 256); //문자열배열 메모리 동적할당
	int mode = R_OK & W_OK; // 읽기, 쓰기 가능

	//접근 권한 확인 작업 (인자 2개 넘겨받을 때)
	if (argc == 2) {
		// 성공적으로 열리면
		if (access(argv[1], mode) == 0) {
			backupdir = argv[1]; //backypdir에 argv[1] 넣어 리턴
			return backupdir;
		}
		
		// 성공적으로 열리지 않으면 (접근 권한 X or 찾을 수 X)
		else {
			printf("Usage : ./ssu_backup <dirname>\n");
		}

	//인자의 개수가 없을 경우
	else {
		if (argc == 1) {
			//mkdir() 함수로 opendir() 이후 현재 작업 디렉토리에 파일 생성
		}
	}


}


//'학번>' 프롬프트를 출력하는 함수
void printPrompt (char *absPath) {
	char userInput[300] = ""; // 사용자로부터 명령어와 filename, period를 입력받기 위한 문자열배열
	char filePath[256] = ""; // 파일의 절대경로 저장 배열
	int period; //파일의 백업주기 저장 변수

	printf("20193017>");
	scanf("%s", userInput);

	//토큰 분리해서 명령어 호출 부분과 파일명, 백업주기 해당 기능 수행에 넘기는 작업 진행
	char *order = strtok(userInput, " "); //공백자 기준으로 문자열 자름

	while (order != NULL) {

		//add <파일명> [백업주기]
		if (!strcpy(order, "add")) {
			filePath = strtok(NULL, " "); //다음 문자열 잘라 filePath에 저장
			period = atoi(strtok(NULL, " ")); // 다음 문자열 잘라 chPeriod에 저장
			
			//add 기능 담당하는 함수에 filepath와 period 인자로 넘겨주기
		}
		
		//remove <파일명>
		else if (!strcpy(order, "remove")) {
			filePath = strtok(NULL, " "); //다음 문자열 잘라 filePath에 저장

			//remove 기능 담당하는 함수에 filepath 넘기기
		}

		//compare <파일명1> <파일명2>
		else if (!strcpy(order, "compare")) {
			filePath = strtok(NULL, " "); //다음 문자열 잘라 filePath에 저장
			char *filePath2 = strtok(NULL, " "); // 다음 문자열 잘라 filePath2에 저장

			//compare 기능 담당하는 함수에 filePath, filePath2 넘기기
		}

		//recover <파일명>
		else if (!strcpy(order, "recover")) {
			filePath = strtok(NULL, " "); //다음 문자열 잘라 filePath에 저장

			//recover 기능 담당하는 함수에 filePath 넘기기
		}

		//list 명령어
		else if (!strcmp(order, "list")) {
			
			//printBackupList(LinkedList);
		}

		//ls 명령어
		else if (!strcmp(order, "ls")) {
			//system("ls");

		}

		//vi 명령어
		else if (!strcmp(order, "vi")) {
			//system("vi");
		}

		//vim 명령어
		else if (!strcmp(order, "vim")) {
			//system("vim");
		}

		//exit 명령어
		else if (!strcmp (order, "exit")) {
			//exit(0);
		}

	}

}

//연결리스트(백업리스트)에 저장되어있는 백업할 파일(노드)의 개수를 세는 함수
int calcFileCnt (LinkedList *linkedList) {
	int cnt = 0; //노드 개수 세는 변수
	DIR *dirptr; //디렉터리형 포인터

	char buf[300] = ""; //작업 디렉토리의 이름 저장하기 위한 배열
	struct dirent *dir; //dirent 구조체

	getcwd(buf, 300); // 현재 작업디렉터리의 이름 size만큼 buf에 복사

	if ((dirptr = opendir(buf)) == NULL) {
		fprintf("stderr", "opendir error\n");

		return -1;
	}

	while ((dir = readdir(dirptr)) != NULL) {
		for (int i = 0; i < strlen(dir -> d_name); i++) {

		//	cnt++; break;
		}

}
