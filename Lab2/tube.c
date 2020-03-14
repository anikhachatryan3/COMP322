//Name: Ani Khachatryan
//Date: 29 February 2020
//Assignment: Launch-Tube
//Purpose: To develop two programs. The two programs are designed to be down in two parts.
//         For tube: it launches two child processes, and sets up a pipe between them for
//         inter-process communication. The program prints the return value of the first 
//         child and then the second child on stderr.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//method to print CPID of both children
void printCPIDs(pid_t child1, pid_t child2) {
    //print cpid of child1
    fprintf(stderr, "CPID1: %d\n", child1);
    //print cpid of child2
    fprintf(stderr, "CPID: %d\n", child2);
}

//method to print retval
void printRetVal(int status1, int status2) {
    //print retval for child1
    printf("RETVAL: %d\n", status1);
    //print retval for child2
    printf("RETVAL: %d\n", status2);
}
//method to use dup2()
// void doDup2() {
//     // dup2();
// }

// //main method
int main(int argc, char** argv) {
    if(argc > 0) {
        //pipe
        int pipe[argc];
        //create status1 and status2 variables
        int status1 = -1;
        int status2 = -1;
        //create first child process using fork() and store in child1
        pid_t child1 = fork();
        //create second child process using fork() and store in child2
        pid_t child2 = fork();
        //create wait1 and wait2 variables
        pid_t wait1;
        pid_t wait2;
        //if both children are a positive number
        if(child1 == 0 && child2 == 0) {
            printf("Child process\n");
        }
        else if((child1 > 0) && (child2 > 0)) {
            //wait for child process 1 and 2 to finish
            wait1 = waitpid(child1, &status1, WUNTRACED);
            wait2 = waitpid(child2, &status2, WUNTRACED);
            //print cpids of both children
            printCPIDs(child1, child2);
            // close();
        }
        //print return value of both children
        printRetVal(status1, status2);
    }
}
