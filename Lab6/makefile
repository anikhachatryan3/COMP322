# Name: Ani Khachatryan
# Project: Lab 6 - Wack a Mole

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLE_SPIRITD = spiritd
EXECUTABLE_MOLES = moles

SRC_SPIRITD = spiritd.c
OBJ_SPIRITD = spiritd.o

SRC_MOLES = moles.c
OBJ_MOLES = moles.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC = gcc
CFLAGS = -g -Wall -Wextra

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLE_SPIRITD) $(EXECUTABLE_MOLES)

spiritd: $(EXECUTABLE_SPIRITD)

moles: $(EXECUTABLE_MOLES)

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLES_SPIRITD): $(SRC_SPIRITD)
	$(CC) $(CFLAGS) -c $(SRC_SPIRITD)
	$(CC) $(CFLAGS) -o $@ $(OBJ_SPIRITD)

$(EXECUTABLE_MOLES): $(SRC_MOLES)
	$(CC) $(CFLAGS) -c $(SRC_MOLES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_MOLES)

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLE_SPIRITD) $(OBJ_SPIRITD) *~
	rm -f $(EXECUTABLE_MOLES) $(OBJ_MOLES) *~
