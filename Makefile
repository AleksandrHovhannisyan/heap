CC = g++
CFLAGS = -std=c++20 -Wall

.PHONY: clean

main: main.cpp heap.h
	$(CC) $(CFLAGS) -o main main.cpp heap.h

clean:
	rm -f main
