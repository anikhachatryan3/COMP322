# Name: Ani Khachatryan
# Project: Lab 7 - Asynchronous Elephant

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLE_GEN = matrix_gen
EXECUTABLE_ADD = matrix_add

SRC_GEN = matrix_gen.c
OBJ_GEN = matrix_gen.o

SRC_ADD = matrix_add.c
OBJ_ADD = matrix_add.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC = gcc
CFLAGS = -g -Wall -Wextra

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLE_GEN) $(EXECUTABLE_ADD)

matrix_gen: $(EXECUTABLE_GEN)

matrix_add: $(EXECUTABLE_ADD)

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLES_GEN): $(SRC_GEN)
	$(CC) $(CFLAGS) -c $(SRC_GEN)
	$(CC) $(CFLAGS) -o $@ $(OBJ_GEN)

$(EXECUTABLE_ADD): $(SRC_ADD)
	$(CC) $(CFLAGS) -c $(SRC_ADD)
	$(CC) $(CFLAGS) -o $@ $(OBJ_ADD)

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLE_GEN) $(OBJ_GEN) *~
	rm -f $(EXECUTABLE_ADD) $(OBJ_ADD) *~
