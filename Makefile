# Makefile for sudokuSolver System
# Currently only makes testing system
# Author: Sebastian Turner 
# Date: 08/27/19

PROG = boardTest

OBJS = boardTest.o sudokuBoard.o
CFLAGS = -Wall -pedantic -std=c11 -ggdb 
CC = gcc
MAKE = makes

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

boardTest.o: sudokuBoard.h

.PHONY clean

clean:
	rm -f *~ *.o
	rm -f $(PROG)