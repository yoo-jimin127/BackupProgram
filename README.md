# lsp_winter_backup_program
### 21.02.06 (토) 프로젝트 진행 계획 및 보고
* ~~명세 분석 및 정리 요약~~ **(02.06 완료)**
* ~~210203 진행되었던 명세 설명 내용 다시 이해~~ **(02.06 완료)**
* 명세 관련 질문사항 정리 **(02.06 진행 중)**
  <br> (개념 이해가 어려운 부분이 존재해 02.07 기본 개념 학습 뒤 스스로 해결할 수 있는 질문내용을 추릴 예정입니다.)
* ~~thread 개념 학습~~ **(02.06 완료)**
* ~~명세서에 있는 함수 기능 이해~~ **(02.07 )**

#### 210206 진행 보고

##### 명세 분석 및 정리 요약 & 명세 관련 질문사항 정리
![image](https://user-images.githubusercontent.com/66112716/107120063-b2f6c300-68ce-11eb-87c6-418de66526e3.png)

![image](https://user-images.githubusercontent.com/66112716/107120088-dde11700-68ce-11eb-961c-ee75df1f0237.png)

![image](https://user-images.githubusercontent.com/66112716/107120102-f7825e80-68ce-11eb-94b1-e61d5b401f80.png)

![image](https://user-images.githubusercontent.com/66112716/107120123-15e85a00-68cf-11eb-9080-77e0a33dc60a.png)
<br> 
- 명세 2p 상 로그파일 작성 예시 - ex) 쓰레드 : 시간 재는 작업, 백업, 추가 등 일 분담하여 담당
- int main (int argc, char * argv[]) 사용해 실행파일 실행 시 인자 삽입
  - argc : 프로그램 실행 시 지정해준 명령행 옵션의 개수가 저장되는 곳
  - argv : 프로그램 실행 시 지정해준 명령행 옵션의 문자열들이 실제로 저장되는 배열
------
### 21.02.07 (일) 프로젝트 진행 계획 및 보고
#### 210207 진행 계획
(명세에 대해 전반적인 이해는 마친 상태입니다. 하지만 구현 방법에 대해 갈피가 잡히지 않아서 명세에 나와있는 함수에 대한 사용법과 멘토님께서 보내주신 thread 관련 코드들에 대한 학습을 빠르게 선행한 뒤 구현 방법에 대해 고민할 예정입니다.)

* ~~pthread_create() 함수 공부~~ **(02.07 완료)**
  - ~~pthread_create.c, pthread_create_2.c 코드 이해 및 함수 사용법 학습~~ **(02.07 완료)**
* ~~pthread_exit() 함수 공부~~ **(02.07 완료)**
* ~~pthread_join() 함수 공부~~ **(02.07 완료)**
  - ~~pthread_join.c 코드 이해 및 함수 사용법 학습~~ **(02.07 완료)**
* ~~pthread_detach() 함수 공부~~ **(02.07 완료)**
* ~~pthread_mutex_init(), pthread_mutex_destroy() 함수 공부~~ **(02.07 완료)**
* ~~system() 함수 공부~~ **(02.07 완료)**

#### 210207 프로젝트 진행 보고 및 학습내용
* pthread 사용 위해 숙지할 점
  - pthread 함수 사용을 위해 반드시 **#include <pthread.h>** 헤더파일 include
  - 컴파일 시 **-lpthread** 옵션 주어야 함<br>
   ex) ```gcc pthread_create.c -o pthread_create -lpthread```
  - pthread_t : pthread 자료형 의미
  <br>
* **pthread_create()** 함수 : pthread 생성 기능 <br>
```int pthread_create (pthread_t *th_id, const pthread_attr_t *attr, void *함수명, void *arg);```
  - 첫번째 인자 : pthread 식별자, thread가 성공적으로 생성될 경우 **thread 식별값** 주어짐
  - 두번째 인자 : pthread 속성 (option), 기본적 스레드 속성 사용 시 NULL(본 프로젝트에서는 NULL)
  - 세번째 인자 : pthread로 분기할 함수, 리턴 값, 매개변수 모두 ```void*``` 로 선언된 함수만 사용 ok ```ex) void* handler (void* arg) {...}```
  - 네번째 인자 : 분기할 함수로 넘겨줄 인자 값, 어떤 자료형 넘겨줄 지 모르므로, void형으로 넘겨준 뒤 상황에 따라 분기하는 함수 내에서 해당 자료형으로 캐스팅해 사용
  - 리턴 값 : 성공적으로 pthread 생성 시 0 리턴 (return형 : int)
  <br>
* **pthread_join()** 함수 : 특정 pthread가 종료될 때까지 기다린 뒤, 특정 pthread가 종료시 자원을 해제시켜줌. <br>
```int pthread_join (pthread_t th_id, void** thead_return);```
  - 첫번째 인자 : 어떤 pthread 기다릴지 정하는 식별자 (스레드 식별자)
  - 두번째 인자 : pthread의 리턴 값, **포인터**로 값 받아오는 점 주의
  - 리턴 값 : 성공 시 0 리턴, 실패 시 에러코드 리턴
  <br>
* **pthread_exit()** 함수 : 현재 실행 중인 thread를 종료시킬 때 사용 <br>
```void pthread_exit(void* ret_value);```
  - 보통 pthread_exit 호출 시 cleanup handler가 호출되며, 보통 리소스 해제하는 일 수행 <br>
    ![image](https://user-images.githubusercontent.com/66112716/107148300-ccaf0d80-6995-11eb-8537-395a3e6129c1.png)
    - 쓰레드에서 자원 사용하는 것이 있었을 때, 종료 전에 자원을 반납하는 등의 처리를 해야 함.<br>
      **sol.** cleanup handler 함수 등록하여 수행
        - ```void pthread_cleanup_push(void (*routine) (void*), void* arg);``` : cleanup handler 함수 등록
          - pthread_exit()가 호출될 때 호출된 handler 정하는 함수
          - 자원 해제용 or mutex lock 해제를 위한 용도로 사용 (동기화)
        - ```void pthread_cleanup_pop(int execute);``` : cleanup handler 함수 제거
          - execute값이 0일 경우 바로 cleanup handler 제거, 그 외의 값일 경우 cleanup handler 한번 실행 수 제거 <br>
        [cleanup handler 함수 등록 관련 내용] (https://bitsoul.tistory.com/166)

*  **pthread_detach()** 함수 : th_id 식별자를 가지는 pthread가 부모 pthread로부터 독립<br>
```int pthread_detach(pthread_t td_id);```
  - 해당 함수를 통해 독립된 pthread는 따로 pthread_join() 없어도 종료 시 자동으로 리소스 해제 됨.<br>
  
* **pthread_t pthread_self()** 함수 : 현재 동작중인 pthread의 식별자 리턴
<br>

#### 공유 자원에 대한 접근 제어를 위해 동기화, mutex 사용
* [mutex 사용 이유, 동기화 달성 방법, mutex 생성 등에 대한 참고자료] (https://www.joinc.co.kr/w/Site/Thread/Beginning/Mutex)
* mutex 사용 시 참고할 사항
  - pthread_mutex_t : 뮤텍스 구조체
  - pthread_mutex_lock() : critical section 시작
  - pthread_mutex_unlock() : creitical section 종료
  <br>
* **pthread_mutex_init()** 함수 : mutex 객체 초기화시키기 위해 사용 <br>
```int pthread_mutex_init (pthread_mutex_t * mutex, const pthread_mutexatt_t *attr);```
  - 첫번째 인자 : mutex 객체를 첫번째 인자로 넣어 mutex 객체 초기화
  - 두번째 인자 : attr 을 통해 mutex 특성 변경 가능, 기본 mutex 특성 이용 시 NULL 사용
    - mutex 특성 : fast, recurisev, error checking 있음. 디폴트 : fast
  - 리턴 값 : 성공적 수행 시 0 리턴, 실패 시 오류 번호 리턴
    <br>
* **pthread_mutex_destroy()** 함수 : mutex 객체 파괴 <br>
```int pthread_mutex_destroy(pthread_mutex_t *mutex);```
  - 인자 : 파괴될 뮤텍스
  - 리턴 값 : 성공적 수행 시 0 리턴, 실패 시 오류 번호 리턴
 
 * [mutex 사용 예제] (https://bitsoul.tistory.com/172)
 ![image](https://user-images.githubusercontent.com/66112716/107149616-e4d65b00-699c-11eb-9983-9257383ee01b.png)
 
* **system()** 함수 : ```/bin/sh -c string```호출하여 지정된 명령어를 실행하고, 명령어가 끝난 후 반환함. 
  - system()함수 사용 방법
  ```
  #include <stdlib.h>  //system() 함수 사용 위해 include
  #include <unistd.h>
  
  int system(const char *string);
  
  int main (int argc, char **argv) {
    int i = 0, retval;
    retval = system("ls -al");
    printf("Exit status %d\n", retval);
  }
  ```
  - 리턴 값 : 성공 시 **0 아닌 값**(string 값이 NULL이고, system()이 shell을 이용할 수 있는 경우) 리턴, 실패 시 0 리턴
    - /bin/sh 실행시키기 위한 execve() 호출 실패 시 127 리턴, 다른 에러의 경우 -1, 그렇지 않으면 명령어의 리턴코드 반환
  - system()은 다른 wait() 상태의 다른 자식에게 영향 X <br>
[system() 함수 참고 자료] (https://www.joinc.co.kr/w/man/3/system)


#### 멘토님/튜터님 피드백
* cleanup handler 관련 함수 사용 대신 **pthread_cancel()** 사용 권장
```int pthread_cancel (pthread_t thread);``` : 인자로 주어진 쓰레드 식별번호 가지는 쓰레드의 취소 요청을 보냄. 
* 리턴, 반환 등의 키워드 통일하여 정리

------
### 21.02.08 (월) 프로젝트 진행 계획 및 보고
#### 210208 프로젝트 진행 계획
* ~~stat 구조체 학습~~ **(02.08 완료)**
* ~~리눅스 환경에서 쉘(shell) 만드는 방법 학습~~ **(02.08 완료)**
  * ~~예제 코드 만들어 쉘 생성, 스크립트 작성 연습~~ **(02.08 완료)**
* ~~쉘스크립트에서 로그파일 생성하고 작성하는 방법 학습~~ **(02.08 완료)**
  * 예제 코드 만들어 명세 상 ui와 같은 로그파일 작성 연습 **(02.08 진행 중)** <br>
  -> 로그파일에 시간 순서대로 로그 작성되는 부분 추가적으로 학습하기 (02.09)
* 명세 상 명령어별 기능 세분화, 로직 구상 **(02.08 진행 중)**
  - ssu_backup 프로그램 기능
  - add <FILENAME> [PERIOD] 기능
  - remove <FILENAME> [PERIOD] 기능
  - compare <FILENAME1> <FILENAME2> 기능
  - recover <FILENAME> 기능
  - list 기능
  - ls 기능, vi(m) 기능
    - system() 함수를 사용하면 될 것으로 예상
  - exit 기능

#### 210208 프로젝트 진행 보고 및 학습 내용
* **stat 구조체** : 파일 정보를 저장하는 구조체
```
struct stat {
  dev_t st_dev; // 장치 파일의 위치 및 여부를 기술
  ino_t st_ino; // 파일의 inode 번호
  mode+t st_mode; // 파일의 모드를 다룸
  nlink_t st_nlink; // 파일의 하드링크 수
  uid_t st_uid; // 소유자의 user ID
  gid_t st_gid; // 소유자의 group ID
  dev_t st_rdev; // 장치 파일 (inode)를 기술
  off_t st_size; // 파일의 사이즈
  blksize_t st_blksize; // 효율적인 I/O 파일 시스템 위한 블럭 사이즈
  blkcnt_t st_blocks; // 파일에 할당한 블럭의 수
  time_t st_atime; // 마지막 접근 시각
  time_t st_mtime; // 마지막 수정 시각
  time_t st_ctime; // 마지막 상태 변경 시각
}
```
*note* ) 기능 중 compare <FILENAME1> <FILENAME2> 에서 파일명1과 파일명2가 동일한 파일인지 구별하는 기능에서 mtime과 파일 크기가 같은 경우의 조건으로 파일을 비교함.
  이 때, 파일 정보를 저장하는 stat 구조체에서 st_mtime 멤버와 st_size 멤버를 호출하여 비교하는 작업을 진행해 compare 기능을 구현하면 될 것으로 보임.

* stst 구조체의 정보 확인을 위한 시스템 호출
```
#include <sys/types.h>
#include <sys/stat.h>

int stat (const char *path, struct stat *buf);
int fstat (int fd, struct stat *buf); //fd : 파일 디스크립터
int lstat (const char *filename, struct stat *buf);
```
* **stat()** 함수 : 첫번째 인자로 pathname을 받으며, stat 구조체에 그 정보를 저장
* **lstat()** 함수 : stat 함수와 기능 
* **fstat()** 함수 : 해당하는 파일의 디스크립터를 받아 stat 구조체에 정보를 저장

[stat 구조체 관련 파일 정보 불러오는 함수] (https://cokk.tistory.com/51)

* **쉘(shell)** 이란 ?
  * 명령어와 프로그램 실행할 때 사용하는 인터페이스
  * 사용자와 커널 사이에서 명령을 해석해 전달하는 **명령어 해석기 기능**
  * 쉘 자체 내애 **프로그래밍 기능**이 있어 프로그램 작성 가능 -> 쉘 프로그램 == 쉘 스크립트
  * **사용자 환경 설정의 기능** : 초기화 파일 기능을 이용해 사용자의 환경 설정 가능
  
* 쉘 기본 명령어
  * ```whoami``` : 로그인한 사용자 ID 알려줌
  * ```passwd``` : 로그인한 사용자 ID의 암호 변경
  * ```pwd``` : 현재 디렉토리 위치 (코딩하면서 디렉토리 위치 확인할 때 사용)
  * ```cd``` : 디렉토리 이동
  * ```ls``` : 파일 목록 출력
  * ```cat``` : 파일 보기
  * ```head/tail``` : head - 파일 시작 부분, tail - 끝 부분
  * ```more``` : 파일보기 (화면 넘어갈 경우, 화면 넘어가기 전까지 보여줌)
  * ```rm``` : 파일 및 폴더 삭제
  * ```man``` : manual
  -> 리눅스 터미널에서의 명령어와 동일한 것 같다. 별도로 익혀야 할 내용은 없을 것 같다.

* bash shell : 리눅스에서 가장 많이 사용되는 쉘.
  * 리눅스 쉘 스크립트 예제
  ```
  #!/bin/bash
  
  echo "helllo world"
  ```
    - 쉘 스크립트 파일 작성 시 가장 처음 ```#!bin/bash``` 구문 추가하여 내용 작성, 문자열 출력 내용 ```echo "..."```
    - 실행 권한 추가한 뒤 실행
    ``` 
    chmod +x test.sh
    ./test.sh
    ```
  * [bash 쉘을 이용해 스크립트 만드는 방법] (https://poorman.tistory.com/316)
  
* 로그파일 생성 방법
  - 본 프로젝트에서의 로그파일 사용 목적 : 
    -  생성된 백업 디렉토리에 하나의 로그파일 생성 & 기록
    - [수행시간] 수행내용 형태로 로그파일 작성
    - add, remove, recover 명령어 실행 성공 시 로그파일에 기록
    - 시간 순서대로 로그 작성될 수 있도록 동기화 수행  
 - [로그파일 갱신하는 쉘 스크립트] (https://guinbun.tistory.com/28) <br>
  -> 중간마다 생기는 갱신 과정 결과와 에러를 다른 로그에 기록하는 부분 참고
  
* 명세 구현 아이디어 정리
  * 필요한 헤더파일 정리
    ```
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <pthread.h>
    #include <unistd.h>
    ```
  * ssu_backup 실행 시 디렉토리 생성할 경로 인자로 입력할 때 입력한 경로로 이동하기 위한 작업 : 입력값을 system() 함수를 이용하여 해당 디렉토리로 이동<br>
  [system() 함수 사용해 쉘에서의 명령어 기능 구현] (https://computersource.tistory.com/67)
  * usage 출력 방법 : ex) ```Usage : ./ssu_backup <dirname> ```
  * 명령어 실행 시 ```<FILENAME>```과 ```[PERIOD]```를 어떻게 구분하여 접근?
    - 구현 방향 : 이전 영단어 프로그램에서 사용하였던 strtok() 함수를 사용해 토큰을 분리하여 구조체 또는 링크드 리스트에 저장함 <br> -> 파일명은 해당 파일명을 불러오는 스레드로 넘기고, preiod는 백업주기를 관리하는 스레드로 넘김.


#### 튜터님 & 멘토님 피드백 
* 쉘 스크립트 != 쉘, 본 프로젝트에서의 쉘 : 학번 > 과 같은 터미널 구현 의미
------
### 21.02.09 (화) 프로젝트 진행 계획 및 보고
#### 210209 프로젝트 진행 계획
* ~~백업 프로그램 구현 시작~~ **(02.09 진행 중)**
  * ~~백업할 파일들을 관리하는 연결리스트 구조체 구현~~ **(02.09 완료)**
  * ./ssu_backup <디렉토리 생성 경로 입력> 구현 **(02.09 진행 중)**
  * ~~ssu_backup 실행 후 "학번>" 프롬프트 출력~~ **(02.09 완료)**

#### 구현 방향 및 학습 내용
  * 기능별 명령어를 모두 함수로 구현하여 입력값에 따라 토큰으로 분리하고(strtok() 또는 다른 방법도 사용 가능할 것으로 보임) 인자로 넘김, 여기서 명령어가 입력된 토큰을 switch문으로 구별해 각 명령어의 기능이 구현되어있는 함수를 호출.
  * 백업리스트 : 링크드 리스트 (노드 구조체로 파일별 노드를 만들고 이를 연결리스트로 연결하자 -> double linked list 사용 예정) 
  ```
  typedef struct node {
    파일의 절대경로
    백업 주기
    백업 옵션
  }Node;
  ```
  -> 연결리스트에서 해당 백업파일이 존재하는지 등을 확인하기 위해 파일을 찾는 작업 등을 위해서 이전 프로젝트에서의 연결리스트 관련 함수 구현.
  <br>
  * 로그파일 작성 방법 : ```logfile.log``` 파일 만들어서 파일입출력 통해 ```fprintf()``` 함수로 수행 성공하면 로그파일에 넣기
     -> 명세 : 하나의 로그파일에 작성 (파일은 하나만 만들고 그 안에서 모든 백업 기록을 다룸. 시간 순으로 로그 작성할 수 있도록 작성하기) <br>
     - [로그파일 작성 예시] (https://m.blog.naver.com/PostView.nhn?blogId=ew32&logNo=150168169124&proxyReferer=https:%2F%2Fwww.google.com%2F)
     <br>
   * main 함수에 경로를 인자로 넘겨주기
   ![image](https://user-images.githubusercontent.com/66112716/107370556-79b89000-6b26-11eb-9793-d0cf1fb71e8d.png)
<br>
    
#### 구현 중 질문 사항
* 명세 : ssu_backup 프로그램 실행 시 백업 디렉토리를 생성할 경로를 인자로 입력<br>
         ssu_backup 실행 후 20190000>와 같은 프롬프트 출력 (공백없이 학번 + '>') <br>
   -> ~~./ssu_backup으로 vi 편집기에서 프로그램을 실행시키면 20190000>이라는 학번이 나오고, 그 뒤에 상대경로 or 절대경로를 바로 입력?~~ <br> 
   ~~아니면 들어가면 "디렉토리를 생성할 경로를 입력하시오 :" 라는 문구를 띄운 뒤 사용자로부터 경로를 입력받으면 그 뒤에 20190000>과 같은 프롬프트를 출력?~~ <br>
   -> ~~명세 3p의 add 명령어 실행 예를 보면 ```20190000>add test1.txt 5``` 와 같이 프롬프트 출력 뒤 바로 ```명령어 filename period```가 나오는데 경로 입력할 때는 '학번>'이 안니오는 것?~~ <br>
  -> **해결.** gcc 컴파일 후 ./ssu_backup <디렉토리 생성할 경로>의 인자를 넣어 해결
  -> **해결.** printf("20190000>");으로 찍는 것임. 프롬프트 출력 방법을 변경하는 것 X
  -> **해결.** 본인의 학번 적는 것
  <br>
