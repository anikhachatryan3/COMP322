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
    fprintf(stderr, "$$ = %d\n", child);
}

//method to print retval
void printRetVal(int status) {
    //print retval
    fprintf(stderr, "$? = %d\n", status);
}

//main method
int main(int argc, char** argv) {
    //if argc is greater than 0 (not empty)
    if(argc > 0) {
        //create i variable to use in for loop
        int i;
        //create status variable
        int status;
        //fork and store in child variable
        pid_t child = fork();
        //create waiting variable
        pid_t waiting;
        //create arg array variable
        char* argArr[argc];
        //if child is 0
        if(child == 0) {
            //while i is less than argc
            for(i = 1; (i - 1) < argc; i++) {
                argArr[i-1] = argv[i];
            }
            execve(argv[1], argArr, NULL);
        }
        //if the child is a positive number
        else if(child > 0) {
            //print the cpid
            printCPID(child);
            //wait for child to finish
            waiting = waitpid(child, &status, WUNTRACED);
        }
        //print the return value of the child
        printRetVal(status);
    }
}
