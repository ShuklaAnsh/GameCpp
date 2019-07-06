#CC specifies which compiler we're using
CC = g++

#LINKER_FLAGS specifies the libraries we're linking against
LFLAGS = -lSDL2main -lSDL2 -lSDL2_image

clean :
	$(RM) *.o

Minesweeper: Game.o Minesweeper/Minesweeper.o Minesweeper/Main.cpp
	$(CC) Game.o Minesweeper/Minesweeper.o Minesweeper/Main.cpp -o MinesweeperGame $(LFLAGS)