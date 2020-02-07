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

int i;
int dec = 0;
//counter variable
int count = 0;
//new char array to store file content in
char arr[9];

//method to check if number is odd or even
void checkParity(int count) {
    //if divisible by 2:
    if(count%2 == 0) {
        //then print even
        printf("\tEVEN\t");
    }
    //if not:
    else {
        //then print odd
        printf("\tODD\t");
    }
}

//method to read the file
void readFile() {
    //new array
    // char arr[9];  //was arr[8] but gave abort trap: 6
    //opening file
    FILE *rFile = fopen("inputFile.txt", "r");
    //reading/scanning content in file
    while((fscanf(rFile, "%s", arr)) != EOF) {
        // printf("%s", arr);
        int nul = 0;
        for(i = 0; i < 8; i++) {
            if(arr[i] == '\0') {
                nul = 1;
            }
            //if binary number is less than 8:
            if(nul == 1) {
                //pad with zeros (0)
                arr[i] = '0';
            }
        }
        // printf("%s    ", arr);
        // printf("\t");
        
        //creating new int array
        int array[8];
        for(int i = 0; i < 8; i++) {
            //converting from char to int and storing in int array
            array[i] = arr[i] - '0';
            //printing int array
            printf("%d", array[i]);
        }

        // ascii
        int dec = 0;
        for(i = 0; i < 8; i++) {
            // dec = dec << 1 | array[i];
            // dec = dec * 2 + array[i];
            if(array[i] == 1) {
                // printf("%f + ", pow(2, i));
                dec += pow(2, 8-i)/2;
                count++;
            }
            printf("");
        }

        if(dec >= 128) {
            dec -= 128;
        }

        printf("\t%c", (char)dec);

        printf("\t%d\t", dec);

        //checking if even or odd
        checkParity(count);
        //resetting counter
        count = 0;

        printf("\n");
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
// gcc -o file file.o -lm
// ./file
