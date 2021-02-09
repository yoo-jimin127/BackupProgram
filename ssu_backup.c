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
typedef struct fileInfo {
	char absPath[300]; // 파일의 절대경로를 저장하기 위한 문자열 배열
	int filePeriod; // 해당 파일의 백업 주기
	//char fileOption[30]; //파일의 백업 옵션
}FileInfo;

//파일명으로 연결된 리스트의 노드
typedef struct node {
	char fileName[256]; // 명세 : 백업할 파일명 길이 제한 255bytes
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
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] : %s \n", i, argv[i]);
	}

	printf("argc 개수 : %d\n", argc);

	//main 함수 : 입력받은 경로 존재, 접근 여부 확인 (별도 함수로 처리)
	//제대로 열 수 있으면 경로 프롬프트 실행 함수에 넘겨 백업 프로그램 시작

	return 0;
}
//================================함수 정의부=======================================

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
		linkedList -> tail -> prev -> next = node; //node : 추기, tail->prev : 기존노드
		node -> next = linkedLIst -> tail;

		node -> prev = linkedList -> tail -> prev;
		linkedList -> tail -> prev = node;
	}
	
	linkedList -> fileCnt++; //연결리스트에 저장된 백업해야할 파일의 개수 카운트 ++
}
