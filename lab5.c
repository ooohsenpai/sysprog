#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <signal.h>
#include <sched.h>
#include <ctype.h> 

void main(int argc, char* argv[]) {

    int fdpipe[2];
    pipe(fdpipe);
    if(fork()>0) {

        char outstring[] = "emAdd21dDd2aaaaaaaaaaaaaaad2d2dgfGoe";

        close(fdpipe[0]);
        write(fdpipe[1], outstring, sizeof(outstring));
    }
    else {
        close(fdpipe[1]);
        char anime[4096];
        int size = read(fdpipe[0], anime, 4096);
        for(int counter = 0; counter<size; counter++) 
        {
            printf("%c", toupper(anime[counter]));
        }
        printf("\n");
    }
}