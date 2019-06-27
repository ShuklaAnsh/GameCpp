#OBJS specifies which files to compile as part of the project
OBJS =  Game.cpp \
		Character.cpp

#CC specifies which compiler we're using
CC = g++

#LINKER_FLAGS specifies the libraries we're linking against
LFLAGS = -lSDL2main -lSDL2 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) $(LFLAGS) $(CFLAGS)