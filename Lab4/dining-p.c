//Name: Ani Khachatryan
//Date: 19 April 2020
//Assignment: Lab 4 - Rice, Rice, and Rice
//Purpose: To develop a single program that behaves as a single philosopher. When this 
//         program is executed with other instances of the program, you will have up to 
//         N cooperating processes all involved in solving the “Dining Philosophers 
//         problem.” (Only turn in Part 2 - modify your program to remove the possibility 
//         of deadlock by removing one of the following two conditions for deadlock: Hold and 
//         wait, or circular wait)

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <semaphore.h>

//globals
#define SEM_FILE1  "/chopstick1"
#define SEM_FILE2  "/chopstick2"
sem_t* rightSide;
sem_t* leftSide;

//global done variable that is used to end program
int done;

//eat method that prints philosopher eating message
void eat(int phil) {
    //print message
	fprintf(stdout, "Philosopher #%d is eating\n", phil);
    //variable that will be used for usleep
    int eatTime = rand()%(1000000+1);
    //sleep for random amount of time
	usleep((useconds_t) eatTime);
}

//think method that prints philosopher thinking message
void think(int phil) {
    //print message
	fprintf(stdout, "Philosopher #%d is thinking\n", phil);
    //variable that will be used for usleep
    int thinkTime = rand()%(1000000+1);
    //sleep for random amount of time
	usleep((useconds_t) thinkTime);
}

//method to set done to number
void setVal() {
    //initialized
	done = 1;
}

//method to get done variable
int getVal() {
    //get value in done
	return done;
}

//signal handler method
void signalHandler() {
    //go to setVal() method
	setVal();
}

//main method
int main(int argc, char** argv) {
    //if there's less than 3 args given
	if(argc != 3) {
        //print message to stderr
		fprintf(stdout, "Error: Please give number of seats and position.\n");
        //exit
		return 1;
	}
    //otherwise
	else {
        //create and initialize seats variable
        int seats = atoi(argv[1]);
        //create and initialize position variable
        int position = atoi(argv[2]);
        //if there's less seats than philosophers
        if(seats < position) {
            //print message
            printf("Error: not enough seats\n");
        }
        //otherwise
        else {
            //create and initialize cycles variable
            static int cycles = 0;
            //send signal to sigHandler function
            signal(SIGTERM, signalHandler);
            //initialize right-handed
            rightSide = sem_open(SEM_FILE1, O_CREAT|O_EXCL, 0660, 1);
            //initialize left-handed
            leftSide = sem_open(SEM_FILE2, O_CREAT|O_EXCL, 0660, 1);
            //if right-handed failed
            if(rightSide == SEM_FAILED) {
                //sem_open
                rightSide = sem_open(SEM_FILE1, 0);
            }
            //if left-handed failed
            if(leftSide == SEM_FAILED) {
                //sem_open
                leftSide = sem_open(SEM_FILE2, 0);
            }
            if(!getVal()) {
                //do the code below
                do {
                    //wait on right-handed semaphore
                    sem_wait(rightSide);
                    //wait on left-handed semaphore
                    sem_wait(leftSide);
                    //send arg to eat function
                    eat(atoi(argv[argc-1]));
                    //signal that right side is free
                    sem_post(rightSide);
                    //signal that left side is free
                    sem_post(leftSide);
                    //send arg to think function
                    think(atoi(argv[argc-1]));
                    //increment counter
                    cycles++;
                    printf("Cycles: %d\n", cycles);
                }
                while(!getVal());
            } 
            //if done
            if(getVal()) {
                //print message to stderr
                fprintf(stderr, "\nPhilosopher %d completed %d cycles.\n", atoi(argv[argc-1]), cycles);
            }
            //close right side
            sem_close(rightSide);
            //close left side
            sem_close(leftSide);
            //unlink
            sem_unlink(SEM_FILE1);
            //unlink
            sem_unlink(SEM_FILE2);
            //destroy right side
            sem_destroy(rightSide);
            //destroy left side
            sem_destroy(leftSide);
        }
	}
    return 0;
}
