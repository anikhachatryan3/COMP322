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
//decimal variable
int dec;
//counter variable
int count = 0;
//new char array to store file content in
char arr[9];  //was arr[8], but gave "abort trap: 6"
//new int array for storing converted char array as int
int array[8];

//method to convert from binary to decimal
void binToDecAndChar(int dec) {
    dec = 0;
    for(i = 0; i < 8; i++) {
        //if there is a 1 in the binary number
        if(array[i] == 1) {
            //convert to decimal
            dec += pow(2, 8-i)/2;
            //increment counter
            count++;
        }
    }

    //if decimal number is bigger than the number of asciis (127)
    if(dec >= 128) {
        //subtract decimal by number of asciis (128)
        dec -= 128;
    }
    //print decimal as ASCII character
    printf("\t%c", (char)dec);

    //print ascii decimal
    printf("\t%d", dec);
}

//method to check if number is odd or even
void checkParity(int count) {
    //if divisible by 2:
    if(count%2 == 0) {
        //then print even
        printf("\tEVEN");
    }
    //if not:
    else {
        //then print odd
        printf("\tODD");
    }
}

//method to convert char array to int array
void convert(char* arr) {
    for(int i = 0; i < 8; i++) {
            //converting from char to int and storing in int array
            array[i] = arr[i] - '0';
            //printing int array
            printf("%d", array[i]);
        }
}

//method to read the file
void readFile() {
    //opening and reading file
    FILE *rFile = fopen("inputFile.txt", "r");
    //reading/scanning content in file until end of file
    while((fscanf(rFile, "%s", arr)) != EOF) {
        //
        int nul = 0;
        for(i = 0; i < 8; i++) {
            if(arr[i] == '\0') {
                nul = 1;
            }
            //if binary number is less than 8:
            if(nul == 1) {
                //pad with zeros (0) to the right of binary number
                arr[i] = '0';
            }
        }

        convert(arr);

        //calling method to convert binary number to decimal and ASCII
        binToDecAndChar(dec);

        //checking if even or odd
        checkParity(count);
        //resetting counter
        count = 0;

        printf("\n");
    }
    fclose(rFile);
}


int main() {
    printf("\nOriginal   ASCII    Decimal    Parity\n");
    printf("--------   -------  --------   --------\n");
    readFile();
    printf("\n");

    return 0;
}
