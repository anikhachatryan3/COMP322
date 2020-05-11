//Name: Ani Khachatryan
//Date: 07 May 2020
//Assignment: Lab 7 - Asynchronous Elephant
//Purpose: To create a program that performs perform matrix addition. Within this program, 
//         however, you will perform the operation in blocks (aka bites). Moreover, you will
//         read the blocks from a text file asynchronously. (matrix_gen is a program that
//         creates a file of integers that represents a NxN matrix.)

#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

//method to make the matrix of random numbers
void makeMatrix(char* argv) {
    //create integer i and j variables
    int i;
    int j;
    //create and initialize size variable
    int size = atoi(argv);
    //double char matrix variable
    int** matrix = (int**)malloc(size * sizeof(int*));
    //if the size is 0 or smaller
    if(size <= 0) {
        //print error message on stderr
        fprintf(stderr, "Error: invalid size\n");
    }
    //otherwise
    else{
        srand(time(0));
        //create and initialize txtFile variable
        FILE* matrixFile = fopen("matrix_file.size", "w");
        //for each i that's smaller than the given size
        for(i = 0; i < size; i++) {
            //allocate space in that row
            matrix[i] = (int*)malloc(size*sizeof(int));
            //for each i that's smaller than the given size
            for(j = 0; j < size; j++) {
                //that position in the matrix is given a random number between -100 and 100
                matrix[i][j] = (rand()%(100 - (-100) + 1)) - 100;
                //store the generated matrix number in a file
                fprintf(matrixFile, "%4d", *(*(matrix+i)+j));
            }
            //after a full row, start over on a new line
            fprintf(matrixFile, "\n");
        }
        //print success message
        printf("Matrix created successfully in matrix_file.size\n");
        //close the file
        fclose(matrixFile);
    }
}

//main method
int main(int argc, char** argv) {
    //if given more than or less than 2 args
    if(argc != 2) {
        //print error message on stderr
        fprintf(stderr, "Error: please provide a size for the array\n");
    }
    //otherwise
    else {
        //call method to make the matrix
        makeMatrix(argv[1]);
    }

    return 0;
}
