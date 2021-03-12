#include "backupProgram.h"

#define MAX_SIZE 999 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //쓰레드 초기화
int ncount; //쓰레드간 공유되는 자원
int result; // pthread_join시 return값 저장하는 변수

pthread_t p_thread[MAX_SIZE]; //스레드 식별자

//================================함수 선언부=======================================

int main (int argc, char* argv[]) {
	char *backupdir; //백업디렉토리를 생성할 절대경로 값 저장 위한 문자열

	backupdir = (char *)malloc(sizeof(char) * 256); //절대경로 저장을 위해 메모리 동적할당

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

// 노드 생성 함수
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

	return NULL;
}

//연결리스트에 노드를 추가하는 함수
void addNode (LinkedList *linkedList, Node *node) {
	//리스트가 비어있는 경우
	if (linkedList -> head -> next == linkedList -> tail) { //head -> next  == tail
		linkedList -> head -> next = node; //head --> node
		node -> next = linkedList -> tail; //노드 next = tail
		node -> prev = linkedList -> head; //노드 prev = head
		linkedList -> tail -> prev = node;
	}

	//리스트가 비어있지 않은 경우
	else {
		linkedList -> tail -> prev -> next = node; //node : 추가, tail->prev : 기존노드
		node -> next = linkedList -> tail;

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

//백업할 파일을 backupLilst.list에 추가하는 함수
void addFileToList (char *dirName, Node *node) {
	FILE *fptr;

	fptr = fopen("backupList.list", "a");
	fprintf(fptr, "%s\t\t%d\n", node -> fileName, node -> filePeriod);

	fclose(fptr);
}

// list 기능을 위해 모든 백업 리스트를 출력하는 함수
void listFunc(LinkedList *linkedList) {
	Node *node;

	node = linkedList -> head -> next;

	while(node -> next != NULL) {
		printf("%s\t\t%d\n", node -> fileName, node -> filePeriod);
		node = node -> next;
	}
}

//================================디렉토리 관련 함수 정의부===================================

//main에서 인자로 입력받은 절대경로의 접근 권한 확인 함수
char *checkAccessDir(int argc, char **argv) {
	static char backupdir[512] = ""; //반환할 경로 저장할 배열
	struct dirent *dir; //dirent 구조체
	struct stat sb; //stat 구조체
	DIR *dirptr = NULL; //dirent 포인터
	char tmpdir[256] = ""; //임시로 현재 디렉토리를 가져와 저장해둘 배열

	int mode = R_OK | W_OK; // 읽기, 쓰기 가능

	realpath(argv[1], tmpdir); //상대경로를 절대경로로 변경하여 tmpdir에 저장
	stat(tmpdir, &sb);

	//인자를 2개 넘겨받은 경우
	if (argc == 2) {
		//성공적으로 접근 가능한 경우
		if (access(tmpdir, mode) == 0) {
			sprintf(backupdir,"%s/backup_directory", tmpdir); //백업디렉토리 명까지 backupdir에 저장
			mkdir(backupdir, 0775); //백업디렉토리 생성
			printf("backupdir : %s\n", backupdir);
			return backupdir; // 접근권한 있으면 backupdir 리턴
		}

		//디렉토리를 찾을 수 없는 경우
		else if ((dirptr = opendir(tmpdir)) == NULL) {
			printf("Usage : ./ssu_backup <dirname>\n");
			return NULL;
		}

		//인자가 디렉토리 파일이 아닌 경우
		else if (S_ISDIR(sb.st_mode) != 1) {
			printf("Usage : ./ssu_backup <dirname>\n");
			return NULL;
		}

		//접근 권한이 없을 경우	
		else if (access(tmpdir, mode) == -1) {
			printf("Usage : ./ssu_backup <dirname>\n");
			return NULL; //프로그램 종료
		}
	}

	//인자로 전달받은 경로가 없을 경우
	else if (argc == 1) {
		getcwd(tmpdir,256); //현재 경로 가져온 뒤
		sprintf(backupdir, "%s/backup_directory", tmpdir);

		mkdir(backupdir, 0755); //실행파일이 있는 곳(현재 디렉토리)에 백업 디렉토리 생성
		return backupdir;
	}

	//인자가 2개 이상인 경우
	else if (argc > 2) {
		printf("Usage : ./ssu_backup <dirname>\n");
		return NULL;
	}

	return NULL;
}

//'학번>' 프롬프트를 출력하는 함수
void printPrompt (char *absPath) {
	char userInput[300]; // 사용자로부터 명령어와 filename, period를 입력받기 위한 문자열배열
	char fileName[256]; // 파일의 절대경로 저장 배열
	char fileName2[256];
	char *token;
	int period = 0; //파일의 백업주기 저장 변수
	LinkedList linkedList;

	initList(&linkedList);

	while(1) {
		memset(userInput, 0, 300);
		memset(fileName, 0, 256);
		int tmpPeriod = 0;

		printf("20193017>");
		fgets(userInput, 256, stdin);

		userInput[strlen(userInput) -1] = '\0';

		//토큰 분리해서 명령어 호출 부분과 파일명, 백업주기 해당 기능 수행에 넘기는 작업 진행
		char *order = strtok(userInput, " "); //공백자 기준으로 문자열 자름

		if (strlen(userInput) == 0) continue; // 엔터만 입력했을 때 프롬프트 재출력하도록

		//add <파일명> [백업주기]
		if (strcmp(order, "add") == 0) {
			token = strtok(NULL, " "); //다음 문자열 잘라 fileName에 저장
			strcpy(fileName, token);

			token = strtok(NULL, " ");

			if (token != NULL) tmpPeriod = atoi(token); // 다음 문자열 잘라 chPeriod에 저장

			else {
				printf("period를 입력하세요.\n");
				//		break;
			}

			period = tmpPeriod;

			//add 기능 담당하는 함수에 filepath와 period 인자로 넘겨주기
			addFunc(&linkedList, absPath, fileName, period);
			//	break;
		}


		//remove <파일명>
		else if (strcmp(order, "remove") == 0) {
			token = strtok(NULL, " "); //다음 문자열 잘라 fileName에 저장

			strcpy(fileName, token);

			//remove 기능 담당하는 함수에 filepath 넘기기
			removeFunc(&linkedList, absPath, fileName);
			//break;
		}

		//compare <파일명1> <파일명2>
		else if (strcmp(order, "compare") == 0) {
			int paramCnt = 0; //fileName1, fileName2 

			token = strtok(NULL, " "); //다음 문자열 잘라 fileName에 저장
			strcpy(fileName, token);
			if (strlen(fileName) != 0) {
				paramCnt++;
			}

			token = strtok(NULL, " "); // 다음 문자열 잘라 fileName2에 저장
			strcpy(fileName2, token);
			if (strlen(fileName2) != 0) {
				paramCnt++;
			}

			if (paramCnt != 2) {
				printf("not 2 paremeter.\n");
				exit(1);
			}

			//compare 기능 담당하는 함수에 filePath, filePath2 넘기기
			compareFunc(fileName, fileName2);
			//	break;
		}

		//recover <파일명>
		else if (strcmp(order, "recover") == 0) {
			token = strtok(NULL, " "); //다음 문자열 잘라 fileName에 저장
			strcpy(fileName, token);

			//recover 기능 담당하는 함수에 filePath 넘기기
			recoverFunc(&linkedList, absPath, fileName);
			//	break;
		}

		//list 명령어
		else if (strcmp(order, "list") == 0) {
			listFunc(&linkedList);
			//	break;
		}

		//ls 명령어
		else if (strcmp(order, "ls") == 0) {
			system(userInput);
			//	break;
		}

		//vi 명령어
		else if (strcmp(order, "vi") == 0) {
			system(userInput);
			//	break;
		}

		//vim 명령어
		else if (strcmp(order, "vim") == 0) {
			system(userInput);
			//	break;
		}

		//exit 명령어
		else if (strcmp (order, "exit") == 0) {
			exit(0);
			return;
		}

		//존재하지 않는 명령어 입력할 경우
		else {
			printf("입력한 명령어가 존재하지 않습니다.\n");
			break;
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
		fprintf(stderr, "opendir error\n");

		return -1;
	}

	while ((dir = readdir(dirptr)) != NULL) {
		for (int i = 0; i < strlen(dir -> d_name); i++) {

			//	cnt++; break;
		}
	}
}

//add 기능을 수행하는 함수
void addFunc(LinkedList *linkedList, char *dirPath, char *fileName, int period) {
	FILE *fptr = NULL;
	DIR *dptr = NULL;
	char buf[256];
	char fileNameBuf[512];
	struct tm *loctm;
	time_t timer;
	char logmsg[1024] = "";
	int year, mon, day, hour, min, sec;
	pthread_t tid;

	Node *newFile; //추가되는 노드
	char thread_name[256]; //파일명으로 스레드 이름을 저장해둠
	int thr_id; //pthread_create() 리턴값 저장 변수
	int status; 
	int a =100;

	getcwd(buf, 256);
	char *fulltime = (char *)malloc(sizeof(char) * 100);
	sprintf(fileNameBuf, "%s/%s", buf, fileName);

	strcpy(thread_name, fileName);
	memset(logmsg, 0, 1024);

	if ((dptr = opendir(dirPath)) == NULL) {
		printf("opendir() error\n");
		exit(1);
	}

	newFile = makeNode(fileNameBuf);//노드 만들고

	//노드 구조체 멤버 값 설정
	strcpy(newFile -> absPath, dirPath);
	newFile -> filePeriod =  period;

	addNode(linkedList, newFile);//리스트에 노드 추가
	addFileToList(dirPath, newFile);

	//스레드 생성부
	if(pthread_create(&tid, NULL, thread_function, (void *)newFile) != 0){ //쓰레드 생성
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}    
	pthread_detach(tid); //detach시켜줘서 자원 회수
}

//remove 기능을 수행하는 함수
void removeFunc(LinkedList *linkedList, char *dirPath, char *fileName) {
	Node *removeFile;

	FILE *fptr = NULL;
	DIR *dirptr = NULL;//dirent구조체 포인터
	struct dirent *entry = NULL;//dirent구조체
	char fullFileName[512]; 
	char buf[256];
	int removeFileCnt = 0; //백업디렉토리에서 삭제할 파일의 수 카운트

	struct tm *loctm;
	time_t timer;

	char logmsg[1024];
	char fulltime[256];
	int year, mon, day, hour, min, sec;

	memset(fulltime, 0, 256);
	memset(logmsg, 0, 1024);

	if (fileName == NULL) { //FILENAME을 입력하지 않은 경우
		printf("파일명을 입력하세요.\n");
		exit(0);
	}

	getcwd(buf, 256);
	sprintf(fullFileName, "%s/%s", buf, fileName);

	removeFile = findNode(linkedList, fullFileName); //연결리스트에서 파일명의 노드를 찾아 리턴받음

	if (removeFile == NULL) { //백업 중단할 파일이 리스트에 존재하지 않는 경우
		printf("백업을 중단할 파일이 백업 리스트에 존재하지 않습니다.\n");
		exit(0);
	}

	timer = time(NULL);
	loctm = localtime(&timer);

	pthread_cancel(removeFile -> tid); //삭제하고자하는 파일의 스레드 종료

	//노드 삭제 수행 시간 계산
	year = loctm -> tm_year + 1900;
	mon = loctm -> tm_mon +1;
	day = loctm -> tm_mday;
	hour = loctm -> tm_hour;
	min = loctm -> tm_min;
	sec = loctm -> tm_sec;

	//파일 삭제 수행을 성공적으로 완료하면 deleted로그 작성
	sprintf(fulltime, "[%d%02d%02d %02d%02d%02d] ", year, mon, day, hour, min, sec);
	sprintf(logmsg, "%s %s%s deleted", fulltime, dirPath, fileName);
	write_log(logmsg);
}

//compare 기능을 수행하는 함수
void compareFunc(char *fileName1, char *fileName2) {
	FILE *file1;
	struct stat buf1;
	char *mtime1;
	size_t size1; //fileName1의 내용 담는 file, stat, tm, size

	FILE *file2;
	struct stat buf2;
	char *mtime2;
	size_t size2; //fileName2의 내용 담은 file, stat, tm, size

	stat(fileName1, &buf1);
	stat(fileName2, &buf2);

	mtime1 = ctime(&buf1.st_mtime); //fileName1의 mtime 측정
	mtime2 = ctime(&buf2.st_mtime); //fileName2의 mtime 측정

	//파일이 존재하지 않을 경우
	if (!(file1 = fopen(fileName1, "r")) && !(file2 = fopen(fileName2, "r"))) {
		fclose(file1);
		fclose(file2);

		printf("입력한 파일이 존재하지 않습니다.\n");
		exit(1);
	}

	//일반 파일이 아닌 경우
	if (S_ISREG(buf1.st_mode) != 1) {
		printf("일반 파일이 아닙니다.\n");
		exit(1);
	}

	//mtime과 파일크기 비교
	if (strcmp(mtime1, mtime2) == 0) {
		if (buf1.st_size == buf2.st_size) {
			printf("%s과 %s은 동일한 파일입니다.\n", fileName1, fileName2);
		}

		else {
			printf("FILENAME1 -> mtime : %sFILENAME1 -> 파일크기 : %d \n", mtime1, (int)(buf1.st_size));
			printf("FILENAME2 -> mtime : %sFILENAME2 ->  파일크기 : %d \n\n", mtime2, (int)(buf2.st_size));
		}
	}
}

//파일 크기를 가져오기 위한 함수 (compare) 명령어에서 사용
static size_t getFileSize(const char *fileName) {
	struct stat sb;

	if (stat(fileName, &sb) != 0) {
		fprintf(stderr, "'stat' failed for '%s' : \n", fileName);
		exit(1);
	}

	return sb.st_size;
}

//recover 기능을 수행하는 함수
void recoverFunc(LinkedList *linkedList, char *dirPath, char *fileName) {
	struct stat sb;
	struct stat tmpsb;

	DIR *dirptr = NULL; //dirent 구조체 포인터
	struct dirent *entry = NULL; //dirent 구조체
	FILE *logfptr = NULL; //로그파일 포인터
	FILE *copy_fptr = NULL; //백업 파일 읽어오는 파일 포인터
	FILE *paste_fptr = NULL; //리커버 파일에 넣는 파일 포인터
	struct tm *loctm;
	time_t timer;

	char fullFileName[512]; //절대경로와 파일이름을 합친 배열
	char fullDirName[512];
	char fulltime[100];
	char logmsg[1024]; //로그메세지
	int year, mon, day, hour, min, sec;
	int rcvFileCnt = 0; //recover 파일 카운터 변수

	char rcvptr[100][256];//출력 내용 저장할 2차원 포인터
	char *cmp_fileName;
	char *buf;
	char cwd[256];
	char d_name_of_file[256];
	int d_name_len = 0;
	char size_tmp[100]; //파일 사이즈 저장 배열
	int file_size = 0;

	int userInput = 0; //사용자 입력값
	char chosen_time[512];
	char find_file[256];

	Node *recoverFile;

	memset(fulltime, 0, 100); //백업 시간 저장하는 메모리 초기화
	memset(fullFileName, 0, 512); //절대경로/파일명 저장하는 메모리 초기화

	getcwd(cwd, 256);
	sprintf(fullFileName, "%s/%s", cwd, fileName);
	sprintf(fullDirName, "%s/backup_directory", cwd);

	recoverFile = findNode(linkedList, fullFileName);

	if (recoverFile -> fileName == NULL) {
		printf("복구를 진행할 파일이 존재하지 않습니다.\n");
		exit(0);
	} 

	timer = time(NULL);
	loctm = localtime(&timer);

	dirptr = opendir(fullDirName);
	if (dirptr == NULL) {
		printf("opendir() error\n");
	}

	//입력받은 파일명과 동일한 백업본 파일 2차원 배열에 저장해주는 작업
	while((entry = readdir(dirptr)) != NULL) {
		memset(d_name_of_file, 0, 256);
		memset(size_tmp, 0, 100);

		strcpy(d_name_of_file, entry -> d_name);

		cmp_fileName = strstr(d_name_of_file, fileName);

		if (cmp_fileName != NULL) { //문자열 비교해 같은 부분 있으면
			stat(fileName, &sb);
			char *token_1st = strtok(d_name_of_file, "_"); 
			char *name_tmp = strtok(NULL, "_");//출력할 배열에 백업시간 저장

			file_size = sb.st_size;
			sprintf(size_tmp, "%dbytes", file_size);

			sprintf(rcvptr[rcvFileCnt], "%d. %s \t %s", rcvFileCnt +1, name_tmp, size_tmp);//rcvptr 배열에 값 저장하는 작업 완료 

			rcvFileCnt++; //파일 개수 +1
		}
	}

	//2차원 배열 출력하고 사용자에게 원하는 백업버전 입력받는 작업
	printf("0. exit\n");
	for (int i = 0; i < rcvFileCnt; i++) {
		printf("%s\n", rcvptr[i]);
	}

	printf("Choose file to recover : ");
	scanf("%d", &userInput);

	if (userInput == 0) { //0을 입력한 경우
		exit(0);
	}

	else { //파일의 백업 버전을 입력한 경우
		char recovered[256];
		memset(recovered, 0, 256);

		strcpy(chosen_time, rcvptr[userInput - 1]); //사용자가 선택한 인덱스의 배열 가져옴
		//printf("chosen_time : %s\n", chosen_time);

		char *token_tmp = strtok(chosen_time, " "); //'순번.' 을 읽어옴
		char *token_time = strtok(NULL, "\t"); //공백자 " " 이후의 백업시간을 토큰으로 가져옴

		sprintf(find_file, "%s_%s", fileName, token_time); //fileName.txt_210312~으로 저장됨

		char *finalName = strtok(find_file, "."); //ex) test1.txt -> test1만 가져오게 됨
		sprintf(recovered, "%s_recover.txt", finalName); //fileName_recover.txt생성
		
		pthread_cancel(recoverFile -> tid); //백업 수행 종료 후 복구 진행
			
		char copybuf[MAX_SIZE + 1]; //파일의 내용을 fgets, fputs 하기 위한 버퍼
		char copyFilePath[MAX_SIZE]; //절대경로/백업디렉토리/파일백업본 주소 저장 버퍼
		
		sprintf(copyFilePath, "%s/%s_%s", fullDirName, fileName, token_time);//fileName.txt_2103~
		printf("copyFilePath : %s\n", copyFilePath);
		
		/*
		if ((copy_fptr = fopen(copyFilePath, "r+")) == NULL) {
			memset(copybuf, 0, MAX_SIZE + 1);
			printf("fopen success\n");
		}
		*/

		if (rename(recoverFile -> fileName, recovered) == 0) { //파일 이름 변경 성공 시
			printf("Recovery success\n");
		}
		/*
		if ((copy_fptr = fopen(copyFilePath, "r+")) != NULL) { //백업파일 open
			memset(copybuf, 0, MAX_SIZE + 1);
			printf("fopen success\n");

			fgets(copybuf, sizeof(copybuf), copy_fptr); //백업 파일의 내용을 copybuf로 읽어옴
			fclose(copy_fptr);

			if (rename(recoverFile -> fileName, recovered) == 0) { //파일 이름 변경 성공 시
				if ((paste_fptr = fopen(recovered, "w")) != NULL) { //백업내용 덮어쓰는 파일 open
					fputs(copybuf, paste_fptr); //파일에 문자열 저장

					printf("Recovery success\n");
					fclose(paste_fptr);
				}
			}
		} */

		else {
			printf("파일 복구에 실패하였습니다.\n");
			exit(0);
		}
	}

	closedir(dirptr);
}


//ls 명령어
void lsFunc() {
	DIR *dirptr = NULL;
	struct dirent *dir = NULL;
	int printCnt = 0;

	char *cwd = (char*)malloc(sizeof(char) * 256);

	getcwd(cwd, 256); //get current working directory

	if ((dirptr = opendir(cwd)) == NULL) {
		printf("ls function error : current directory cannot open\n");
		exit(1);
	}

	while((dir = readdir(dirptr)) != NULL) {
		printf("%s\t", dir->d_name);
	}

	closedir(dirptr); 
}

//============================= 로그파일 작성 함수 ================================
void write_log(char *msg) {
	FILE *fptr;
	char logMsg[1024];

	fptr = fopen("logfile.log", "a");

	if (fptr != NULL) {
		fprintf(fptr, "%s\n", msg);
	}

	fclose(fptr);
}

//=========================== 스레드 관련 함수  ===================================
void *thread_function (void *addFile) {
	Node *newNode;
	newNode = (Node *)addFile;

	struct stat statbuffer;//stat구조체
	struct stat copystat;
	FILE *addfptr = NULL; //add한 파일 포인터
	FILE *backupfptr = NULL; //backup한 파일 포인터
	DIR *dirptr; //dirent 포인터
	struct dirent *dir; //dirent 구조체

	time_t timer;
	struct tm *loctm;
	char *backupFile; //백업된 파일의 이름을 '_년월일시분초'를 추가해 저장하는 배열

	char *tmpbuf; //파일 내용 읽어와 쓰는 작업 중 사용하는 임시 버퍼
	char *justFileName; // 파일명
	char fullFilePath[256]; // 절대경로를 포함한 파일명
	char logmsg[1024] = ""; 

	int year, mon, day, hour, min, sec;
	char *fulltime;

	backupFile = (char *)malloc(sizeof(char) *256);

	newNode -> tid = pthread_self(); 

	fulltime = (char *)malloc(sizeof(char) *100);

	if ((timer = time(NULL)) == -1) { //초 단위로
		perror("time() call error");
		exit(1);
	}

	if ((loctm = localtime(&timer)) == NULL) { //시간을 분리하여 tm 구조체에 넣음
		perror("localtime() call error");
		exit(1);
	}

	memset(logmsg, 0, 1024);

	year = loctm -> tm_year + 1900;
	mon = loctm -> tm_mon +1;
	day = loctm -> tm_mday;
	hour = loctm -> tm_hour;
	min = loctm -> tm_min;
	sec = loctm -> tm_sec;
	sprintf(fulltime, "[%02d%02d%02d %02d%02d%02d] ", year, mon, day, hour, min, sec); // 로그파일 작성 ex) [190311 153320] 

	pthread_mutex_lock(&mutex); //스레드 동기화 lock
	justFileName = makeJustFile(newNode -> fileName);
	sprintf(logmsg, "%s %s/%s added", fulltime, newNode -> absPath, justFileName);
	write_log(logmsg);
	pthread_mutex_unlock(&mutex); //스레드 동기화 unlock

	sleep(newNode -> filePeriod);// 백업 수행 주기만큼 시간 지연
	stat(newNode -> fileName, &statbuffer);

	while(1) { //해당 노드가 pthread_exit() 까지 반복
		memset(fullFilePath, 0, 256);
		stat(newNode -> fileName, &statbuffer); //추가한 파일의 정보를 읽어올 수 있도록
		tmpbuf = (char *)malloc(sizeof(char) * statbuffer.st_size); //파일 크기만큼 tmpbuf 동적할당

		addfptr = fopen(newNode -> fileName, "r"); //추가한 파일을 읽기 모드로 fopen
		if (addfptr == NULL) {
			//fprintf(stderr, "fopen() error\n");
			exit(1);
		}

		memset(fulltime, 0, 100); //백업 수행 시간 저장하는 배열 초기화
		memset(logmsg, 0, 1024); //로그 메시지 저장 배열 초기화

		if ((timer = time(NULL)) == -1) { //초 단위로
			perror("time() call error");
			exit(1);
		}   

		if ((loctm = localtime(&timer)) == NULL) { //시간을 분리하여 tm 구조체에 넣음
			perror("localtime() call error");
			exit(1);
		}   
		//백업 수행시간 측정하여 fulltime에 저장
		year = loctm -> tm_year + 1900;
		mon = loctm -> tm_mon +1;
		day = loctm -> tm_mday;
		hour = loctm -> tm_hour;
		min = loctm -> tm_min;
		sec = loctm -> tm_sec;
		sprintf(fulltime, "[%02d%02d%02d %02d%02d%02d] ", year, mon, day, hour, min, sec); //fulltime 저장
		justFileName = makeJustFile(newNode -> fileName);
		sprintf(backupFile, "%s/%s_%02d%02d%02d%02d%02d%02d", newNode -> absPath, justFileName, year, mon, day, hour, min, sec); //백업된 파일 만드는 부분

		backupfptr = fopen(backupFile, "w+"); //파일이 존재하지 않을 경우 빈 파일을 새로 생성(백업할 파일)
		if (backupfptr == NULL) {
			fprintf(stderr, "backupfptr : fopen() error\n");
			exit(1);
		}

		int count = fread(tmpbuf, sizeof(char), statbuffer.st_size -1 , addfptr); //마지막 null 제외한 파일 내용 읽어옴
		fwrite(tmpbuf, sizeof(char), count, backupfptr); //읽어들인 내용을 파일에 씀

		sprintf(logmsg, "%s %s generated", fulltime, backupFile);
		write_log(logmsg); //백업 후 로그 작성

		fclose(addfptr);
		fclose(backupfptr);
		sleep(newNode -> filePeriod);// 백업 수행 주기만큼 시간 지연

	}

	closedir(dirptr);
}

char* makeJustFile(char *filename) {
	char *file; //파일이름
	int count1 = 0, count2 = 0; //토큰처리를 위한 변수
	int i; //for문제어를 위한 변수

	file = (char *)malloc(sizeof(char)*255); //동적할당

	for(i = 0; i < strlen(filename); i++){
		if(filename[i] == '/'){ // '/'을 만날때마다 카운트
			count1++;
		}
	}
	for(i = 0; i < strlen(filename); i++){
		if(filename[i] == '/'){ // '/'을 만날때마다 카운트
			count2++;
		}
		if(count1 == count2){ //카운트수가 같다면
			strcpy(file, filename+(i+1)); // '/'다음은 파일이름만 있으므로 그때부터 파일이름을 복사해줌
			break;
		}
	}

	return file; //파일이름 리턴
}
