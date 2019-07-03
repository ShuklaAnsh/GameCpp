#OBJS specifies which files to compile as part of the project
OBJS =  Minesweeper.cpp test.cpp

#CC specifies which compiler we're using
CC = g++

#LINKER_FLAGS specifies the libraries we're linking against
LFLAGS = -lSDL2main -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Minesweeper.o

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) -c $(OBJ_NAME) $(LFLAGS)

test : $(OBJS)
	$(CC) $(OBJS) -o test $(LFLAGS)

Graph : Graph.cpp
	$(CC) Graph.cpp -o Graph

clean:
	$(RM) *.o