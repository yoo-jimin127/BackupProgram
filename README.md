# lsp_winter_backup_program
### 21.02.06 (토) 프로젝트 진행 계획 및 보고
* 명세 분석 및 정리 요약 **(02.06 완료)**
* 210203 진행되었던 명세 설명 내용 다시 이해 **(02.06 완료)**
* 명세 관련 질문사항 정리 **(02.06 진행 중)**
  <br> (개념 이해가 어려운 부분이 존재해 02.07 기본 개념 학습 뒤 스스로 해결할 수 있는 질문내용을 추릴 예정입니다.)
* thread 개념 학습 **(02.06 완료)**
* 명세서에 있는 함수 기능 이해 **(02.06 진행 중)**

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
  
### 21.02.07 (일) 프로젝트 진행 계획 및 보고
#### 210207 진행 계획
(명세에 대해 전반적인 이해는 마친 상태입니다. 하지만 구현 방법에 대해 갈피가 잡히지 않아서 명세에 나와있는 함수에 대한 사용법과 멘토님께서 보내주신 thread 관련 코드들에 대한 학습을 빠르게 선행한 뒤 구현 방법에 대해 고민할 예정입니다.)

* pthread_create() 함수 공부 **(02.07 완료)**
  - pthread_create.c, pthread_create_2.c 코드 이해 및 함수 사용법 학습 **(02.07 완료)**
* pthread_exit() 함수 공부 **(02.07 완료)**
* pthread_join() 함수 공부 **(02.07 완료)**
  - pthread_join.c 코드 이해 및 함수 사용법 학습 **(02.07 완료)**
* pthread_detach() 함수 공부 
* pthread_mutex_init(), pthread_mutex_destroy() 함수 공부
* system() 함수 공부

#### 210207 프로젝트 보고 및 학습내용
* pthread 사용 위해 숙지할 점
  - pthread 함수 사용을 위해 반드시 **#include <pthread.h>** 헤더파일 include
  - 컴파일 시 **-lpthread** 옵션 주어야 함
  - pthread_t : pthread 자료형 의미
  <br>
* **pthread_create()** 함수 : pthread 생성 기능 <br>
```int pthread_create (pthread_t *th_id, const pthread_attr_t *attr, void *함수명, void *arg);```
  - 첫번째 인자 : pthread 식별자, thread가 성공적으로 생성될 경우 **thread 식별값** 주어짐
  - 두번째 인자 : pthread 속성 (option), 기본적 스레드 속성 사용 시 NULL(본 프로젝트에서는 NULL)
  - 세번째 인자 : pthread로 분기할 함수, 반환 값, 매개변수 모두 ```void*``` 로 선언된 함수만 사용 ok ```ex) void* handler (void* arg) {...}```
  - 네번째 인자 : 분기할 함수로 넘겨줄 인자 값, 어떤 자료형 넘겨줄 지 모르므로, void형으로 넘겨준 뒤 상황에 따라 분기하는 함수 내에서 해당 자료형으로 캐스팅해 사용
  - 리턴 : 성공적으로 pthread 생성 시 0 반환 (return형 : int)
  
* **pthread_join()** 함수 : 특정 pthread가 종료될 때까지 기다린 뒤, 특정 pthread가 종료시 자원을 해제시켜줌. <br>
```int pthread_join (pthread_t th_id, void** thead_return);```
  - 첫번째 인자 : 어떤 pthread 기다릴지 정하는 식별자 (스레드 식별자)
  - 두번째 인자 : pthread의 리턴 값, **포인터**로 값 받아오는 점 주의
  - 리턴 값 : 성공 시 0 리턴, 실패 시 에러코드 리턴
  
* **pthread_exit()** 함수 : 현재 실행 중인 thread를 종료시킬 때 사용 <br>
```void pthread_exit(void* ret_value);```
  - 보통 pthread_exit 호출 시 cleanup handler가 호출되며, 보통 리소스 해제하는 일 수행
    
  
