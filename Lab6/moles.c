//Name: Ani Khachatryan
//Date: 04 May 2020
//Assignment: Lab 6 - Wack a Mole
//Purpose: To create a daemon and a child process. The daemon that you create will 
//         spawn and terminate a child process upon receiving a signal.  For this 
//         daemon, you need to handle three signals: SIG_TERM, SIG_USER1, SIG_USER2.

#include <stdio.h>
#include <string.h>

//main method
int main(int argc, char** argv) {
    //create file variable
    FILE* logfile;
    //initialize logfile
    logfile = fopen("~/lab6.log", "w+");
    //if the logfile is NULL
    if(logfile == NULL) {
        //print error message on stderr
        fprintf(stderr, "Something went wrong\n");
    }
    //otherwise
    else {
        //if compared is 0
        if(strcmp("mole1", argv[1]) == 0) {
            //print pop message in logfile
            fprintf(logfile, "Pop %s\n", argv[1]);
        }
        //if compared is 0
        else if(strcmp("mole2", argv[1]) == 0) {
            //print pop message in logfile
            fprintf(logfile, "Pop %s\n", argv[1]);
        }
        //print pop messages
        // fputs(logfile, "Pop %s\n", argv[1]);
    }
    //close file
    fclose(logfile);

    return 0;

}
