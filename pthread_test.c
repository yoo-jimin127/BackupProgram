#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void write_log(char *msg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *t_function(void *data) {
	pid_t pid;
	pthread_t tid;
	int year, month, day, hour, min, sec;
	struct tm *t;
	time_t timer;
	char logmsg[1024] ="";

	char *fulltime = (char *)malloc(sizeof(char)*100);

	pid = getpid();
	tid = pthread_self();
	
	timer = time(NULL);
	t = localtime(&timer);

	char *thread_name = (char *)data;
	
	int i = 0;
	year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;

	while( i < 3) {

		year = t -> tm_year + 1900;
		month = t -> tm_mon + 1;
		day = t -> tm_mday;
		hour = t -> tm_hour;
		min = t -> tm_min;
		sec = t -> tm_sec;

		sprintf(fulltime, "[%d%d%d %d%d%d] ", year, month, day, hour, min, sec);
		
		pthread_mutex_lock(&mutex);

	printf("%s %s --  pid : %u, tid : %x --- %d\n", fulltime, thread_name, (unsigned int)pid, (unsigned int)tid, i);
		sprintf(logmsg, "%s %s --- pid : %u, tid : %x --- %d\n", fulltime, thread_name, (unsigned int)pid, (unsigned int)tid, i);
		
		write_log(logmsg);

		pthread_mutex_unlock(&mutex);

		i++;
		sleep(1);
	}
}

int main() {
	pthread_t p_thread[2];
	int thr_id;
	int status;
	char p1[] = "thread_1";
	char p2[] = "thread_2";
	char pM[] = "thread_m";

	sleep(1);

	thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)p1);

	if (thr_id < 0) {
		perror("thread create error : ");
		exit(0);
	}
	
	thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)p2);

	if (thr_id < 0) {
		perror("thread create error : ");
		exit(0);
	}
	
	t_function((void *)pM);

	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);

	printf("pthread end\n");

	return 0;
}

void write_log(char *msg) {
	FILE *fptr;
	char logMsg[1024];

	memset(logMsg, 0, 1024);

	fptr = fopen("test.log", "w");

	if (fptr != NULL) {
		fputs(msg, fptr);
		//fprintf(fptr, msg);
	}

	fclose(fptr);
}
