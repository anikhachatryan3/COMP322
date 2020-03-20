//Name: Ani Khachatryan
//Date: 25 January 2020
//Class: COMP322/L
//Assignment: Lab 0 - Making Sense of Ones and Zeros
//Purpose: To write a command line tool that will read a series of 1’s and 0’s from a file 
//         that consists of: the original value, the corresponding ASCII character, the 
//         corresponding decimal value, and the value of either EVEN or ODD depending on 
//         the number of 1's set.

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

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
    if(dec > 32 && dec != 127) {
        //check if number is ascii
        if(isascii(dec)) {
            printf("\t%c", (char)dec);
        }
    }
    //if non printable ascii character, look for them here and print
    else {
        if(dec == 0) {
            printf("      NUL");
        }
        else if(dec == 1) {
            printf("      SOH");
        }
        else if(dec == 2) {
            printf("      STX");
        }
        else if(dec == 3) {
            printf("      ETX");
        }
        else if(dec == 4) {
            printf("      EOT");
        }
        else if(dec == 5) {
            printf("      ENQ");
        }
        else if(dec == 6) {
            printf("      ACK");
        }
        else if(dec == 7) {
            printf("      BEL");
        }
        else if(dec == 8) {
            printf("      BS");
        }
        else if(dec == 9) {
            printf("      TAB");
        }
        else if(dec == 10) {
            printf("      LF");
        }
        else if(dec == 11) {
            printf("      VT");
        }
        else if(dec == 12) {
            printf("      FF");
        }
        else if(dec == 13) {
            printf("      CR");
        }
        else if(dec == 14) {
            printf("      SO");
        }
        else if(dec == 15) {
            printf("      SI");
        }
        else if(dec == 16) {
            printf("      DLE");
        }
        else if(dec == 17) {
            printf("      DC1");
        }
        else if(dec == 18) {
            printf("      DC2");
        }
        else if(dec == 19) {
            printf("      DC3");
        }
        else if(dec == 20) {
            printf("      DC4");
        }
        else if(dec == 21) {
            printf("      NAK");
        }
        else if(dec == 22) {
            printf("      SYN");
        }
        else if(dec == 23) {
            printf("      ETB");
        }
        else if(dec == 24) {
            printf("      CAN");
        }
        else if(dec == 25) {
            printf("      EM");
        }
        else if(dec == 26) {
            printf("      SUB");
        }
        else if(dec == 27) {
            printf("      ESC");
        }
        else if(dec == 28) {
            printf("      FS");
        }
        else if(dec == 29) {
            printf("      GS");
        }
        else if(dec == 30) {
            printf("      RS");
        }
        else if(dec == 31) {
            printf("      US");
        }
        else if(dec == 32) {
            printf("    Space");
        }
        else if(dec == 127) {
            printf("      DEL");
        }
    }
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

//method to add padding
void padding(char* arr, int counter) {
    //pad until i < 8
    for(i = counter; i < 8; i++) {
        arr[counter] = '0';
        //increment counter
        counter++;
    }
    arr[9] = '\0';
    //call method to convert binary numbers
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
    if(fd != -1) {
        printf("\nOriginal   ASCII    Decimal    Parity\n");
        printf("--------   -------  --------   --------\n");
        //while number of content in file being read is greater than 0
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
    //otherwise
    else {
        //error
        printf("\nError. Invalid file.\n");
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
        else if((argv[i] == ' ' || argv[i] == '\n') || (argv[i] != '1' && argv[i] != '0')) {
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
        //otherwise
        else {
            //error
            printf("\nError. Invalid input given.\n");
            //break the loop
            break;
        }
    }
}

//method to check if given 8 bit binary is valid input
bool validate8Bit(char* arr) {
    for(int k = 0; k < 8; k++) {
        //if arr[k] reaches end of file
        if(arr[k] == '\0') {
            //it's fine (break)
            break;
        }
        //otherwise
        else {
            //if arr[k] is not 0 or 1
            if(arr[k] != '1' && arr[k] != '0') {
                //not good (false)
                return false;
            }
        }
    }
    return true;
}

//main method
int main(int argc, char** argv) {
    //if no input given
    if(argc <= 1) {
        //error out
        printf("\nError. Please provide input.\n\n");
        return 1;
    }
    //else
    else {
        //if input is a number or '-'
        if(argv[1][0] == '1' || argv[1][0] == '0'|| argv[1][0] == '-') {
            //initialize i to equal 1
            int i = 1;
            //if first input is '-'
            if(argv[1][0] == '-') {
                //then i = 2 and print nothing (except the headers and lines)
                i = 2;
                printf("");
            }
            //initialize j to equal i
            int j = i;
            //while j is less than number of inputs (argc)
            while(j < argc) {
                //if given input not valid
                if(!validate8Bit(argv[j])) {
                    //error
                    printf("\nError. Invalid input given.\n\n");
                    return 1;
                }
                //increment j
                j++;
            }
            printf("\nOriginal   ASCII    Decimal    Parity\n");
            printf("--------   -------  --------   --------\n");
            //while i is less than number of inputs (argc)
            while(i < argc) {
                //call method
                readArg(argv[i]);
                //increment i
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
