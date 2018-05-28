/**
 *   \file NcursesCpp.cpp
 *   \brief Ncurses wrapper.
 *
 *  Wraps the ncurses functions used in GameOfLife to make it more
 *  object oriented. This could do with a lot of work but the aim is
 *  to abstract it so I can make it more idiomatic without effecting
 *  the game of life simulation.
 *
 */
#include "NcursesCpp.h"
#include <ncurses.h>
#include <string>
#include <utility>

using namespace std;

NcursesCpp::NcursesCpp()
{
  return;
}

NcursesCpp::NcursesCpp(bool delay, bool cursor, bool use_keypad)
{
  initscr();
  noecho();
  nodelay(stdscr, delay);
  curs_set(cursor);
  keypad(stdscr, use_keypad);
}

void
NcursesCpp::mvprintstr(int y, int x, string str)
{
  mvprintw(y, x, str.c_str());
}

void
NcursesCpp::refresh_screen(void)
{
  refresh();
}

char
NcursesCpp::getchar(void)
{
  return getch();
}

void
NcursesCpp::clear_screen()
{
  clear();
}

void
NcursesCpp::end_window(void)
{
  endwin();
}

pair<int, int>
NcursesCpp::get_max_xy()
{
  int x, y;
  getmaxyx(stdscr, y, x);
  return make_pair(y, x);
}
