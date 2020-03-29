//Name: Ani Khachatryan
//Date: 21 March 2020
//Assignment: Lab 3 - Catcher
//Purpose: To develop a single program that catches signals. When the program 
//         catches the signals, it writes particular information onto stdout.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

//global count variable
static int count = 0;
//global term variable
static int term = 0;
//array of signals that can be caught (signals given on slack)
static const char* sigs[27] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE","USR1", "EGV", 
                           "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", "TSTP", "TTIN", "TTOU", 
                           "URG", "XCPU", "XFSZ", "TALRM", "PROF", "WINCH"};
void totalCount();

//method to print PID on stderr
void statLine(int pid) {
    //print on stderr
    fprintf(stderr, "catcher: $$ = %d\n", pid);
}

//method used to catch signals
void sigCatch(int num) {
    //create seconds variable
    time_t seconds;
    //how many seconds
    time(&seconds);
    //if num equals 15 (TERM)
    if(num == 15) {
        //increment
        term++;
    }
    //otherwise
    else {
        //term equals 0
        term = 0;
    }
    //if number is the same as SIGUSR1
    if(num == SIGUSR1) {
        //print for SIGUSR1
        fprintf(stdout, "SIGUSR1 caught at %ld\n", seconds);
    }
    //if number is the same as SIGUSR2
    else if(num == SIGUSR2) {
        //print for SIGUSR2
        fprintf(stdout, "SIGUSR2 caught at %ld\n", seconds);
    }
    //otherwise
    else {
        //print signal and seconds (time) on stdout
        fprintf(stdout, "SIG%s caught at %ld\n", sigs[num-1], seconds);
    }
    //increment counter for total signals
    count++;
}

//method to count how many SIGTERM signals have been caught
void termCounter() {
    //while 3 SIGTERM signals have not been caught
    while(term < 3) {
        //pause program
        pause();
    }
    //call totalCount method
    totalCount();
}

//handler method used to check each argument
void sig(int argc, char** argv) {
    //create i variable
    int i, j;
    //making 2 for loops to check all arguments
    for(i = 1; i < argc; i++) {
        for(j = 0; j < 27; j++) {
            //if signals compared together = 0
            if(strcmp(argv[i], "USR1") == 0) {
                //signal for SIGUSR1
                signal(SIGUSR1, sigCatch);
            }
            if(strcmp(argv[i], "USR2") == 0) {
                //signal for SIGUSR2
                signal(SIGUSR2, sigCatch);
            }
            else {
                signal(j+1, sigCatch);
            }
        }
    }
    //call termCounter method
    termCounter();
}

//method to print total number of signals caught
void totalCount() {
    //print on stderr
    fprintf(stderr, "catcher: Total signals count = %d\n", count);
}

//main method
int main(int argc, char** argv) {
    //call statLine method
    statLine(getpid());
    //calling sig method
    sig(argc, argv);
    
    return 0;
}
