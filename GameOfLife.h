// -*- mode: c++ -*-
/**
 *   \file GameOfLife.h
 *   \brief Head file for GameOfLife.
 *
 *  Defines the GameOfLife and the accompanying structure
 *  `StateChange`. This file declares all the member functions and
 *  attributes for inclusion in other files.
 *
 */

#ifndef GameOfLife_H
#define GameOfLife_H

#include <vector>

enum StateChange {
	NoChange, /*!< Do not change the state of the cell. */
	Resurect, /*!< Change cell state from dead to alive. */
	Kill,     /*!< Change cell state from alive to dead. */
};

class GameOfLife {
      public:
	GameOfLife(int cell_count, int len, int width);
	void play(void);
	std::vector<std::vector<bool>> get_board();
	void step();

      private:
	std::vector<std::vector<bool>> board;
	int height;
	int width;
	int cell_count;
	int step_count;
	int kill_count;
	int resurect_count;
	int no_change_count;

	enum StateChange cell_state_change(int x, int y);
	void resurect_cell(int x, int y);
	void kill_cell(int x, int y);
	int get_neighbour_count(int x, int y);
	bool is_alive(void);
	int get_nsteps(void);
};
#endif
