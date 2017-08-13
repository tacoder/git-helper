CC = g++
CFLAGS = -Wall
DEPS = intro.cpp
OBJ = git/util.o

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $< -o  $@

intro.out: $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) intro.cpp -o $@ $< -lncurses

%.cpp:
	$(CC) $(CFLAGS) -c  $@ $<
	
