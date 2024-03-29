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
        [cleanup handler 함수 등록 관련 내용](https://bitsoul.tistory.com/166)

*  **pthread_detach()** 함수 : th_id 식별자를 가지는 pthread가 부모 pthread로부터 독립<br>
```int pthread_detach(pthread_t td_id);```
  - 해당 함수를 통해 독립된 pthread는 따로 pthread_join() 없어도 종료 시 자동으로 리소스 해제 됨.<br>
  
* **pthread_t pthread_self()** 함수 : 현재 동작중인 pthread의 식별자 리턴
<br>

#### 공유 자원에 대한 접근 제어를 위해 동기화, mutex 사용
* [mutex 사용 이유, 동기화 달성 방법, mutex 생성 등에 대한 참고자료](https://www.joinc.co.kr/w/Site/Thread/Beginning/Mutex)
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
 
 * [mutex 사용 예제](https://bitsoul.tistory.com/172)
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
[system() 함수 참고 자료](https://www.joinc.co.kr/w/man/3/system)


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

[stat 구조체 관련 파일 정보 불러오는 함수](https://cokk.tistory.com/51)

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
  * [bash 쉘을 이용해 스크립트 만드는 방법](https://poorman.tistory.com/316)
  
* 로그파일 생성 방법
  - 본 프로젝트에서의 로그파일 사용 목적 : 
    -  생성된 백업 디렉토리에 하나의 로그파일 생성 & 기록
    - [수행시간] 수행내용 형태로 로그파일 작성
    - add, remove, recover 명령어 실행 성공 시 로그파일에 기록
    - 시간 순서대로 로그 작성될 수 있도록 동기화 수행  
 - [로그파일 갱신하는 쉘 스크립트](https://guinbun.tistory.com/28) <br>
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
    * 연결리스트 관련 함수 구현 **(02.09 진행 중)**
      * ~~연결리스트 초기화 함수 initList()~~ **(02.09 완료)**
      * ~~연결리스트에 노드 추가 함수 addNode()~~ **(02.09 완료)**
      * ~~연결리스트에서 노드 찾는 함수 findNode()~~ **(02.09 완료)**
      * remove 명령어 실행을 위해 연결리스트에 노드 삭제 함수 removeNode()
  * ~~./ssu_backup <디렉토리 생성 경로 입력> 구현~~ **(02.09 완료)**
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
     - [로그파일 작성 예시](https://m.blog.naver.com/PostView.nhn?blogId=ew32&logNo=150168169124&proxyReferer=https:%2F%2Fwww.google.com%2F)
     
 * main 함수에 경로를 인자로 넘겨주기
   ![image](https://user-images.githubusercontent.com/66112716/107370556-79b89000-6b26-11eb-9793-d0cf1fb71e8d.png)
<br>
    -> argv[1]에 백업디렉토리 생성할 경로 저장됨. <br>
    -> mkdir [argv[1]에 저장되어있는 경로] 이용해 입력한 위치에 백업 디렉토리 생성
    
   * 분기문으로 각 조건에 따라 다르게 처리 <br>
    1. 인자 없는 경우 : ```getcwd()```로 현재 작업 경로 알아와서 그 아래에 ```mkdir``` <br> 
    2. 인자 2개 이상인 경우 : usage 출력 (argv 인덱스 개수 조건으로 걸어 printf("사용법 출력") <br>
    3. 디렉토리 찾을 수 없는 경우 : *디렉토리 찾을 수 있는지 검사하는 함수 정의해 호출* <br>
    4. 디렉토리 접근 권한 없는 경우 : *디렉토리의 접근 권한 확인하는 함수 정의해 호출 : (https://pliss.tistory.com/95)* <br>
  
* mkdir 함수 or 명령어 참고 자료
  * [mkdir 함수](https://shaeod.tistory.com/322) (https://www.it-note.kr/205)
  * [터미널 명령어 mkdir, system() 사용](https://m.blog.naver.com/PostView.nhn?blogId=skout123&logNo=50133723008&proxyReferer=https:%2F%2Fwww.google.com%2F)

    
#### 구현 중 질문 사항
* 명세 : ssu_backup 프로그램 실행 시 백업 디렉토리를 생성할 경로를 인자로 입력<br>
         ssu_backup 실행 후 20190000>와 같은 프롬프트 출력 (공백없이 학번 + '>') <br>
   -> ~~./ssu_backup으로 vi 편집기에서 프로그램을 실행시키면 20190000>이라는 학번이 나오고, 그 뒤에 상대경로 or 절대경로를 바로 입력?~~ <br> 
   ~~아니면 들어가면 "디렉토리를 생성할 경로를 입력하시오 :" 라는 문구를 띄운 뒤 사용자로부터 경로를 입력받으면 그 뒤에 20190000>과 같은 프롬프트를 출력?~~ <br>
   -> ~~명세 3p의 add 명령어 실행 예를 보면 ```20190000>add test1.txt 5``` 와 같이 프롬프트 출력 뒤 바로 ```명령어 filename period```가 나오는데 경로 입력할 때는 '학번>'이 안니오는 것?~~ <br>
  -> **해결.** gcc 컴파일 후 ./ssu_backup <디렉토리 생성할 경로>의 인자를 넣어 해결
  -> **해결.** printf("20190000>");으로 찍는 것임. 프롬프트 출력 방법을 변경하는 것 X
  -> **해결.** 본인의 학번 적는 것
  
* 터미널 명령어 ```mkdir```와 동일한 기능을 위해 ```int mkdir(const char *dirname);```을 사용해야할까? ```system(mkdir "~");```을 사용해야 할까?

------
### 21.02.10 (수) 프로젝트 진행 계획 및 보고
#### 210210 프로젝트 진행 계획
* 연결리스트 관련 함수 구현
  * remove 명령어 실행을 위해 연결리스트에 노드 삭제 함수 removeNode() **(02.10 진행 중)**
  * main 함수에서 입력받은 명령어, 파일명, 백업주기 토큰으로 분리해 구조체의 멤버에 저장하는 함수 splitByToken()
  * 연결리스트 (백업리스트)에 저장되어있는 백업할 파일의 개수를 세는 함수 calcFileCnt() **(02.10 진행 중) -> 추가 구현할 것**

* 백업 기능 관련 함수
  * main 함수에서 디렉토리 접근 권한 여부 확인하는 함수 checkAccessDir() **(02.10 진행 중)**
  * ~~main 함수에서 입력받은 디렉토리를 인자로 받아 프롬프트 출력 및 명령어 입력을 받는 함수 printPrompt()~~ **(02.09 완료)**
  
#### 지난 시간 코멘트
* mkdir 기능을 수행할 때, system() 함수 사용 대신 다른 방법 사용 권장
* github 코드 업로드 문제 : ```pull``` 해주기
  
  
#### 구현 방향 및 학습 내용
* calcFileCnt() 구현 중 백업리스트의 백업할 파일(노드) 개수를 세는 작업에서 어떠한 조건을 충족하면 cnt++을 해줄지 추가적으로 고민해볼 것. <br>
  -> 사용자가 입력한 경로에 생성되는 백업 디렉토리의 이름을 통일하여 그 디렉토리만 열어서 읽어오거나, 다른 부분에서 통일시킨 뒤 파일을 만들어야할 것 같음.

* removeNode() 함수 구현 참고 자료
  - (https://www.geeksforgeeks.org/delete-a-linked-list-node-at-a-given-position/)
  - (http://blog.naver.com/PostView.nhn?blogId=hmin011&logNo=150154090477)
  
* splitByToken() 함수 구현 중 공백문자를 기준으로 2번째 저장되는 토큰은 node 구조체의 fileName으로, 3번째 저장되는 토큰은 fileInfo의 filePeriod 멤버에 저장 <br>
  -> 구조체의 멤버 선언이 잘못 된 것으로 판단됨. 수정하기 <br>
  -> 첫번째 토큰은 명령어. 명령어는 구조체 멤버에 저장하는 것이 아닌 해당 명령어에 따른 명령어 기능 정의 함수를 호출하여 사용하기.
  
* checkAccessDir() 함수 구현 방향
  * main 함수에서 인자로 입력받은 argc와 argv를 바탕으로 해당 경로에 백업 디렉토리를 생성할 수 있는지의 접근 권한을 확인하는 기능
  * 접근 권한 확인을 마친 절대경로를 따로 저장하기 위해 main 함수에서 ```char *backupdir```을 생성하고 동적할당을 해주었음. <br>
    -> 접근 가능한 경로이면 checkAccessDir 함수에서 해당 경로를 리턴하고, 이 리턴 값을 main함수의 backupdir에 저장해 printPrompt의 인자로 넘겨 함수를 호출하는 방법으로 구현할 예정.
  * 경로로의 접근이 가능한 조건을 어떻게 확인할 수 있는지 학습하기.
  
#### 구현 중 질문 사항
* calcFileCnt() 함수에서 ```strcmp(dir -> d_name, "..") == 0```, ```strcmp(dir -> d_name, ".") == 0```일 경우에 대해 분기문을 작성하고 continue를 해야할까? <br>
  -> 명세에서 인자가 없는 경우 current working 디렉토리 밑에 백업 디렉토리 생성 및 백업하는 경우 **현재 작업 디렉토리**를 열어야 하므로 디렉토리 관련 함수를 구현한 뒤 추가적으로 조건을 넣어줄 예정

------
### 21.02.15 (월) 프로젝트 진행 계획 및 보고
#### 210215 프로젝트 진행 계획
* 연결리스트 관련 함수 구현
  * ~~remove 명령어 실행을 위해 연결리스트에 노드 삭제 함수 removeNode()~~ **(02.15 구현 완료)** 
  * ~~main 함수에서 입력받은 명령어, 파일명, 백업주기 토큰으로 분리해 각각의 함수 호출, 백업주기 저장하는 기능 printPrompt에 추가~~ **(02.15 구현 완료)**
  * ~~백업 실행 중인 백업리스트(노드) 모두 출력하는 list 기능 위해 연결리스트의 노드 출력하는 함수 printBackupList()~~ **(02.15 구현 완료)**
  
* 백업 기능 관련 함수
  * main 함수에서 디렉토리 접근 권한 여부 확인하는 함수 checkAccessDir() **(02.15 진행 중)**  <br>
    - ~~파일 및 디렉터리 접근 권한 확인을 위한 멤버 st_mode 활용법 학습 및 관련 예제 코드 작성해 연습~~ **(02.15 완료)**

  
#### 구현 방향 및 학습 내용
* 노드 삭제 함수 removeNode() 구현 중, 이중 연결 리스트에서의 노드 삭제 방법 학습 <br>
  [deleteNode()](https://movahws.tistory.com/113) <br>
  -> 구현 방향 findNode()와 동일한 방법으로 curr->fileName을 찾아 해당 노드의 next, prev 연결 뒤 free 처리하여 해결
  
* [연결리스트 관련 함수 구현 참고 자료](http://ehpub.co.kr/tag/%EC%97%B0%EA%B2%B0%EB%A6%AC%EC%8A%A4%ED%8A%B8%EC%97%90%EC%84%9C-%EB%85%B8%EB%93%9C-%EC%A0%9C%EA%B1%B0/)

* 파일의 정보를 저장하기 위한 구조체가 별도로 필요하지 않다고 판단 <br>
-> fileInfo 구조체를 삭제하고 Node에 파일의 정보들을 멤버로 모두 저장할 수 있도록 수정

* 파일의 접근 권한 확인하기 위한 함수 checkAccessDir() 구현 방법
  - stat 구조체 및 dirent 구조체 사용하여 구현 예정
    - stat 구조체의 멤버 중 ```st_mode``` 확인해 접근권한 살피기 <br>
    - ```st_mode``` : 파일의 종류와 file에 대한 access 권한 정보, 파일의 종류 체크하는 POSIX macro
    
* 파일 권한 정보 확인하기 위한 st_mode 활용 예제 및 학습내용
[st_mode](https://www.it-note.kr/173)
![image](https://user-images.githubusercontent.com/66112716/107954300-9f8adc80-6fdf-11eb-8b4d-4059b9bffa65.png)

#### 구현 중 질문 사항
* printPrompt() 함수에서 토큰을 분리해 첫번째 문자열(명령어), 두번째 문자열(백업할 파일 경로), 세번째 문자열(백업 주기) 중 세번째 문자열을 토큰분리와 동시에 형변환하는 방법<br>
 -> **sol.** [atoi strtok()](https://m.blog.naver.com/PostView.nhn?blogId=bestheroz&logNo=66531604&proxyReferer=https:%2F%2Fwww.google.com%2F)
------
### 21.02.16 (화) 프로젝트 진행 계획 및 보고
#### 지난 시간 피드백
* 접근 권한 확인 함수 access() 사용할 것
* removeNode() 함수 작성 시 free() 사용 X -> 세그멘테이션 오류 가능성 높음

#### 구현 방향 및 학습 내용
* access() 함수 사용 방법 [access()](https://jdm.kr/blog/76)
  * ```int access (const char *pathname, int mode);```
    * 헤더 : <unistd.h>
    * 첫번째 인자 : 파일이나 디렉토리 전체 이름
    * 두번째 인자 : 검사할 내용
    * 리턴 값 : 
      - 0 : 기능 or 파일이 존재함
      - -1 : mode에 대해 하나 이상 거절되었거나 에러가 있음. 자세한 내용은 errno에 세팅 됨.
    * mode 값에 지정하여 사용할 수 있는 상수
      - R_OK : 읽기 가능?
      - W_OK : 쓰기 가능?
      - X_OK : 실행 가능?
      - F_OK : 파일 존재?
  -> 본 프로젝트 구현에서의 접근권한은 ```int mode = R_OK & W_OK```로 지정하여 읽고 쓸 수 있는지를 조건으로 진행
  
* main() 함수에서 checkAccessDir() 함수 호출 시 넘겨준 argc, argv 인자의 개수에 따라 ```./ssu_backup /home/user/.../test1.txt``` 와 같은 실행 형태가 아닐 경우 Usage 출력하도록 함. <br>
  -> 정상적인 수행의 경우 argc == 2여야 함. (argv[0] : ./ssu_backup, argv[1] : 절대경로)
  
* checkAccessDir()에서 고려해야 할 조건
  1. 상대경로(같은 디렉토리 안에 있는 경우)를 입력받았을 때, 이를 파일작업이 가능하게 할 수 있도록 절대경로로 바꿔주어야함.
    - ```_fullpath()```함수 사용해 상대경로로 입력된 인자를 절대경로로 바꿔주는 작업 진행 가능.
    - [```_fullpath()``` 함수](https://docs.microsoft.com/ko-kr/cpp/c-runtime-library/reference/fullpath-wfullpath?view=msvc-160)
  2. 인자 X 경우 : 현재 작업 dir 밑에 백업dir 생성 ```mkdir()```함수 사용해 현재 디렉토리(current working directory) 밑에 디렉토리 생성된 것 확인 완료.
    ```
    int main() {
      DIR *dir_info;
      struct dirent *dir_entry;
      
      mkdir("test_A", 0755); //실행파일이 있는 곳에 생성
      mkdir("test_B", 0755); //실행파일이 있는 곳에 생성
      
      dir_info = opendir("."); //현재 디렉토리 열기
      if (NULL != dir_info) {
        while(dir_entry = readdir(dir_info)) {
          printf("%s\n", dir_entry->dir_name);
         }
        closedir(dir_info);
      }
    }
    ```
      
  3. 인자로 입력받은 dir 찾을 수 X : https://incleaf.tistory.com/10 : c언어로 CMD 명령어 실행 방법 (system() 지양)
    - dirent 구조체 사용해서 opendir의 리턴 값이 NULL이면 찾을 수 없는 것으로 처리 가능할 듯!
    - [dirent 구조체로 인자로 입력받은 디렉토리 찾기](http://blog.naver.com/PostView.nhn?blogId=ambidext&logNo=221148484739&categoryNo=65&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView&userTopListOpen=true&userTopListCount=5&userTopListManageOpen=false&userTopListCurrentPage=1)
    
  4. 인자로 입력받은 디렉토리가 dir 파일 X : stat 구조체에서 ```if(S_ISDIR(statbuf.st_mode))```이면 디렉토리파일임을 확인할 수 있도록 구현.
    - [파일 관련된 정보 얻기 위한 stat함수 중 POSIX macro](https://www.it-note.kr/173)
  5. 인자로 입력받은 dir 접근 권한 X : access() 함수의 예외로 처리
  
#### 구현 중 질문 사항
* checkAccessDir()에서 고려할 조건 중 3번의 경우 cmd 명령어 ```find```나 ```dir```를 통해 인자로 입력받은 dir 찾을 수 있는 것으로 알고 있습니다. ```windows("find <dirname>");```와 같이 함수에서 입력받은 dirname을 넘겨 사용할 수 있나요?<br>
  -> ```DIR *dir = opendir(); dir == NULL```이면 해당 디렉토리 찾을 수 없는 것으로 처리해도 되나요??
  -> ```stat()``` or ```lstat()``` 함수 이용해서 구현해도 가능. opendir() 사용해도 가능!

------
### 21.02.17 (수) 프로젝트 진행 계획 및 보고
#### 지난 시간 피드백
* 절대경로를 상대경로로 바꿀 수 있는 방법 1
  - ```realpath()```함수를 통하여 상대경로 값을 인자로 넘겨 절대경로로 바꾸어줄 수 있음.
* 절대경로를 상대경로로 바꿀 수 있는 방법 2
  - 명세 상 조건: 상대경로는 같은 디렉터리에만 있을 때로 정의함.
  - ```getcwd()```를 이용해 현재 디렉터리를 알아낸 다음, ```sprintf()```이용하여 ```getcwd()/dirname```으로 경로를 변경해줄 수 있음.

#### 구현 방향 및 학습 내용
* 같은 디렉터리 내에 존재하는 상대경로를 프로그램 실행 시 인자로 전달받았을 때, ```getcwd()```로 현재 디렉터리를 알아와 임시 버퍼에 저장한 뒤 ```sprintf()```로 백업 디렉토리 만들어줌.

* ```realpath()```함수 사용하여 [실행파일의 절대경로를 얻어내는 방법](https://webnautes.tistory.com/1448) 

* ```mkdir()``` 사용하여 인자로 받은 경로에 백업 디렉토리 생성하는 작업 구현 계획
  - 먼저 ```realpath()```함수 사용해 상대경로를 절대경로로 바꿔놓음. (tmpdir 변수에 저장)
  - ```sprintf()```로 변환된 절대경로에 backup_directory 추가해서 저장. (backupdir 변수에 저장)
  - ```mkdir(backupdir, 0775);```으로 디렉토리 파일 생성
  - backupdir 리턴
-> 인자로 전달받은 경로에 백업디렉토리 만드는 방법이 이게 맞는지 의문..

* **compare** 기능 구현 시 ```mtime``` 비교하는 방법
  - [stat 구조체의 mtime과, tm 구조체의 mtime을 계산하는 방법](https://reakwon.tistory.com/40)
  ![image](https://user-images.githubusercontent.com/66112716/108219723-55d5f980-7179-11eb-82af-15128cf16d37.png)
  - [tm 구조체를 사용하여 mtime ](https://modoocode.com/109)
  - ```localtime()```을 통해 mtime 계산 [localtime() 함수 사용 방법](https://modoocode.com/120)
    - ```struct tm* localtime (const time_t* timer);```
    - 인자 : time_t형 변수를 가리키는 포인터
    - 리턴 값 : 멤버들이 초기화 된 tm 구조체를 가리키는 포인터
  - 파일의 크기를 비교하는 과정에서 cmd 명령어의 cmp 사용하려면 system() -> 파일 크기 비교하는 ```sizecmp()``` 함수 or stat 구조체의 ```st_size```멤버 비교
    - [파일 크기 비교](https://www.enqdeq.net/148)

#### 구현 중 질문 사항
* 프로그램 실행 시 절대경로 인자가 없을 경우, 현재 작업 디렉토리 밑에 백업 디렉토리를 생성할 때 ```backup_dir```의 이름으로 저장해야하나요? 자유롭게 백업 디렉토리명을 생성해도 되는 것인지 궁금합니다!
   -> 자유로 해도 가능

* 명세 2p에서의 로그파일 작성 예시에서는 ```<절대경로>/~~~.txt```와 같이 txt 파일로 저장되어 있는데, 백업파일으로 추가하는 파일의 형식은 txt파일로 제한해두었다고 생각하고 구현해도 괜찮은가요??
  -> 모든 확장자가 다 가능하도록 구현
  
  ------
### 21.02.18 (목) 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용
* compare 명령어 : ```size_t size;```를 만들어 stat 구조체의 st_size를 받아 비교하도록 구현 <br>
  -> stat 구조체에 저장되어있는 파일의 크기를 계산해 리턴하는 함수 ```getFileSize()``` 함수를 따로 구현하여 한번에 작업할 수 있도록 함.
  - 고려 사항 (에러 처리) : 
      - fileName이 존재 X : ```opendir()```로 ```fopen()```이 되지 않으면 에러 처리
      - 일반 파일이 아님 : ```S_IFREG(statbuf.st_mode)``` 이용해 리턴값 != 0이면 에러 처리
        - [일반파일임을 확인하는 방법](https://ehpub.co.kr/tag/s_isreg/)
      - 입력 인자가 2개가 아님 : 
        - 구현 아이디어 : 만약 인자가 1개 또는 0개일 때(에러 발생 조건) 함수 자체에서의 fileName1과 fileName2는 전달받은 인자가 없기에 NULL일 것임. 둘 중 하나라도 NULL인 상태이면 에러처리. 
  - localtime() 함수로 파일의 mtime을 계산하여 리턴받고 이를 비교할 때, mtime이 str 형태로 저장되기에 비교 연산자(==)가 아닌 strcmp로 두 값을 비교해주었음.
  - size_t는 ```unsigned int```타입이기에 비교연산자로 비교.
  
* list 명령어 : 이전에 구현한 linkedlist의 정보를 출력하는 ```printBackupList()``` 함수 호출.

* ls 명령어 : dirent 관련 함수와 getcwd() 함슈 사용을 통해 구현 -> dirent구조체의 d_name 순회하여 출력
  - [ls 명령어 구현](https://go-it.tistory.com/4)

* add 명령어 : 백업해야하는 파일 백업리스트에 새로 추가 ```add test1.xt 5```
  - 연결리스트에 노드를 추가하는 함수 addNode() 호출하고 연결리스트에 연결하는 작업.
  - Node의 구조체 멤버(파일이름, 파일의 절대경로, 파일의 백업주기)에 인자 받아와 저장하는 작업.

* exit 명령어 : ```exit(0);```정상 수행으로 프로그램 종료 명령어 사용


#### 구현 중 질문 사항
* '에러 발생 시 에러 처리를 한 뒤 프롬프트로 제어가 넘어감'이라고 나와있는 부분을 ```exit(1);```를 사용해 처리하였습니다. 프롬프트("학번>")를 출력하고 그 안에서 명령어를 입력하여 처리하는 부분이 printPrompt()라는 함수로 구현되어 있어서 제어를 이 프롬프트 기능을 수행하는 함수로 넘어가도록 하는 기능 구현을 방법을 찾지 못했습니다.. 
  프롬프트로 전달된 인자는 그대로인 상태에서 이 프롬프트 함수로 다시 돌아갈 수 있도록 어떻게 할 수 있나요??

* compare 기능에서 입력 인자가 2개가 아닌 경우를 (인자가 1개 or 0개) ```compareFunc()``` 함수의 fileName1이나 fileName2중 하나라도 NULL일 것이기에 이를 조건으로 에러처리를 하였는데, 인자가 2개 이상인 경우에는 어떻게 처리를 해주어야 하나요??
  - 해당 질문에 대한 본인 아이디어 : 프롬프트(```printPrompt()```)에서 호출을 할 때 ```strtok()```로 토큰을 분리해 filePath, filePath2를 ```compare(fileParh, filePath2);```로 넘겨주었는데 이 때 사용자가 입력한 문장에서 몇개의 토큰이 분리되는지를 구별해 그 개수를 카운트한 뒤 프롬프트 함수 자체에서 2개 초과 or 미만 시 에러처리를 해주는 방법을 사용해도 될 것 같음.

  ------
### 21.02.19 (금) 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용
* 지난 시간 질문 1에 대한 피드백 : while(1)로 프롬프트 제어, exit가 나올 경우에만 ```exit(0)``` or ```return``` 후에 프로그램을 종료하도록 작성.
  - 추가적인 작업 : 주어진 명령어 이외의 다른 명령어 입력될 경우 메시지 출력 후 다시 프롬프트로 돌아오도록.

* ls, vi 명령어의 경우 ```system()``` 함수를 사용하여 구현.
  - 구현 방법 : ```fgets()```로 프롬프트에서 한 줄을 받아옴.

* system() 함수 사용해 ls, vi 기능 구현 완료. 지정된 명령어가 아닌 다른 명령어 입력 시 메시지 출력 후 넘어가도록.
  - [system() 함수 사용하여 cmd 명령어 기능 구현하기](https://m.blog.naver.com/PostView.nhn?blogId=skout123&logNo=50133723008&proxyReferer=https:%2F%2Fwww.google.com%2F)

* ls, vi 기능에서 ```ls <dirname>```, ```vi <filename>```의 형태로 명령어 작성하는 방법 구현 방향
  - ```strtok()```함수를 사용하여 두번째 인자로 받아들인 내용을 dirname과 filename으로 저장함.
  -  ```strcat()```함수를 사용하여 명령어 토큰(ls or vim)과 dirname, filename을 합쳐 ```system()``` 함수의 인자로 넘김.

* remove 명령어 구현 방향
  - 명령어 기능 : 백업 리스트에 존재하는 파일의 백업을 중단하기 위해 백업 리스트에서 삭제
  - 연결리스트 관련 함수 ```findNode()```를 사용해 인자로 받은 노드의 존재여부를 확인
  - ```findNode()```의 리턴노드 값을 삭제할 노드인 구조체 변수 ```removeNode```에 저장
  - 저장된 노드를 ```removeNode()``` 함수를 사용하여 리스트에서 삭제

* 로그파일에 수행시간을 기준으로 수행 내용을 기록하는 방법
  - 수행 시간을 측정하여 출력하는 방법 : ```compareFunc()```함수에서 사용하였던 tm 구조체를 통해 구조체의 멤버로 가지는 ```tm_year```, ```tm_mon```, ```tm_mday```를 통해 수행 시간의 앞부분을, ```tm_hour```, ```tm_min```, ```tm_sec```을 통해 수행 시간의 뒷부분을 작성
    - tm 구조체의 멤버들은 모두 int형이므로 이를 시간 순서대로 작성되도록 하기 위해서는 정렬함수를 작성하여 업데이트 될 때마다 순서대로 정렬하는 작업 진행.
  - add, remove, recover 명령이 실행되는 경우를 분기문으로 나누어 해당 명령어가 성공적으로 수행되는지의 여부에 따라 adder, generated, deleted의 내용을 작성.

#### 210219 이후 계획
* 아직 스레드를 아무 곳에서도 사용하지 않은 상태. 주말동안 스레드가 이 프로그램에서 어떠한 기능에 사용되는지 생각해보고 바로 구현에 옮길 수 있도록 공부하고 다시 구상해볼 것.
* 작업 간 수행 시간 충돌이 일어날 수 있기에 동기화 작업을 진행하여주는 MUTEX 사용도 하지 않은 상태. 간단한 예제코드를 만들어 동시에 작업이 진행될 때 동기화가 제대로 되는지 확인해보고 본 프로젝트의 구현에도 적용시켜볼 것.
* 아직 구현이 마무리되지 않은 add, recover 명령어에 대해 구현할 것.

  ------
### 21.02.20 (토) 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용
* **로그파일 생성 후 내용 작성** : [로그파일 작성](https://m.blog.naver.com/PostView.nhn?blogId=ew32&logNo=150168169124&proxyReferer=https:%2F%2Fwww.google.com%2F)
  - (https://qmffor09.tistory.com/85)
  - 로그파일 작성하는 함수 ```write_log()``` 작성. -> ```#include <sys/time.h>``` 함수 이용해 로그가 찍히는 시간대를 파악할 수 있음.
  - 날짜/시간을 스트링으로 변환하는 함수 ```strftime()``` : 로그파일 작성, compare 함수에서 사용되는 time을 string형으로 변환하는 기능(logfile에서는 시간순서대로 정렬하게 되어 있으므로 이러한 함수가 있다는 것을 알아두자!)
    ```#include <time.h>
       size_t strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr);
    ```
  - 로그파일 작성 시 이를 출력하기 위해 로그파일에 기록되어야 하는 메시지를 단위로 나누어봄.
    - [수행시간] : 이를 tm 구조체에서 읽어와 int형으로 관리
    - 절대경로 (Node 구조체에서 absPath 멤버에 저장되어있는 값)
    - 파일 이름(Node 구조체에서 fileName 멤버에 저장되어있는 값)
    - 백업 수행 시간 (위의 수행시간과 동일한 내용을 _190311153325와 같이 출력)
    - 수행 내용 (added, generated, deleted) <br>
   -> 구현 아이디어 : ```listFunc()```에서 노드에 저장되어있는 파일명, 주기를 읽어오는 것과 같이 로그파일에 출력되어야 하는 정보를 하나의 구조체로 정의하여 그 멤버들을 출력하는 방법으로 구현?!
   
* 멘토님 조언 : 명령 프롬프트에서 ```scanf()```가 아닌 ```fgets()```로 받아와야 함.
  - ls, vim 명령어에서 굳이 토큰을 다른 문자배열에 저장하지 않고 뒤의 개행문자를 제거하여 바로 system() 함수의 인자로 넘겨 작업하도록 함. <br>
  -> 코드 수정 완료
  
* **add 명령어 구현** : 연결리스트, 파일을 추가할 절대 경로, 추가할 파일 명, 백업 주기를 인자로 받아 구현.
  - 인자로 전달받은 절대경로를 ```opendir()```의 인자로 넘겨 디렉토리 열기
  - 인자로 전달받은 fileName으로 노드를 만들고, 이를 리스트에 추가한 뒤 리스트 목록(backupList.list)에 추가하는 작업
  - *인자로 전달받은 백업 주기마다 파일을 백업하는 작업을 수행하여야 함.

* 스레드 공부 내용을 바탕으로 한 사용 방법 : 
  - 스레드 : 프로세스 내에서 실제로 작업을 수행하는 주체
  - 스레드 사용을 통해 백업주기를 기준으로 해당 시간만큼 파일을 백업시키는 작업 진행하도록 구현 예정.

* add 명령어의 기능 중 추가된 파일을 백업리스트에 추가하는 기능이 필요하다고 판단. ```addFileToList()``` 함수를 구현하여 파일의 이름을 리스트에 추가시킴.

* 연결리스트에서 노드를 만드는 함수 ```makeNode()```가 구현되어있지 않아 해당 함수 구현.

#### 구현 중 질문 사항
* 로그파일을 시간 순서대로 작성하는 동기화 작업은 단순히 tm구조체를 통해 읽어온 시간을 바탕으로 정렬을 진행하여 작성해도 되나요?? 스레드에 대한 설명에서 동기화 작업을 진행할 때 MUTEX를 사용하는 방법을 말씀해주셨는데, 로그파일에서도 동기화를 mutex 사용으로 진행하여야 하는지 여쭤보고 싶습니다.

------
### 21.02.21 (일) 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용
* ```pthread_create()```함수를 이용하여 add 명령어에서 파일을 추가할 경우 파일:스레드 = 1:1으로 스레드를 생성하는 함수 구현 중

* 스레드 관련 구현 내용
  - 백업주기만큼 백업을 진행하기 위해 ```sleep()```함수의 인자에 해당 파일의 filePeriod를 넣어 해당 백업 주기마다 백업을 진행하도록 함.
  - ```pid_t pid``` : 프로세스 아이디, ```pthread_t tid``` : 스레드 아이디 즉, 프로세스 식별자 & 스레드 식별자
  - ```pthread_self()```함수를 통해 현재 쓰레드의 아이디를 얻어올 수 있음. [파일별로 스레드 생성하는 방법](https://bitsoul.tistory.com/167)
  - 수행 시간을 [연월일 시분초]로 가져오기 위한 방법 : ```time_t timer```, ```struct_tm *t```tm 구조체를 통해 
    1. 현재 시간을 초 단위로 얻고 (```time_t timer = time(NULL);```)
    2. 초 단위로 얻은 시간을 분리해 구조체에 넣어주는 작업 (```struct tm *t = localtime(&timer);```)을 진행
    - [참고 자료 1](https://rosagigantea.tistory.com/229), [참고 자료 2](https://www.it-note.kr/141)
    - int형으로 리턴받은 년월일 시분초를 전체 시간을 나타내는 perform_full으로 바꾸기 위해 ```itoa()``` 함수 사용 ([itoa()](https://com12127.tistory.com/4))

* 스레드 생성 예제 학습 코드 실행 화면
![image](https://user-images.githubusercontent.com/66112716/108627354-77482580-7498-11eb-97c3-7f475e1bbc61.png)

* 스레드 수행시간 & 수행 항목 로그파일에 기록하는 예제 코드 실행 화면
 ![image](https://user-images.githubusercontent.com/66112716/108628520-ca24db80-749e-11eb-800c-f629c34a2cb2.png)
  - 스레드가 제대로 생성되고 수행시간과 수행 내용의 일부가 test.log파일에 저장되는 것 확인할 수 있음.
  - ```pthread_mutex_lock()```, ```pthread_mutex_unlock()```함수를 사용하여 동기화를 진행하였으나 더 학습이 필요할 것으로 보임.
  - 오류 : 가장 마지막에 생성된 스레드의 정보만이 로그파일에 기록되어 디버깅 과정 중에 있음. <br>
    -> 해당 예제를 완료한 뒤 백업 프로그램 스레드 함수에 해당 기능을 추가하면 될 것으로 보임.

------
### 21.02.22 (월) 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용
* **mutex** : 여러 개의 쓰레드가 공유하는 데이터를 보호하기 위해 사용.
  - 보호하고자 하는 데이터를 다루는 코드 영역을 한번에 하나의 쓰레드만 실행 가능하도록.
  - ```pthread_mutex_init(pthread_mutex_t mutex_lock, NULL)``` : 뮤텍스 객체를 기본 특성으로 초기화 (add 명령어 함수 구현부에서 뮤텍스를 먼저 초기화해준 뒤, 스레드를 생성하는 로직)
  - ```pthread_mutex_lock()```과 ```pthread_mutex_unlock()``` 사이에서는 **공유하는 변수에 하나의 스레드만 접근 가능하도록** 수행할 수 있음, 먼저 수행되는 스레드가 종료될 때까지 **다른 스레드 : 대기상태로 존재**, 앞선 스레드가 lock ~ unlock 영역을 빠져나오면 진입
  
* mutex를 사용하여 멀티스레드의 동기화 진행 예제 코드 실행 결과
 ![image](https://user-images.githubusercontent.com/66112716/108715062-b12f2f80-755d-11eb-9a5a-f85d0b25dceb.png)
  - 뮤텍스를 사용하여 스레드 공유 자원을 나타내는 변수 g_count를 통해 하나의 스레드씩 실행됨을 확인

![image](https://user-images.githubusercontent.com/66112716/108719930-88119d80-7563-11eb-982c-e1bcbadb4bca.png)
  - 스레드 실행 시간을 ```struct_tm```구조체와 ```time_t```를 사용해 ```sleep()```함수로 수행의 지연을 주었음에도 모두 같은 시간으로 수행시간이 찍힘.
  - ```clock_gettime()```함수의 사용을 통해서도 시간을 측정할 수 있음. add와 remove, recover 명령어에서 명령어를 실행할 때에 수행 시간을 구해 로그작성 함수에 fulltime을 넘겨야 하는지, 스레드 수행 부분에서 수행 시간을 구해 로그 작성 함수에 넘겨야 하는지 더 생각해보기.

* 스레드 생성과 뮤텍스를 이용해 멀티스레드의 동기화를 진행하는 방법에 대해서는 예제코드를 실행해보며 어느정도 숙지가 된 것으로 느껴짐. 210223 (화)부터 다시 프로그램 구현으로 돌아가 add, remove, recover 명령어에서 이를 적용시켜 구현할 예정.

------
### 21.02.23 (화) 프로젝트 진행 계획 및 보고
* 지난 시간 구현 방향에 대한 피드백 : 스레드 수행 시간을 구하는 과정 중 ```struct_tm```구조체와 ```time_t```를 사용해 ```time()```, ```localtime()``` 함수로 측정하는 것이 맞음. 계속 구현 진행할 것!

#### 구현 방향 및 학습 내용
* ```remove``` 명령어 수행 성공 시 로그파일에 "[수행시간] 수행내용"의 로그를 작성하도록 구현.
  - ```removeFunc()``` 함수 자체에서 함수가 호출되어 파일 삭제가 진행될 때의 수행 시간을 구하고, 이를 문자배열 logmsg에 저장해 ```write_log()```함수로 넘김.
  - 스레드를 멈추기 위한 [pthread_join()](https://y0ubat.tistory.com/78)
  - 로그파일에 ```removeFunc()```의 인자로 입력받은 fileName 노드의 멤버인 백업 파일의 절대경로(absPath)를 작성하기 위해 ```findNode()```함수로 찾은 removeFile 노드의 absPath를 저장. (```strcpy()```사용해 함수 내부 문자배열에 저장 후 노드 삭제)
  
*  add 명령어를 실행함과 동시에 생성되는 스레드를 remove 명령어를 실행할 때에 소멸시켜주도록 구현.
  - [스레드 종료 후 리턴 값 받아옴](https://bitsoul.tistory.com/160)

* 로그파일에서 작업 디렉토리를 구하는 ```getcwd()```, 디렉토리를 생성하는 ```mkdir()```, 작업 디렉토리를 변경하는 ```chdir()``` 
  - [디렉토리 관련 함수](http://forum.falinux.com/zbxe/index.php?mid=C_LIB&document_srl=408482)

* ```recover```명령어 본인이 이해한 로직
  1. main 함수를 실행할 때 ./ssu_backup <백업디렉토리 생성할 경로>
  2. 경로 확인 함수에서 백업 디렉토리 생성할 경로 바꿔서 backupdir 배열에 저장함
  3. add 명령어 실행 시 위의 백업디렉토리에 파일을 추가하고 period의 주기로 백업이 진행됨
  4. recover 명령어 실행 시 예를 들어 test1.txt 파일이 190423 231006에 생성되어 5초의 백업주기마다 백업되어 그 수행사항이 프롬프트에 순번과 함께 출력됨
  ```
  ex)
  0.  exit
  1.  190423 231011   13bytes
  2.  190423 231016   13bytes
  3.  190423 231021   17bytes
  4.  ...
    ```
  5. 사용자가 원하는 백업상태(예를 들어 2번의 백업 상태로 돌아가고자 함.)를 입력하면 2번의 백업 상태로 되돌아감
  6. 해당 test1.txt 파일(원본)이 2번의 백업 상태로 바뀌어 저장됨

* recover 명령어 구현을 위해 백업이 진행될 때마다 파일의 백업수행시간, 파일의 크기, 백업된 파일의 내용을 멤버로 저장하는 구조체를 따로 만들어 연결리스트로 관리하고, recover 명령이 수행될 때마다 해당 내용을 출력하는 방법으로 구현하는 것 어떨지? <
  -> 기존에 구현해놓은 initList, makeNode, addNode, deleteNode 등 연결리스트 함수에 더해 백업시간 기준 오름차순으로 순번을 출력하기 위해 정렬함수를 추가적으로 구현하여 노드의 연결 순서를 변경할 것. 
 
 
#### 구현 중 질문 사항
* ```recover``` 명령어 명세 관련 질문 : *사용자가 백업 파일을 선택하면 변경된 파일의 내용을 출력* 부분에서 예를 들어 test1.txt파일에 <br>
    ```
    1. 210223 102510 내용에는 "안녕하세요 저는 ~~~ 입니다.", 
    2. 210223 102517 내용에는 "안녕히가세요 저는 ~~~ 입니다."
    ```
    가 저장되어있다고 했을 때, 1번을 선택하면 프롬프트 창에 "안녕하세요 저는 ~~~ 입니다."(변경된 파일의 내용)가 출력되어야 하는 것인가요?? <br>
    그렇다면 test1.txt 파일은 가장 최근에 백업된 내용이 아닌 사용자가 선택한 순번의 백업수행 내용으로 돌아가야하는 것인가요??
    
    ------
### 21.02.24 (수) 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용
* 노드 정렬 함수 (백업 시간 기준) : 해당 명령어 파일에서는 tm_year, ... , tm_sec에 저장되어있는 int형 자료를 recovertime 변수에 sprintf()함수를 통해 문자열 배열로 담아 백업 수행 내역을 관리하는 노드 Backup_Node에 저장함. <br>
  -> 문자열 형태로 저장되어있는 시간을 오름차순으로 정렬하기 위해서는 이를 정수형으로 비교하여 정렬해야 함.
  - ```atoi(num)```함수를 사용하여 문자열을 숫자로 바꾸어 저장할 수 있음. [문자열 숫자로 바꾸는 atoi() 함수](https://dojang.io/mod/page/view.php?id=385)
  - 또는 형변환을 하지 않고도 바로 비교할 수 있는 방법
![image](https://user-images.githubusercontent.com/66112716/108935166-96a9a300-7690-11eb-9bba-f5b5844f9c47.png)
  - [노드의 특정 멤버를 기준으로 값을 비교하여 정렬하는 방법](https://wnsgml972.github.io/data%20structure/2018/05/07/datastructure_ascending_insert_node/) 또는 [자료구조 연결리스트 오름차순 정렬](http://blog.naver.com/PostView.nhn?blogId=sejin7307&logNo=140126970646) <br>
  -> 굳이 백업수행내용이 저장된 리스트를 정렬할 필요가 있는지 재고. 백업 내용이 수행되면 동기화를 적용한 스레드의 내용이 시간순서대로 로그파일에 기록되지 않을까 하는 판단. 예제코드 만들어 확인하는 .
  
* recover 명령어 실행 시 수행내용 로그파일에 기록하도록 구현.

#### 구현 중 질문 사항
* 로그파일에 기록되는 수행 내역이 added, generated, deleted인데 added = add 명령어 수행 시 작성되는 로그, generated = recover 명령어 수행 시 작성되는 로그, deleted = remove 명령어 수행 시 작성되는 로그가 맞나요??

    ------
### 21.02.25 (목) 프로젝트 진행 계획 및 보고

#### 구현 내용 중 질문사항에 대한 피드백
* recover 명령어 구현에 있어 백업 시간 순서대로 출력하는 방법에서 굳이 노드 정렬작업을 할 필요는 없어보임.
  - 백업 폴더에 ```<파일이름_날짜>```와 같은 형식으로 저장이 되어있음.
  - dirent 구조체 함수 ```opendir()```, ```readdir()```를 이용하여 파일에 해당하는 이름을 찾은 뒤 파일의 이름을 가져와 정렬한 뒤 출력하면 됨. 

* recover 명령에서 ```opendir()```, ```readdir()```를 사용하는 구현방법 권장 방향
  - recover 할 원본파일에 해당하는 파일이 백업디렉토리에 몇개 있는지 개수 카운트
  - 해당 개수만큼의 파일이름 저장하는 포인터 만들어 메모리 동적할당
  - 다시 opendir(), readdir()함수 이용해 이름 저장
  - 출력할 때 정렬하여 출력하는 방식

* 로그 기록에 대한 내용
  - ```added``` : add 명령어로 파일 추가
  - ```generated``` : 백업 수행할 때마다 기록
  - ```deleted``` : remove 명령어로 파일 삭제
  - *명세에 나와있는 recover 명령어는 로그에 별도로 작성되지 않음. (명세 오류) add와 백업수행, remove 명령어만 로그가 작성됨.*
  
#### 구현 방향 및 학습 내용
* **스레드 함수 구현**
  - 스레드 : add 명령어로 파일이 생성되고 스레드를 생성하는 작업과 동시에 기존에 생성된 스레드의 백업을 주기마다 실행하는 작업
  - pthread_self()함수를 이용해 스레드의 식별자를 반환해 BackupNode 멤버에 함께 저장 (백업 진행 시 접근할 수 있도록)
  - 동기화를 위해 각 명령어 함수에서 개별적으로 구현해놓은 로그 작성 코드를 thread_function() 함수에서 처리하도록 함.
  - 스레드 함수에서 파일의 정보를 stat 구조체에 저장하기 위해 ```stat()``` 함수를 사용해 fileName을 인자로 넘겨 스탯버퍼에 저장하는 작업 진행.
  - 스레드를 생성하는 ```pthread_create()```함수는 ```addFunc()```함수에서 사용하여야할 것 같은데, 스레드 생성 함수로 넘겨지는 인자들에 대해 구현에 어려움을 느끼는 중. 

* **recover 명령어 구현**
  - 백업이 수행될 때마다 백업된 파일의 내용을 저장하는 BackupNode의 개수를 카운트하는 함수를 통해 백업이 수행된 노드의 개수를 리턴받음.
  - add한 파일이 백업주기마다 백업이 진행된 시간과 파일 크기를 노드로 관리하도록 스레드 함수 또는 add 명령어 함수 구현하는 부분에 추가할 예정.
  - recover 명령어를 실행하면 입력한 파일명에 대해 순번과 함께 백업버전(백업시간)을 나타내게 되는데, 선택한 순번에 해당하는 백업버전을 어떻게 찾을지 고민 중.
    - 2차원 배열을 생성하여 ```arr[백업수행횟수 카운트][256]```로 파일의 백업시간과 파일크기를 str로 저장해 인덱스로 접근할까?
    - 만약 위처럼 2차원 배열로 저장된 버전들 중 210225230605 13bytes의 백업버전이 선택되었다면, 공백자 기준으로 토큰을 분리해 첫번째 토큰과 BackupNode -> backup_time을 비교해 해당 BackupNode의 file_content 내용을 strcpy()하는 방법으로 구현할 수 있을 것 같음.<br>
    -> 너무 복잡하고 어려운 접근방법같기도.. 전체 구현물이 실행되고 있지 않기에 이 방법으로 구현이 가능한지 간단하게 테스트코드 작성해 확인 과정 중.

    ------
### 21.02.27 (토) 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용
* **recover 명령어 명세**
  - 백업이 수행될 때마다 로그에 ```fileName.~_백업수행시간```으로 찍히는 시간이 파일의 백업수행 저장방법
  - 파일의 이름만을 알아도 백업된 파일에 대한 접근이 fopen()으로 가능해짐.
  - fopen() 사용 : 백업 디렉터리에 있는 절대경로를 확인할 수 있다면 파일 오픈 가능
  - BackupNode 구조체로 백업 수행 시간, 주기, 내용을 저장할 것 없이 파일이름과 크기만을 저장할 수 있으면 됨.
  - 파일의 이름을 알면 dirent 구조체 or stat으로 파일의 크기/이름 등에 대해 접근 가능

* **recover 명령어 구현**
  - ex) test1.txt 파일이 add 명령어를 통해 백업 디렉터리에 추가됨
  - 입력된 주기마다 test1.txt 파일이 백업됨
  - ```recover test1.txt``` 명령어가 실행되면, test1.txt에 대한 것을 백업 디렉터리에서 찾아 개수 count
  - count 수만큼 2차원 포인터를 동적할당
  - dirent 함수 opendir(), readdir()을 이용하여 파일을 열고 파일명을 넣어줌<br>
    -> count 수만큼의 파일이름이 생김
  - 순번과 같이 수행시간을 정렬하여 화면 출력
  - 분기문 안에서 사용자의 입력값과 일치한 순번(인덱스로 접근)의 파일으로 overwrite

* 함수 정의부를 위해 backupProgram.h 파일을 새로 만들어 헤더파일과 소스코드 파일 분기. 구조체도 해당 헤더파일로 옮겨 작업

* **add 명령어 구현**
- Node 구조체에 스레드 식별자를 저장하기 위해 ```pthread_t tid;```멤버를 추가하고 ```pthread_self()``` 함수를 사용하여 구조체에서 이를 함께 저장하도록 함
- Node 구조체에 stat을 통한 파일의 정보 중 ```st_size```를 저장
  - 프롬프트 함수에서 넘겨받은 연결리스트, 절대경로, 파일 이름, 백업주기를 생성된 노드의 멤버에 넣어줌.
  - 스레드를 생성하는 작업은 addFunc()에서, 생성된 스레드를 백업주기 간격으로 백업하는 작업은 thread_function()에서
 
 * **백업 기능 구현** 
  - 백업하여 만든 <파일명_백업시간>은 ```addFunc()```에서 ```makeNode()```로 계속 리스트에 추가할 예정
  - 파일의 정보는 stat 구조체가 관리하므로 ```strcat()```함수를 사용해 함수의 인자로 전달받은 파일명 뒤에 ```time_t st_mtime;```을 추가하여 생성할 예정(또는 기존에 작성해두었던 tm 구조체로 백업시간 계산을 하여 fulltime을 추가하는 것이 옳은 방법일수도 있을 것 같음)

* **remove 명령어 스레드 관련 추가 구현**
  - remove 명령어에서는 이미 생성되어있는 파일을 삭제해야하는 것. -> 즉 opendir()을 통해 삭제할 파일이름을 가진 파일이 몇개인지 확인 가능하며 이를 제거하면 됨.
  - ```pthread_self()```의 리턴 값을 비교하면 될까??
  - [pthread_exit() 함수를 통해 생성되어있는 스레드를 종료하는 예제](https://bitsoul.tistory.com/165)

    ------
### 21.02.28 () 프로젝트 진행 계획 및 보고

#### 구현 방향 및 학습 내용

* **구현된 코드 디버깅 진행 중 학습한 내용**
  - realpath() 함수 사용 시 ```realpath(절대경로로 변환할 상대경로, 변환된 절대경로 저장될 버퍼)``` : 리턴 값이 NULL이 아니면 성공적으로 변환됨. 성공적으로 변환되었을 경우 함수의 두번째 인자를 리턴해주면 됨. (절대경로로 백업 디렉터리 생성하는 곳에 사용)
  - stat 구조체를 사용하기 위해서는 stat 구조체를 만들고 stat() 함수를 이용해 해당 파일을 인자로 넘겨주어야 함. <br>
    -> ```stat(tmpdir, &sb);```로 realpath()를 통해 변환한 절대경로를 stat 구조체로 만들어줌.
    - [stat file permission](https://cokk.tistory.com/51)
  - 500line mtime 구하는 로직 수정할 것.
  - backupNode 사용해 따로 구현한 부분 수정 중에 있음.
  - **발생한 error 디버깅 거의 마무리 되어감. 이제 warning 잡을 예정.. **

* **remove 명령어 추가 구현**
  - ```readdir()```으로 백업디렉토리 하위의 파일 중 삭제할 파일의 이름과 동일한 파일을 찾기 위해 ```strstr(entry->d_name, fileName);```의 리턴 값이 NULL이 아닌 경우 해당 파일을 삭제하는 방식으로 구현 완료
  - [strstr()](https://dojang.io/mod/page/view.php?id=371)
  
* **recover 명령어 추가 구현**
  - 디렉토리 열어 입력한 파일명 가지는 파일 카운트한 뒤 2차원 포인터 메모리 동적할당 해주어 배열에 값 넣어주는 작업 구현 진행 중
  - 금일 순번과 함께 백업파일 출력하는 부분까지 금일 보고 이후에 더 구현할 예정
  - 파일의 내용을 출력할 때 파일이름은 ```entry -> d_name```으로 접근, 파일 크기는 ```fseek()```, ```ftell()```함수를 사용하여 구현 
  - dirent 구조체의 ```d_reclen```변수가 파일 이름 길이임을 알게 됨. (dirent 구조체에는 파일의 크기를 저장하는 변수가 없었다!)
  
    ------
### 21.03.01 (월) 프로젝트 진행 계획 및 보고

#### 진행 내용 및 학습 내용
* **recover 명령어**
  - 파일 크기 구해 ```순번. 백업된 파일  파일크기```의 형식으로 2차원 배열에 저장하는 부분 구현 완료
  - https://yaraba.tistory.com/618
  - 사용자가 선택한 백업버전의 파일을 리커버 파일로 복구하여 명세의```test1_190325230522.txt``` -> ```test1_recover.txt```와 같이 저장하도록 구현
  - [텍스트 파일 내용 복사하는 기능](https://dojang.io/mod/page/view.php?id=623) 
  - ```fread()``` 함수를 사용해 파일 내용 읽어오고, ```fwrite()```함수 사용해 원본 파일에 쓰도록 구현
  - 파일 내용 읽어와 붙여넣기 하는 부분 661 line ~ 다시 확인하기

* **스레드 함수**
  - 스레드 함수에서 내용 복사/붙여넣기 과정 중 stat 구조체의 st_size로 recover 명령어에서도 파일 크기를 구하여 출력할 수 있었음. ```fseek()```, ```ftell()``` -> ```statbuffer.st_size```
  - 백업 주기마다 ```<파일명_백업수행시간>```의 포맷을 가진 파일을 생성하고 이전버전 파일의 내용을 ```fread()```, ```fwrite()```를 이용해 파일에 백업하는 부분 구현 완료
  - 파일 백업 후 로그파일에 generated 로그 작성되도록 구현 완료

* **구현한 코드 디버깅 & 변수명/함수명 통일**

#### 구현 중 질문 사항
* 2차원 배열에 백업파일의 개수만큼 카운트해서 1차원 포인터에 동적할당을 해주었고, 2차원 포인터에 tmpmem배열에 저장된 ```순번. 파일백업시간  파일크기```형식의 문자열을 반복문 안에서 넣어주었습니다. 명세 상에는 파일명_백업시간이 아닌 백업시간만 출력이 되는데 그렇다면 앞에 파일명을 삭제하여 출력할 수 있는 방법은 없을까요..?
  - ex) 백업파일을 dirent 구조체 변수 entry -> d_name 으로 접근해 출력했는데 d_name에서 ```test1.txt_190325153325```를 ```190325153325```만 출력할 수 있는 방법이요!
  - **공부한 내용** : strncpy()함수 또는 strstr() 함수를 사용하여도 위의 예로 보았을 때 ```test1.txt```만 추출할 수 있는 것으로 확인됨..

    ------
### 21.03.02 (화) 프로젝트 진행 계획 및 보고

#### 지난 시간 피드백
* recover 실행 예에서 ```ls testdir``` 실행 결과가 원본파일, _ recover파일만 존재함 <br>
  -> 백업수행된 파일은 다른 디렉토리에서 관리하도록 할 것
* 위 질문 : 파일 이름 길이 + 1 해서 ```strcpy()```
* 스레드 종료 시 : 파일별 구조체의 변수 활용할 것

#### 진행 내용 및 학습 내용
* **remove 명령어**
  - 입력받은 파일의 스레드를 종료하기 위해 스레드 함수에서 스레드 식별자를 구조체 변수에 저장하여주고, remove 함수에서 해당 파일의 정보를 저장하는 노드 구조체 변수에 스레드아이디를 찾아 ```pthread_cancel()``` 시켜줌.

* **recover 명령어**
  - [문자열 복사를 시작하고자 하는 부분의 포인터로 strcpy()하는 방법](https://blockdmask.tistory.com/56)
  - 문자열의 포인터를 인자로 그 부분부터 strcpy()를 하는 부분에서 헤맴.
  - ![image](https://user-images.githubusercontent.com/66112716/109657100-77d37100-7ba8-11eb-8ce5-32828b27f53d.png) <br>
    - 성공! ```entry -> d_reclen```으로 접근해 프로그램 코드에 적용 완료
  - 파일 크기를 fseek(), ftell()이 아닌 st_size로 구해 저장하도록 코드 수정

* **add 명령어**
  - 스레드 생성하여줌. 스레드 간 공유되는 자원의 개수를 카운트하기 위해 선언한 전역변수 ```ncount```를 사용하여 add 명령어가 실행될 때마다 ncount++;를 하여 파일별로 각각의 스레드를 생성하여줌.
  - add에서 생성된(```pthread_create()```) 스레드 식별자가 remove 명령어에서 종료될 때(```pthread_cancel()```)까지 스레드의 종료를 기다리도록 ncount만큼의 반복문 안에서 ```pthread_join()``` 처리를 해줌.
  - [코드 참고](https://bitsoul.tistory.com/157)

* **구현된 코드 디버깅**

#### 0303 진행 계획
* 백업이 진행될 때 백업파일은 별도의 디렉터리를 생성해 그 아래에서 관리할 수 있도록 ```thread_function```에서 백업을 진행할 때에는 백업된 파일 관리 전용 디렉터리에 파일 백업하도록 하는 부분 진행.
* 기능 구현 대부분 완료. 명세 중 예외처리 조건 살펴보지 못한 부분 추가구현 뒤 마무리 된다면 디버깅하여 제대로 수행되도록 할 것.

    ------
### 21.03.03 (수) 프로젝트 진행 계획 및 보고

#### 지난 시간 피드백
* ncount의 전역변수로 자원이 할당된 스레드를 관리하였지만, 연결리스트 구조체의 파일 count 변수로 할당된 스레드를 구할 수도 있음.

#### 진행 내용 및 학습 내용
* mkdir() 함수를 사용해서 디렉토리를 생성하는 부분 모두 수정.
  - [디렉토리 폴더 만들기](https://m.blog.naver.com/PostView.nhn?blogId=hts0128&logNo=90048315393&proxyReferer=https:%2F%2Fwww.google.com%2F)
  - [참고2](https://devkyu.tistory.com/96)

* **remove 명령어 예외처리부분 구현 완료**

* **코드 error & warning 80% 해결**
- ```function returns address of local variable``` : 해당 warning의 해결방법으로 checkAcessDir() 함수에서 변환된 절대경로를 static char변수로 선언해줌. 

#### 추가적으로 더 구현해야하는 부분
* recover 명령어에서 사용자가 선택한 순번의 백업파일의 내용을 fread(), fwirte()로 _ recover 파일에 저장하려면 파일의 크기를 알아야함. 이 때 선택한 파일을 stat함수를 통해 구조체에 접근할 수 있도록 한 뒤, 해당 파일의 ```st_size```만큼 fread 인자로 넘겨주기

* 백업파일을 관리하는 디렉토리 만들어 그 안에서 관리하는 방법 아직 X -> 내일까지 꼭 공부하고 구현해놓기

* recover할 때 백업시간 기준 오름차순으로 정렬되어 출력되게 하는 부분 구현 X, 디버깅 완료 후 실행해보며 추가하기

    ------
### 21.03.04 (목) 프로젝트 진행 계획 및 보고
* recover에서 선택한 파일의 이름을 rename() 함수를 통해 이름을 바꿔 저장하도록 함.

* 컴파일 시 에러 모두 해결하고 명령어별 함수 호출부에 인자 전달하여 명령어별 실행 확인 중.
  - 프롬프트 출력 부에서 명령어와 파일명을 입력받아 저장하는 부분에서 문제 발생. 디버깅 중.
  - 프롬프트 문제 해결 -> 세그멘테이션 오류.. (배열/포인터 부분 디버깅 중..)
  - 백업디렉토리 생성 부분 코드 수정 중.
  - **프롬프트 출력** : 성공적으로 진행됨.
  - **checkAccessDir()** 함수 : mkdir() 오류, 예외처리 부분 수정
  - **add 명령어** : mkdir 오류로 인해 파일 생성 X, checkAccessDir 함수 디버깅한 뒤 재실행할 예정
  - **list 명령어** : listFunc는 다른 코드에서 옮겨와 임의의 데이터를 추가하고 실행해보았을 때 제대로 실행됨. 연결리스트에 파일 정보를 저장하는 노드가 생성된다면 제대로 실행될 것으로 보임.
  - **ls 명령어** : 성공적으로 ls 기능이 수행되나, exit 명령어 입력 전까지 실행 후 다시 프롬프트로 돌아오지 않아 이 부분 수정 중.
  - **vi(m) 명령어** : 성공적으로 vi 편집창으로 이동함. 이 명령어 역시 실행 후 다시 프롬프트로 제어 넘기는 부분 수정.
  - **exit 명령어** : 성공적으로 실행됨. (프로그램 종료)

    ------
### 21.03.05 (금) 프로젝트 진행 계획 및 보고
* **3/4 실행 시 문제가 되었던 부분 코드 수정 진행 중.**
  - **checkAccessDir()** 절대경로로의 변환, 디렉토리 생성 및 파일 권한 확인 부분 : 백업디렉토리를 생성할 인자가 없는 상태로 실행할 경우 현재 디렉토리의 하위에 백업디렉토리(backup_directory)가 성공적으로 생성되는 것을 확인함. 인자가 있을 때 그 경로에 백업 디렉토리를 제대로 생성하도록 코드 수정 중. 
  
  - **연결리스트 함수 부분** : 연결리스트 함수 기능 디버깅 결과 완벽하게 잘 실행됨. 백업리스트의 파일 확인을 위해 backupList.list 파일에 추가된 노드들을 확인한 결과 정상적으로 생성되는 것 확인.
  
  - **add 명령어 부분** : 스레드 함수에서 실행되는 ```void *addFile```을 노드로 만들어 해당 파일명을 fopen()하는 부분에서 fopen() 오류 발생하여 수정 중. <br>
    - findNode에 addFile을 인자로 넘겨 연결리스트에서 찾은 파일을 newNode에 저장해주는 방법으로 접근 (thread_function의 인자와 addFunc에서의 스레드 함수 호출부를 수정)

    ------
### 21.03.06 (토) 프로젝트 진행 계획 및 보고
* **add 명령어** : 명령어 입력 시 period 입력하지 않은 경우 처리해주도록 코드 수정
* **remove 명령어** : 파일 삭제 및 스레드 중지 부분 디버깅
* **list 명령어** : backupList.list의 내용들을 읽어오도록 코드 수정
* **백업 시간 기록** : 210307000315와 같이 항상 12자리로 구현되도록 시간 측정부 코드 수정
* **compare 명령어** : 정상적으로 수행됨, 기능 구현 완료
  - ![image](https://user-images.githubusercontent.com/66112716/110207651-47514700-7ec8-11eb-81d0-b2dc9ab5e559.png)
* **모든 명령어** : exit 명령어를 제외하고 나서는 에러/명령어 수행 후 프롬프트로 제어를 넘기도록 수정함. <br>
  -> 프로그램 종료는 exit 명령하여야만 가능하도록.
  - ![image](https://user-images.githubusercontent.com/66112716/110210746-7c649600-7ed6-11eb-8820-1a83411d69c4.png)

    ------
### 21.03.07 (일) 프로젝트 진행 계획 및 보고
* **백업 시간 & 수행 시간** : localtime() 함수를 사용하여 tm 구조체의 변수를 통해 년월일 시분초 형식에 맞게 출력
* **logfile 작성** 문제 해결 -> fopen() 모드를 다르게 해주어 로그가 수행시간 순으로 누적 작성되도록 함
  - ![image](https://user-images.githubusercontent.com/66112716/110214702-31a04980-7ee9-11eb-95d2-ad013d4c19da.png)
* **remove 명령어** : 세그멘테이션 오류로 인해 removeFunc() 호출부와 구현부 디버깅 중
  - 배열과 포인터 사용부분을 모두 수정해보고 있지만 계속 코어덤프가 발생함.
  - pthread_cancel() 주석하여도 코어덤프...
* **recover 명령어** : 인자로 입력받은 ```node -> fileName```을 findNode() 함수로 찾는 과정에서 오류가 발생한 것으로 예상됨. 
  - findNode() 함수 문제 X, 라인별 디버깅 중.

    ------
### 21.03.08 (월) 프로젝트 진행 계획 및 보고
* **checkAccessDir() 함수 디버깅 완료** : 입력받은 상대/절대경로에 백업 디렉토리를 성공적으로 생성하며, 해당 디렉토리 내부에 백업 파일을 성공적으로 추가하고 백업버전까지 저장되는 것 확인.
* **실행 시 인자를 넘겨주었을 떄 로그파일 작성 여부** : 입력한 상대/절대 경로를 변환한 경로에 파일 added, generated 성공적으로 로그 찍히는 것 확인.
* **프롬프트에서 엔터만 입력한 경우** : 다시 프롬프트로 제어가 넘어감.
* **add 명령어** : period 입력 없을 시 예외처리 구현 완료.
* **remove 명령어** : 명령어 기능 구현 완료. 실행 정상적으로 되며 스레드가 종료되어 백업이 중지됨.
  ![image](https://user-images.githubusercontent.com/66112716/110336137-e8c2cf00-8067-11eb-8166-3484fa108e11.png)
* **recover 명령어** : 함수 실행 자체가 되지 않고 코어덤프 발생. remove에서와 같은 로직으로 파일을 findNode()를 통해 찾아오지만 이 마저도 실행안됨. 라인 별 디버깅 중.
  - rename() 함수 사용해 파일 관련 부분 재구현할 예정.

    ------
### 21.03.09 (화) 프로젝트 진행 계획 및 보고
* recover 명령어 함수 디버깅 -> 계속 코어덤프가 발생하여 처음부터 재구현

    ------
### 21.03.10 (수) 프로젝트 진행 계획 및 보고
* **list 명령어** : ```backupList.list```의 추가된 내용을 그대로 읽어오는 방식에서 백업리스트의 ```node -> fileName```, ```node -> filePeriod```를 fileCnt만큼 순차적으로 읽어오도록 구현방법 변경
* **warning 해결** : 컴파일시 발생하는 warning 모두 해결
  ![image](https://user-images.githubusercontent.com/66112716/110646683-79311900-81fa-11eb-8170-e709c0a68343.png)
* **recover 명령어** : 코어덤프 해결한 뒤 프로그램 실행 시 생성되는 backup_directory를 open.
  - ```recover <FILENAME>```의 filename을 가진 백업파일을 strstr()로 모음.
  - 백업 수행시간을 저장하기 위해 strtok()를 사용해 위에서 필터링된 파일들 중 두번째 토큰을 rcvptr[][]에 저장.
  - 순번, 파일크기와 함께 출력하고 사용자로부터 원하는 백업수행버전을 입력받는 것까지 구현 완료. 
  ![image](https://user-images.githubusercontent.com/66112716/110646288-19d30900-81fa-11eb-9ed9-eaceb430936b.png)
  - **추가 구현이 필요한 내용** : 사용자가 입력받은 백업본의 파일으로 복구하는 과정 디버깅 중.
    - ```filename_recover.txt```가 백업 디렉토리와 로그에 추가되도록 코드 추가.
    - 정상 작동 여부 확인.

    ------
### 21.03.11 (목) 프로젝트 진행 계획 및 보고
* recover 명령어에서 입력받은 파일명과 사용자로부터 선택된 백업본을 fileName_recover.txt 파일로 변경하는 작업 진행 중.
* recover 명령어에서 백업이 수행된 파일을 가져오는 기능은 backup_directory 에서 opendir(), readdir()로 받아오는 것 맞음.
* **코멘트** : 연결리스트에 저장되어있는 파일명에 구현한 함수 makeJustFile로 접근하기.
  - thread 함수 수정 중 오류가 생겨 해결할 예정

    ------
### 21.03.12 (금) 프로젝트 진행 계획 및 보고
* 어제 발생하였던 스레드 함수 오류 해결.
* rename()을 이용하여 파일명을 파일명_recover로 수정하였더니 파일 이름이 바뀐 것 확인할 수 있었음.
  - ![image](https://user-images.githubusercontent.com/66112716/110935642-0ac39680-8373-11eb-928c-83e6e0ba80bc.png)
  - ![image](https://user-images.githubusercontent.com/66112716/110935675-16af5880-8373-11eb-9b7c-924265619e1c.png)
  - rename()을 수행하면 일정 시간 후 프로그램이 셧다운 되는 오류 발생.
    - 명세 '백업 수행 종료 후 복구 진행'에 따라 ```rename(), fread(), fwrite()``` 전에 해당 파일의 스레드를 ```pthread_cancel()``` 시켜주어 해결.
* fread(), fwrite() 사용해 백업본으로 복구하여 저장하는 작업 진행.
 - fgets(), fputs() 이용해서 구현하는 것으로 방법 변경함.
 - 백업 디렉토리에 존재하는 파일의 내용을 fopen()하는 과정에서 오류 발생. 해결 방법을 모르겠음.. 계속 디버깅 중!

    ------
### 21.03.13 (토) 프로젝트 진행 계획 및 보고
* **recover 명령어에서 백업파일의 내용을 _ recover 파일로 옮기는 작업**
  - fread(), fwrite()의 과정이 잘못되었는지 확인하기 위하여 ```test_fopen.c``` 파일을 만들어 ```fopen_test.txt```는 백업 디렉토리 안에 위치, ```paste.txt``` 파일을 밖에 위치하게 하여 fread(), fwrite() 작업을 해주었음.
  - 프로그램 구현에서와 동일한 방법을 사용했음에도 위의 test_fopen.c 예제코드에서는 fopen_test.txt의 내용이 paste.txt로 정상적으로 옮겨진 것을 확인.
  - ![image](https://user-images.githubusercontent.com/66112716/111029821-1a5de080-8442-11eb-9a8c-35b59d956eac.png)
  - 프로그램 코드에서는 ```copy_fptr```의 fopen() error가 발생함. 파일의 위치와 이름을 정확히 넘겨주었음에도 이러한 오류가 발생하여 해결 방법 모색 중.

    ------
### 21.03.14 (일) 프로젝트 진행 계획 및 보고
* remove 명령어 수정 완료
  ![image](https://user-images.githubusercontent.com/66112716/111071399-557f1300-8519-11eb-81cd-34d9e845495b.png)
* recover 명령어 구현 완료
  ![image](https://user-images.githubusercontent.com/66112716/111071417-76dfff00-8519-11eb-8ba7-e9b9c5814f11.png)
  ![image](https://user-images.githubusercontent.com/66112716/111071429-80696700-8519-11eb-8e2e-4e15e2e44649.png)


