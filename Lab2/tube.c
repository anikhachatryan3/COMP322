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
void printCPIDs(char* argv1, char* argv2, pid_t child1, pid_t child2) {
    //print cpid of child1
    fprintf(stderr, "%s: $$ = %d\n", argv1, child1);
    //print cpid of child2
    fprintf(stderr, "%s: $$ = %d\n", argv2, child2);
}

//method to print retval
void printRetVals(char* argv1, char* argv2, int status1, int status2) {
    //print retval for child1
    fprintf(stderr, "%s: $? = %d\n", argv1, status1);
    //print retval for child2
    fprintf(stderr, "%s: $? = %d\n", argv2, status2);
}

// //main method
int main(int argc, char** argv) {
    if(argc > 0) {
        int i;
        int pipeSize[2];
        int j;
        //pipe
        pipe(pipeSize);
        //while i is less than argc
        for(i = 0; i < argc; i++) {
            //create divider
            int divider = strcmp(argv[i], ",");
            //if divider = 0
            if(divider == 0) {
                j = i++;
                argv[i] = NULL;
                break;
            }
        }
        //create first child process using fork() and store in child1
        pid_t child1 = fork();
        //create wait1 and wait2 variables
        pid_t wait1;
        pid_t wait2;
        //create status1 and status2 variables
        int status1;
        int status2;
        //if child1 is equal to 0
        if(child1 == 0) {
            //close pipe
            dup2(pipeSize[1], 1);
            //execute first command
            execve(argv[1], argv + 1, NULL);
        }
         //else if child1 is -1
        else if(child1 == -1) {
            //print error message
            printf("Error. Failed 1st fork.\n");
        }
        //if child1 is a positive number
        else {
            //create second child process using fork() and store in child2
            pid_t child2 = fork();
            //if child2 is equal to 0
            if(child2 == 0) {
                //close pipe
                dup2(pipeSize[0], 0);
                //execute second command
                execve(argv[j], argv + j, NULL);
                //exit sucessfully
                exit(0);
            }
            //else if child2 is a positive number
            else if(child2 > 0) {
                //print the CPIDs of both children
                printCPIDs(argv[1], (argv[3]+6), child1, child2);
            }
            //else
            else {
                //print error message
                printf("Error. Failed 2nd fork.\n");
            }
            //wait for child process 1 and 2 to finish
            wait1 = waitpid(child1, &status1, WUNTRACED);
            wait2 = waitpid(child2, &status2, WUNTRACED);
            //close both
            close(pipeSize[0]);
            close(pipeSize[1]);
            //print return value of both children
            printRetVals(argv[1], (argv[3]+6), status1, status2);
        }
    }
}
