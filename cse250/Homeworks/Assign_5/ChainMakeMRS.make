#  Makefile: Editing of Tim Budd's "Makefile" by Bina Ramamurthy and 
#  Ken Regan, Fall 1996, and again by KWR in Spring 2000.
#  Tailored for ChainMakeMRS.make by MRS for CSE250, Spring 2014.
#
#  USAGE---enter at command prompt in directory:  make -f LinkMain.make


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

all:	 ChainClientMRS

# Invoke this via "make -f ChainMake.make clean".  No "-" before "clean"!
clean:
	$(RM) *$(OBJ)    # ISR/*$(OBJ)---etc. for any subdirectories


StringWrap.o: StringWrap.cpp StringWrap.h  
	$(CC) -c StringWrap.cpp

ChainClientMRS.o: ChainClientMRS.cpp
	$(CC) -c ChainClientMRS.cpp

ChainClientMRS: ChainClientMRS.o StringWrap.o
	$(CC) -o ChainClientMRS ChainClientMRS.o StringWrap.o

#PhraseDriverKWR.o: PhraseDriverKWR.cpp StringWrapKWR.h PhraseKWR.h 
#	$(CC) -c PhraseDriverKWR.cpp

#phrasedriver: PhraseDriverKWR.o PhraseKWR.o StringWrapKWR.o
#	$(CC) -o phrasedriver PhraseDriverKWR.o PhraseKWR.o StringWrapKWR.o $(LIBS)

# The .o file with main should come before all the other object files in the
# final linking stage.

