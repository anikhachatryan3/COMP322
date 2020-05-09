//Name: Ani Khachatryan
//Date: 04 May 2020
//Assignment: Lab 6 - Wack a Mole
//Purpose: To create a daemon and a child process. The daemon that you create will 
//         spawn and terminate a child process upon receiving a signal.  For this 
//         daemon, you need to handle three signals: SIG_TERM, SIG_USER1, SIG_USER2.

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

//global variables - I made these global because I wanted to be able to
//                   call them from any method.
pid_t mole1;            //create mole1
pid_t mole2;            //create mole2
pid_t daemonPID;        //create daemonPID
int opening;            //create opening variable

//method to make new moles
void newMole() {
    //generate pseudo random number
    srand(time(0));
    //create and initialize rand variable
    int rand = (random()%2);
    //create makeMole variable
    pid_t makeMole;
    //create char array proc
    char* proc[3];
    //create char pointer whichMole
    char* whichMole;
    if(rand == 1) {
        //store mole1 into whichMole
        whichMole = "mole1";
        //create and initialize makeMole variable
        makeMole = fork();
        //if makeMole value is equal to 0
        if(makeMole == 0) {
            //store mole.c into proc[0]
            proc[0] = "mole.c";
            //store whichMole into proc[1]
            proc[1] = whichMole;
            //store nothing into proc[2]
            proc[2] = NULL;
            //execute
            execv(proc[0], proc);
        }
    }
    //otherwise
    else {
        //store mole2 into whichMole
        whichMole = "mole2";
        //create and initialize makeMole variable
        makeMole = fork();
        //if makeMole value is equal to 0
        if(makeMole == 0) {
            //store mole.c into proc[0]
            proc[0] = "mole.c";
            //store whichMole into proc[1]
            proc[1] = whichMole;
            //store nothing into proc[2]
            proc[2] = NULL;
            //execute
            execv(proc[0], proc);
        }
    }
}

//method to check signals
void checkSigs(int sig) {
    //re-register checkSigs
    signal(sig, checkSigs);
    //if given signal is SIGTERM
    if(sig == SIGTERM) {
        //kill both moles
        kill(mole1, SIGKILL);
        kill(mole2, SIGKILL);
        //kill the daemon process
        kill(daemonPID, SIGKILL);
        //exit sucessfully
        exit(0);
    }
    //if given signal is SIGUSR1
    else if(sig == SIGUSR1) {
        //kill mole1
        kill(mole1, SIGKILL);
        //call method to make a new mole
        newMole();
    }
    //if given signal is SIGUSR2
    else if(sig == SIGUSR2) {
        //kill mole2
        kill(mole2, SIGKILL);
        //call method to make a new mole
        newMole();
    }
}

//method that gives signals
void signals() {
    //SIGUSR1 signal
    signal(SIGUSR1, checkSigs);
    //SIGUSR2 signal
    signal(SIGUSR2, checkSigs);
    //SIGTERM signal
    signal(SIGTERM, checkSigs);
}

//method to fork
void makeFork() {
    //create and initialize new fork variable
    pid_t forking = fork();
    //create fDes1 variable
    int fDes1;
    //create fDes2 variable
    int fDes2;
    //create rLim variable for the struct
    struct rlimit rLims;
    //create i variable
    unsigned int i;
    //if fork value is greater than 0
    if(forking > 0) {
        //print messsage to let user know it's parent process
        printf("Parent process exiting\n");
        //terminate parent process (make parent exit)
        exit(0);
    }
    //if fork value is 0
    else if(forking == 0) {
        //set file creation mask to 0
        umask(0);
        //call method to make signals
        signals();
        //initialize daemonPID
        daemonPID = getpid();
        //print the PID of the daemon
        printf("Daemon PID = %d\n", daemonPID);
        //set sid
        setsid();
        //change directory to "/"
        chdir("/");
        //initialize opening variable
        opening = open("/dev/null", O_CREAT, 0777);
        //get limit
        getrlimit(RLIMIT_NOFILE, &rLims);
        //if the limit is infinity
        if(rLims.rlim_max == RLIM_INFINITY) {
            //change limit to 1024
            rLims.rlim_max = 1024;
        }
        //for all i that is less than the max
        for(i = 0; i < rLims.rlim_max; i++) {
            //close them all
            close(i);
        }
        //initialize fDes1 variable
        fDes1 = dup(opening);
        //initialize fDes2 variable
        fDes2 = dup(opening);
        //while true
        while(true) {
            //pause
            pause();
        }
    }
    //otherwise
    else {
        //print error message on stderr
        fprintf(stderr, "Error: fork failed");
    }
}

//main method
int main() {
    //call method to create signals
    signals();
    //call method to fork
    makeFork();

    return 0;
}
