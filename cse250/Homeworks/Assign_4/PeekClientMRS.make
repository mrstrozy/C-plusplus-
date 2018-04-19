#  Makefile: Editing of Tim Budd's "Makefile" by Bina Ramamurthy and 
#  Ken Regan, Fall 1996, and again by KWR in Spring 2000.
#  Tailored for PeekClientMRS.make by MRS for CSE250, Spring 2014.
#
#  USAGE---enter at command prompt in directory:  make -f PeekClientMRS.make


# Unix Macros---choose which compiler and options here!

CC     = g++ -Wall     #optional change to: g++ -Wall
# CC     = g++ -fhandle-exceptions -frtti
# CC     = CC     # name of the Sun C++ compiler---NOT available on timberlake
                  # if you have a command-line installation at home (as
                  # opposed to an IDE like Eclipse), put your compiler here.
# CC = gfilt

LIBS   = -lm
OBJ    = .o
RM     = rm -fr


# SYNTAX: Dependencies must be on same line as ":".  Actions must
# follow on succeeding line(s), and have at least one TAB indent.
# Hence, be careful mouse-copying makefile text if tabs convert to spaces.

all:	PeekClientMRS

# Invoke this via "make -f PeekClientMRS.make clean".  No "-" before "clean"!
clean:
	$(RM) *$(OBJ)    # ISR/*$(OBJ)---etc. for any subdirectories



PeekDeque2MRS.o: PeekDeque2MRS.h  
	$(CC) -c PeekDeque2MRS.cpp


PeekClientMRS.o: PeekDeque2MRS.cpp PeekDeque2MRS.h 
	$(CC) -c PeekClientMRS.cpp

PeekClientMRS: PeekDeque2MRS.o PeekClientMRS.o 
	$(CC) -o PeekClientMRS PeekClientMRS.o PeekDeque2MRS.o $(LIBS)

# The .o file with main should come before all the other object files in the
# final linking stage.

