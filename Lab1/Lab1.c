//Name: Ani Khachatryan
//Date: 19 February 2020
//Assignment: Lab1 - Time and Forking Children
//Purpose: write a command line tool that reports basic process identification 
//         information, and the associated times for running the command line tool.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <sys/wait.h>
// #include <sys/types.h> 
#include <sys/errno.h>
#include <sys/times.h>

//method for child process
void childProcess(pid_t parent, pid_t child) {
    //print pid and ppid
    printf("PPID: %d, PID: %d\n", parent, child);
    //exit process
    exit(EXIT_SUCCESS);
}

//method to print user and sys
void childTime(clock_t user, clock_t system) {
    printf("USER: %d, SYS: %d\n", (int)user, (int)system);
}

//method for parent process
void parentProcess(pid_t parent, pid_t pid, pid_t child, int status) {
    //print pid, ppid, cpid, and retVal
    printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", parent, pid, child, status); //WEXITSTATUS(status)?
}

//method to print cuser and csys
void parentTime(clock_t user, clock_t system) {
    printf("CUSER: %d, CSYS: %d\n", (int)user, (int)system);
}

//main function
int main() {
    //create time variable
    time_t seconds;
    //create waiting variable
    pid_t waiting;
    //create status variable
    int status;
    time(&seconds);
    //print start time
    printf("START: %ld\n", seconds);
    //create child process (fork)
    pid_t child = fork();
    //create struct for user and system times
    struct tms clocks;
    //if child = 0
    if(child == 0) {
        //do child process
        childProcess(getppid(), getpid());
    }
    //if child is greater than 0
    else if(child > 0) {
        //is parent (wait for child to finish)
        waiting = waitpid(child, &status, WUNTRACED);
        //do parent process
        parentProcess(getppid(), getpid(), child, status);
        times(&clocks);
        //get child time
        childTime(clocks.tms_utime, clocks.tms_stime);
        //get parent time
        parentTime(clocks.tms_cutime, clocks.tms_cstime);
    }
    //otherwise
    else {
        //print error number (errno)
        printf("Error Number: %d\n", errno);
        //print "error"
        printf("Forking Failed.\n");
        return 1;
    }
    time(&seconds);
    printf("STOP: %ld\n", seconds);

    return 0;
}
