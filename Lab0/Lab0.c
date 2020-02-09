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
#include <unistd.h>
#include <fcntl.h>

int i;
//counter variable
int count = 0;
//new char array to store file content in
char arr[9];
//new int array for storing converted char array as int
int array[8];

//method that checks if number is even or odd
void checkParity(int count) {
    //if divisible by 2
    if(count%2 == 0) {
        //then print even
        printf("\tEVEN");
    }
    //if not
    else {
        //then print odd
        printf("\tODD");
    }
}

//method to convert from binary to decimal
void binToDecAndChar(int dec) {
    count = 0;
    //decimal variable
    for(i = 0; i < 8; i++) {
        //if there is a 1 in the binary number
        if(array[i] == 1) {
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

    //print if even or odd
    checkParity(count);
}

//method that converts binary to decimal
void convert(char* arr) {
    //decimal variable
    int dec = 0;
    for(int i = 0; i < 8; i++) {
        //converting from char to int and storing in int array
        array[i] = arr[i] - '0';
        //printing int array
        printf("%d", array[i]);
        //converting binary to decimal
        dec += (arr[i] - '0') << (7-i);
    }
    //call method to convert to decimal and ASCII
    binToDecAndChar(dec);
}

void padding(char* arr, int counter) {
    for(i = counter; i < 8; i++) {
        arr[counter] = '0';
        counter++;
    }
    arr[9] = '\0';

    convert(arr);
}

//method to read the file
void readFile(char* filename) {
    //file destination variable
    int fd;
    //buffer variable
    char buffer;
    //counter variable
    int counter = 0;
    //opening and reading file
    fd = open(filename, O_RDONLY);
    while(read(fd, &buffer, 1) > 0) {
        //if buffer is a number
        if(buffer == '0' || buffer == '1') {
            //store into char array
            arr[counter] = buffer;
            //increment counter
            counter++;
        }
        //if buffer is not a number or is a space
        if((buffer == ' ' || buffer == '\n') || (buffer != '1' && buffer != '0')) {
            //check if counter is less than 8. if so
            if(counter < 8) {
                //pad numer/array
                padding(arr, counter); 
            }
            //if not
            else {
                //just convert (skip padding)
                convert(arr);
            }
            //reset counter
            counter = 0;

            printf("\n");
        }
    }
}

//method to read argv as input (not from a file)
void readArg(char* argv) {
    //counter variable
    int counter = 0;
    for(i = 0; i <= 8; i++) {
        //if argv is a number
        if(argv[i] == '0' || argv[i] == '1') {
            //save number to arr (char array)
            arr[counter] = argv[i];
            //increment counter
            counter++;
        }
        //if argv is a space, new line, or not a number
        if((argv[i] == ' ' || argv[i] == '\n') || (argv[i] != '1' && argv[i] != '0')) {
            //if counter is less than 8
            if(counter < 8) {
                //call method to add padding
                padding(arr, counter);
            }
            //else
            else {
                //just convert (skip padding)
                convert(arr);
            }
            //reset counter
            counter = 0;

            printf("\n");
        }
    }
}

//main method
int main(int argc, char** argv) {
    printf("\nOriginal   ASCII    Decimal    Parity\n");
    printf("--------   -------  --------   --------\n");
    //if no input given
    if(argc <= 1) {
        //Error out
        printf("Error");
        return 1;
    }
    //else
    else {
        //if input is a number or '-'
        if(argv[1][0] == '1' || argv[1][0] == '0'|| argv[1][0] == '-') {
            //call method to convert inputs
            int i = 1;
            while(i < argc) {
                readArg(argv[i]);
                i++;
            }
        }
        //if input is not a number or '-'
        else if(!(argv[1][0] == '1' || argv[1][0] == '0'|| argv[1][0] == '-')) {
            //call method to read file
            readFile(argv[1]);
        }
    }
    printf("\n");

    return 0;
}
