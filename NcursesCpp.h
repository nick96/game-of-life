// -*- mode: c++ -*-
/**
 *   \file NcursesCpp.h
 *   \brief Ncurses wrapper header.
 *
 *  Wraps the ncurses functions used in GameOfLife to make it more
 *  object oriented. This could do with a lot of work but the aim is
 *  to abstract it so I can make it more idiomatic without effecting
 *  the game of life simulation.
 *
 */
#ifndef NcursesCpp_H
#define NcursesCpp_H

#include <string>
#include <utility>

using namespace std;

class NcursesCpp
{
public:
  NcursesCpp();
  NcursesCpp(bool delay, bool cursor, bool use_keypad);
  void mvprintstr(int y, int x, string str);
  void refresh_screen(void);
  char getchar(void);
  void clear_screen(void);
  void end_window(void);
  pair<int, int> get_max_xy(void);
};

#endif
