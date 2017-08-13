CXX = g++
CPPFLAGS = -lncurses       # put pre-processor settings (-I, -D, etc) here
CXXFLAGS = -Wall  # put compiler settings here
LDFLAGS =         # put linker settings here

all: t

t: intro.cpp
	g++ intro.cpp -lncurses -o intro

run:
	./intro


