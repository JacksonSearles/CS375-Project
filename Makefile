TARGET = huffman

CC = g++
CFLAGS = -Wall -O2 -no-pie

all: $(TARGET)

$(TARGET): huffman.o
	$(CC) $(CFLAGS) -o $(TARGET) huffman.o

huffman.o: huffman.cpp
	$(CC) $(CFLAGS) -c huffman.cpp

clean:
	rm -f $(TARGET) *.o