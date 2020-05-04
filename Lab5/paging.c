//Name: Ani Khachatryan
//Date: 26 April 2020
//Assignment: Lab 5 - Page/Offset Calculation
//Purpose:  To develop a single program that calculates the page number and 
//          the offset within the page for a given virtual memory address.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//method to calculate and print offset value
void offsetCalc(int input, int page) {
    //get actual page size and store in totPage variable
    unsigned long totPage = page * pow(2, 12);
    //subtract input value by actual page and store in offset variable
    int offset = input - totPage;
    //print offset value
    printf("offset = %d\n", offset);
}

//method to calculate and print page number
void pageCalc(unsigned long input) {
    //divide input by 4096 (4k page size) and store value in page valiable
    unsigned long page = input/(pow(2, 12));
    //print page number
    printf("page number = %lu\n", page);
    //send page number and input to offsetCalc method
    offsetCalc(input, page);
}

//method to print out number user gave
void printOut(char** argv) {
    //print user input
    printf("The address %s contains: \n", *argv);
    //change input from char** to int and store in input variable
    unsigned long input = atol(*argv);
    //send input to pageCalc method
    pageCalc(input);
}

//main method
int main(int argc, char** argv) {
    //if the user input is more than or less than 2
    if(argc < 2 || argc > 2) {
        //print error message
        printf("Error: please provide an address in this format: ./paging <address>\n");
    }
    //if the user enters a negative address
    else if(atol(argv[1]) < 0) {
        //print error message
        printf("Error: please provide a positive address\n");
    }
    //if the user gives a value bigger than 32 bits
    else if(atol(argv[1]) >= pow(2, 32)) {
        //print error message
        printf("Error: please give a 32-bit address\n");
    }
    //otherwise
    else {
        //go to printOut method
        printOut(&argv[1]);
    }
}
