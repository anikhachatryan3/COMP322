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

//globals - I decided to use these as globals because the program would always 
//          give warnings and errors when they were local variables. I wanted to 
//          make sure that the program can compile with as little warnings and 
//          errors as possible.
#define CHOPSTICK1  "/chopstick1"
#define CHOPSTICK2  "/chopstick2"
sem_t* rSide;
sem_t* lSide;

//global done variable that is used to end program
int done;

//eat method that prints philosopher eating message
void eat(int phil) {
    //print message
	fprintf(stdout, "Philosopher #%d is eating\n", phil);
    //variable that will be used for usleep (mod 1 million done because of slack comment from student)
    int eating = rand()%(1000000+1);
    //sleep for random amount of time
	usleep((useconds_t) eating);
}

//think method that prints philosopher thinking message
void think(int phil) {
    //print message
	fprintf(stdout, "Philosopher #%d is thinking\n", phil);
    //variable that will be used for usleep (mod 1 million done because of slack comment from student)
    int thinking = rand()%(1000000+1);
    //sleep for random amount of time
	usleep((useconds_t) thinking);
}

//method to set done to number
void giveDoneVal() {
    //initialized
	done = 1;
}

//method to get done variable
int getDoneVal() {
    //get value in done
	return done;
}

//signal handler method
void checkSig() {
    //go to giveDoneVal() method
	giveDoneVal();
}

//method to remove system resources
void closeSems() {
    //close right side
    sem_close(rSide);
    //close left side
    sem_close(lSide);
    //unlink
    sem_unlink(CHOPSTICK1);
    //unlink
    sem_unlink(CHOPSTICK2);
    //destroy right side
    sem_destroy(rSide);
    //destroy left side
    sem_destroy(lSide);
}

//main method
int main(int argc, char** argv) {
    //if argc has exactly 3 values
	if(argc == 3) {
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
            int cycles = 0;
            //send signal to sigHandler function
            signal(SIGTERM, checkSig);
            //initialize right-handed
            rSide = sem_open(CHOPSTICK1, O_CREAT, 0660, 1);
            //initialize left-handed
            lSide = sem_open(CHOPSTICK2, O_CREAT, 0660, 1);
            //do the code below
            do {
                //wait on right-handed semaphore
                sem_wait(rSide);
                //wait on left-handed semaphore
                sem_wait(lSide);
                //send arg to eat function
                eat(position);
                //signal that right side is free
                sem_post(rSide);
                //signal that left side is free
                sem_post(lSide);
                //send arg to think function
                think(position);
                //increment counter
                cycles++;
            }
            while(getDoneVal()); 
            //if done
            if(getDoneVal() != 1) {
                //print message to stderr
                fprintf(stderr, "Philosopher #%d completed %d cycles.\n", position, cycles);
            }
            closeSems();
        }
	}
    //otherwise
    else {
        //print message to stderr
		fprintf(stdout, "Error: Please give number of seats and position.\n");
    }
    return 0;
}
