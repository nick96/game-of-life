CPP=g++
CFLAGS=-Wall -Wextra -std=c++17
SFML_LDFLAGS=$(shell pkg-config --libs sfml-all)
NCURSES_LDFLAGS=-lncurses
SFML_OBJ=sfml_main.o GameOfLife.o
NCURSES_OBJ=ncurses_main.o GameOfLife.o util.o NcursesCpp.o
SFML_EXE=gol_sfml
NCURSES_EXE=gol_ncurses

all: $(SFML_EXE) $(NCURSES_EXE)

$(SFML_EXE): $(SFML_OBJ)
	$(CPP) $(SFML_OBJ) $(CFLAGS) -o $(SFML_EXE) $(SFML_LDFLAGS)

$(NCURSES_EXE): $(NCURSES_OBJ)
	$(CPP) $(NCURSES_OBJ) $(CFLAGS) -o $(NCURSES_EXE) $(NCURSES_LDFLAGS)

%.o: $.cpp
	$(CPP) -c $(CFLAGS) -o $*.o $*.cpp

clean:
	rm $(SFML_OBJ) $(SFML_EXE) $(NCURSES_OBJ) $(NCURSES_EXE)
