#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int backup_time;
	int file_size;
	char file_content[9999];

	struct backupNode *next;
	struct backupNode *prev;
}BackupNode;

typedef struct list {
	BackupNode *head;
	BackupNode *tail;
}

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

// make node function
Node *makeNode (char *fileName) {
    Node *newNode; 
        
    newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode -> fileName, fileName);

    newNode -> next = NULL;
    newNode -> prev = NULL;

    return newNode;
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

//add new file into backup list
void addFileToList (char *dirName, Node *node) {
    FILE *fptr;

    fptr = fopen("backupList.list", "a");
    fprintf(fptr, "%s", node -> fileName);

    fclose(fptr);
}

int main (void) {
	 return 0;
}
