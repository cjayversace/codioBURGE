signals: signal.c
	gcc signal.c -o signalab 


signals: signal.c
	gcc signal.c -o signalab 

CC = gcc
CFLAGS = -Wall -g
TARGET = my3proc
SOURCES = main3.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
