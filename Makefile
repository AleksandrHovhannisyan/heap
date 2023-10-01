CC = g++
CFLAGS = -std=c++20 -Wall

.PHONY: clean

heap: main.cpp heap.h
	$(CC) $(CFLAGS) -o heap main.cpp heap.h

clean:
	rm -f heap
