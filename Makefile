CC = g++
CFLAGS = -std=c++11 -Wall
SRC_DIR = .

all: test

test: test.o server.o thdpool.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: $(SRC_DIR)/test.cpp server.h
	$(CC) $(CFLAGS) -c $< -o $@

server.o: $(SRC_DIR)/server.cpp server.h thdpool.h
	$(CC) $(CFLAGS) -c $< -o $@

thdpool.o: $(SRC_DIR)/thdpool.cpp thdpool.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test
