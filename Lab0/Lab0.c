//Name: Ani Khachatryan
//Date: 25 January 2020
//Class: COMP322/L
//Assignment: Lab 0 - Making Sense of Ones and Zeros
//Purpose: To write a command line tool that will read a series of 1’s and 0’s from a file 
//         that consists of: the original value, the corresponding ASCII character, the 
//         corresponding decimal value, and the value of either EVEN or ODD depending on 
//         the number of 1's set.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void readFile() {
    char arr[8];
    // int count;
    // int i = 0;
    FILE *rFile = fopen("inputFile.txt", "r");
    // fscanf(rFile, "%s", c);
    while((fscanf(rFile, "%s", arr)) != EOF) {
        printf("%s\n", arr);
    }
    fclose(rFile);
}

int main() {
    printf("\nOriginal   ASCII   Decimal   Parity\n");
    printf("--------  -------  --------  -------\n");
    readFile();
    printf("\n");

    return 0;
}


//Compile:
// gcc -c file.c -Wall -Wextra
// gcc -o file file.o -lm ??
// ./file
