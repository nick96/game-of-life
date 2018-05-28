CPP=g++
CFLAGS=-Wall
LDFLAGS=$(shell pkg-config --libs sfml-all)
OBJ=main.o GameOfLife.o
EXE=gol

$(EXE): $(OBJ)
	$(CPP) $(OBJ) -o $(EXE) $(LDFLAGS)

GameOfLife.o: $(OBJ)
	$(CPP) $(CFLAGS) -c GameOfLife.cpp

clean:
	rm $(OBJ) $(EXE)
