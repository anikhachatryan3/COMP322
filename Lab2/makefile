# Name: Ani Khachatryan
# Project: Lab 2 - Launch-Tube

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES = launch tube
SRC_LAUNCH = launch.c
OBJ_LAUNCH = launch.o

SRC_TUBE = tube.c
OBJ_TUBE = tube.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC = gcc
CFLAGS = -g -Wall -Wextra

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLES)

launch: $(OBJ_LAUNCH)
	$(CC) $(SRC_LAUNCH) $(CFLAGS) -o launch

tube: $(OBJ_TUBE)
	$(CC) $(SRC_TUBE) $(CFLAGS) -o tube


# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLES) $(OBJ_LAUNCH) *~
	rm -f $(EXECUTABLES) $(OBJ_TUBE) *~
