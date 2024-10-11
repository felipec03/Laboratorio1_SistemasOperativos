# Makefile for C project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC = cut.c srep.c count.c archivos.c

# Object files
OBJ = cut.o srep.o count.o archivos.o

# Executable files
EXECUTABLES = cut srep count

# Default target
all: $(EXECUTABLES)

# Rules to create each executable
cut: cut.o archivos.o
	$(CC) -o $@ $^

srep: srep.o archivos.o
	$(CC) -o $@ $^

count: count.o archivos.o
	$(CC) -o $@ $^

# Compiling source files to object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

# Additional rule for archivos.c without a header
archivos.o: archivos.c
	$(CC) $(CFLAGS) -c $<

# Clean up build files
clean:
	rm -f $(OBJ) $(EXECUTABLES)

.PHONY: all clean
