# Compiler and flags
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic

# Executable names

EXEC1 = a2q1

# Source files for question 1
Q1_SRC = q1.c q1_functions.c
Q1_HEADER = q1.h


# Default target
all: $(EXEC1)

# Rule to build a2q1
$(EXEC1): $(Q1_SRC) $(Q1_HEADER)
	$(CC) $(CFLAGS) -o $(EXEC1) $(Q1_SRC)

#Clean up object files and executables
clean:
	rm -f $(EXEC1)