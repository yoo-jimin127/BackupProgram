#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
 
#define THR 8
 
void* testFunc(void* arg){
    int i,j,k;
    long long cntt=0;
    int itr = 8000 / THR;
    for(i=0;i<itr;i++){
        for(j=0;j<1000;j++){
            for(k=0;k<1000;k++){
                cntt= cntt+k;
                cntt = cntt/3;
            }
        }
    }
    *((long long*)arg) = cntt;
}
 
 
int main()
{
    long timeDist=0;
    struct timespec tspec;
    int i;
 
    clock_gettime(CLOCK_REALTIME, &tspec);
    timeDist = tspec.tv_sec;
    ///////////////////////////////////////////
    pthread_t thr[THR];
    int thr_id;
    long* status;
    long long reslt[THR];
    for (i = 0; i < THR; i++) {
        thr_id = pthread_create(&thr[i], NULL, testFunc, (void*)(&reslt[i]));
        if(thr_id < 0){
            perror("thread create error : ");
            exit(0);
        }
    }
 
    for (i = 0; i < THR; i++) {
        pthread_join(thr[i], (void*)status);
        free(status);
    }
 
    clock_gettime(CLOCK_REALTIME, &tspec);
    timeDist = tspec.tv_sec - timeDist;
    printf("total time:%ld\n",timeDist);
    ///////////////////////////////////////////
    return 0;
}
