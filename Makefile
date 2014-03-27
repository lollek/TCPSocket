CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11 -Weffc++
OBJS = TCPSocket.o

all: $(OBJS)

test: all
	@cd tests && make && cd ..

clean:
	$(RM) $(OBJS)

