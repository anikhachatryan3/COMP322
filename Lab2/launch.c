//Name: Ani Khachatryan
//Date: 29 February 2020
//Assignment: Lab2 - Launch-Tube
//Purpose: To develop two programs. The two programs are designed to be down in two parts. 
//         The first part is a program called “launch”, whereas the second part is a 
//         program called “tube”. For launch: it launches another process and then has this
//         process execute a particular program.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//method to print the cpid
void printCPID(pid_t child) {
    //print cpid
    fprintf(stderr, "CPID: %d\n", child);
}

//method to print retval
void printRetVal(int status) {
    //print retval
    printf("RETVAL: %d\n", status);
}

//main method
int main(int argc, char** argv) {
    //create i variable to use in for loop
    int i;
    //create status variable
    int status;
    //fork and store in child variable
    pid_t child = fork();
    //create waiting variable
    pid_t waiting;
    //if argc is not 0 (or empty)
    if(argc > 0) {
        //if child is 0
        if(child == 0) {
            //do child stuff
            // for(i = 0; i < argc; i++) {
                printf("do something\n");
            //     execve(argv[i]);
            // }
        }
        //if the child is a positive number
        else if(child > 0) {
            //wait for child to finish
            waiting = waitpid(child, &status, WUNTRACED);
            //print the cpid
            printCPID(child);
            //print the return value of the child
            printRetVal(status);
        }
    }
}
