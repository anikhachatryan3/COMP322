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
    if(num == 15) {
        term++;
    }
    else {
        term = 0;
    }
    count++;
    //print signal and seconds (time) on stdout
    fprintf(stdout, "SIG%s caught at %ld\n", sigs[num-1], seconds);
}

//method to count how many SIGTERM signals have been caught
void termCounter() {
    //while 3 SIGTERM signals have not been caught
    while(term < 3) {
        //pause program
        pause();
    }
    //if SIGTERM counter equals 3
    if(term == 3) {
        //successfully exit
        exit(EXIT_SUCCESS);
    }
}

//handler method used to check each argument
void sig(int argc, char** argv) {
    //create i variable
    int i, j;
    //making 2 for loops to check all arguments
    for(i = 1; i < argc; i++) {
        for(j = 0; j < 27; j++) {
            //if signals compared together = 0
            if(strcmp(argv[i], sigs[j]) == 0) {
                //signal
                signal(j+1, sigCatch);
            }
        }
    }
    termCounter();
}

//method to print total number of signals caught
void totalCount() {
    //print on stderr
    fprintf(stderr, "catcher: Total signals count = %d", count);
}

//main method
int main(int argc, char** argv) {
    //call statLine method
    statLine(getpid());
    //calling sig method
    sig(argc, argv);
    //call totalCount method
    totalCount();
    
    return 0;
}
