CC = g++
CFLAGS = -std=c++0x -Wall
DEPS = intro.cpp
OBJ = git/util.o util/logger.o util/system.o

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $< -o  $@

intro.out: $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) intro.cpp -o $@ $(OBJ) -lncurses -lmenu

%.cpp:
	$(CC) $(CFLAGS) -c  $@ $<
	
