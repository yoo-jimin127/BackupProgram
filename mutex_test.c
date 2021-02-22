#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex_lock;

int g_count = 0;

void *t_function (void *data) {
	int i;
	char* thread_name = (char *)data;
	int year, month, day, hour, min, sec;
	struct tm *t;
	time_t timer;
	char logmsg[1024] = "";
	pid_t pid;
	pthread_t tid;

	char *fulltime = (char *)malloc(sizeof(char)*100);


	pid = getpid();
	tid = pthread_self();

	timer = time(NULL);
	t = localtime(&timer);

	pthread_mutex_lock(&mutex_lock);
	g_count = 0;

	year = t -> tm_year + 1900;
	month = t -> tm_mon +1;
	day = t -> tm_mday;
	hour = t -> tm_hour;
	min = t -> tm_min;
	sec = t -> tm_sec;

	sprintf(fulltime, "[%d%d%d %d%d%d] ", year, month, day, hour, min, sec);

	
	for (i = 0; i < 4; i ++) {
		printf("%s %s COUNT %d --- pid : %u, tid : %x\n", fulltime, thread_name, g_count, (unsigned int)pid, (unsigned int)tid);
		g_count++;
		sleep(2);
	}

	pthread_mutex_unlock(&mutex_lock);
}

int main () {
	pthread_t p_thread1, p_thread2, p_thread3;
	int status;

	pthread_mutex_init(&mutex_lock, NULL);

	pthread_create(&p_thread1, NULL, t_function, (void *)"Thread1");
	pthread_create(&p_thread2, NULL, t_function, (void *)"Thread2");
	pthread_create(&p_thread3, NULL, t_function, (void *)"Thread3");
	//	pthread_create(&p_thread4, NULL, t_function, (void *)"Thread4");

	pthread_join(p_thread1, (void *)&status);
	pthread_join(p_thread2, (void *)&status);
	pthread_join(p_thread3, (void *)&status);
	//	pthread_join(p_thread4, (void *)&status);

	printf("---pthread ended---\n");

	return 0;
}
