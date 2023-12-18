// Joey Troyer
// 08-25-23
// Purpose: To get experience using signals in c

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// thread safe error flag
_Atomic int error = 0;

// this function runs when for SIGUSR1
void USR1(){
    printf("Final Exam is on December 4th at 8am\n");
    fflush(stdout);

    // rest singal
    if(signal(SIGUSR1, USR1) == SIG_ERR){
        error = 1;
    }
}

// this function runs for SIGUSR2
void USR2(){
    printf("I have no conflicts with that exam time\n");
    fflush(stdout);

    // rest singal
    if(signal(SIGUSR2, USR2) == SIG_ERR){
        error = 1;
    }
}


int main() {
    // create signal
    if(signal(SIGUSR1, USR1) == SIG_ERR){
        return 1;
    }

    // create signal
    if(signal(SIGUSR2, USR2) == SIG_ERR){
        return 1;
    }


    // infinite sleep loop
    while(1){
        sleep(1);

        if(error == 1)
            return 1;
    }

    return 0;
}

