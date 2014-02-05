CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11 -Weffc++
OBJS = TCPSocket.o

all: $(OBJS)

tests: $(OBJS)
	$(CXX) $(CXXFLAGS) -o TCPSocket_example/example_client $(OBJS) TCPSocket_example/example_client.cc
	$(CXX) $(CXXFLAGS) -o TCPSocket_example/example_server $(OBJS) TCPSocket_example/example_server.cc


