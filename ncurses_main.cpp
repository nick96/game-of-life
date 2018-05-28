/**
 *   \file main.cpp
 *   \brief Main file for running game of life simulation.
 *
 *  Main file for building the game of life simulation
 *  executable. This simply constructs a GameOfLife object with the
 *  cell_count, length and width provided as command line arguments or
 *  determined by the terminal dimensions (if specified length/width
 *  is less than zero) then plays the simulation.
 *
 */


#include "GameOfLife.h"
#include "NcursesCpp.h"
#include "util.h"
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <sstream>

using namespace std;

void play(GameOfLife gol);
void ncurses_board(NcursesCpp screen, GameOfLife gol);

int
main(int argc, char* argv[])
{
  int cell_count = argc > 1 ? atoi(argv[1]) : -1;
  int length = argc > 2 ? atoi(argv[2]) : -1;
  int width = argc > 3 ? atoi(argv[2]) : -1;
  GameOfLife gol(cell_count, length, width);
  play(gol);
}

void play(GameOfLife gol) {
  NcursesCpp screen;
  ifstream greet_file("greet.txt");
  string greeting = "", line;
  if (greet_file.is_open()) {
    while (getline(greet_file, line))
      greeting += line + "\n";
  }
  greet_file.close();
  screen.mvprintstr(10, 0, greeting);
  screen.refresh_screen();
  // Wait for user to press return key
  while (screen.getchar() != 10)
    ;

  int delay = 100;
  while (gol.is_alive()) {
    screen.clear_screen();
    ncurses_board(screen, gol);
    screen.refresh_screen();
    gol.step();
    cout << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    char input = screen.getchar();
    if (input == 'q') {
      break;
    } else if (input == '+') {
      delay += 100;
    } else if (input == '-') {
      delay -= 100;
    }
  }
  screen.end_window();
}

void ncurses_board(NcursesCpp screen, GameOfLife gol)
{
  string line = "+" + repeat("-", (gol.get_width() * 4) - 1) + "+";
  screen.mvprintstr(0, 0, line);
  for (int x = 0; x < gol.get_width(); x++) {
    ostringstream stream;
    stream << "|";
    for (int y = 0; y < gol.get_height(); y++) {
      if (gol.get_board()[x][y]) {
        stream << " ⬤ |";
      } else {
        stream << "   |";
      }
    }
    screen.mvprintstr(2 * x + 1, 0, stream.str());
    screen.mvprintstr(2 * x + 2, 0, line);
  }
}

