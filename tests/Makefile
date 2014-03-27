CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11 -Weffc++
OBJS = ../TCPSocket.o
TESTS = server.o client.o

all: $(TESTS) tests

tests: server

server: $(TESTS)
	g++ -o server -lgtest -lgtest_main server.o $(OBJS)
	./server

clean:
	$(RM) $(TESTS) $(basename $(TESTS))
