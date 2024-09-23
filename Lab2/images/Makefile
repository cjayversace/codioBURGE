prog1: main.c
	gcc main.c -o prog1

prog2: main2.c
	gcc main2.c -o prog2

my3proc: main3.c
	gcc main3.c -o my3proc

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Targets
TARGETS = prog1 prog2 my3proc

# Source files
SOURCES = main.c main2.c main3.c

# Default target
all: $(TARGETS)

# Compile prog1
prog1: main.c
	$(TARGET): $(SOURCECC) $(CFLAGS) main.c -o prog1

# Compile prog2
prog2: main2.c
	$(CC) $(CFLAGS) main2.c -o prog2

# Compile my3proc
my3proc: main3.c
	$(TARGETCC) $(SOURCECFLAGS) main3.c -o my3proc

# Clean up the binaries
clean:
	rm -f $(TARGETS)
