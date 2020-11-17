#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sched.h>

void writeLog(FILE *logFile)
{
    fprintf(logFile, "hi i'm %d writing some logs here\n", getpid());
}

void main(int argc, char* argv[]) {
    //sem_t *sem1;
    //sem_t *sem2;


    char *semOneName = "/mysem1";
    char *semTwoName = "/mysem2";
    sem_t *sem1 = sem_open(semOneName, O_CREAT | O_EXCL, O_RDWR, 0);
    sem_t *sem2 = sem_open(semTwoName, O_CREAT | O_EXCL, O_RDWR, 1);

    if(fork())
    {
        for(int i = 0; i < 3; i++){
            sem_wait(sem1);
            FILE *logFile = fopen("log.txt", "a");
            fprintf(logFile, "%d is writing some logs here\n", getpid());
            fclose(logFile);
            sem_post(sem2);
            
        }
    }
    else {
        for(int i = 0; i < 3; i++){
            sem_wait(sem2);
            FILE *logFile = fopen("log.txt", "a");
            fprintf(logFile, "%d is writing some logs here\n", getpid());
            fclose(logFile);
            sem_post(sem1);
        }
    }
    sem_unlink(semOneName);
    sem_unlink(semTwoName);
}