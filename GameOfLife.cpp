/**
 *   \file GameOfLife.cpp
 *   \brief Game of life simulation object.
 *
 *  Defines what is means to be a GameOfLife object and the
 *  companying methods.
 *
 */

#include "GameOfLife.h"
#include "util.h"
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

using namespace std;

// Initialise cell_count on a board of nblocks x nblocks.
GameOfLife::GameOfLife(int n, int hig, int wid) {
        height = hig;
        width = wid;

        if (n < 0) {
                cell_count = (height * width) / 4;
        } else {
                cell_count = n;
        }

        vector<bool> inner(width, false);
        vector<vector<bool>> outer(height, inner);
        board = outer;
        srand(time(0));
        for (int i = 0; i < cell_count; i++) {
                int x, y;
                x = rand() % height;
                y = rand() % width;
                while (board[x][y]) {
                        x = rand() % height;
                        y = rand() % width;
                }
                board[x][y] = true;
        }
}

// Get the number of steps taken in the game so far.
int GameOfLife::get_nsteps() { return step_count; }

// Check there are still cells alive.
bool GameOfLife::is_alive() { return cell_count != 0; }

// Step to the next phase of the game of life.
void GameOfLife::step() {
        for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                        switch (cell_state_change(i, j)) {
                        case NoChange:
                                no_change_count++;
                                break;
                        case Resurect:
                                resurect_count++;
                                resurect_cell(i, j);
                                break;
                        case Kill:
                                kill_count++;
                                kill_cell(i, j);
                                break;
                        }
                }
        }
        step_count++;
        return;
}

// Determine the change in state required for the cell at (x,y).
enum StateChange GameOfLife::cell_state_change(int x, int y) {
        int neighbours = get_neighbour_count(x, y);
        if (board[x][y]) {
                if (neighbours < 2 || neighbours > 3) {
                        return Kill;
                } else {
                        return NoChange;
                }
        } else {
                if (neighbours == 3) {
                        return Resurect;
                } else {
                        return NoChange;
                }
        }
}

// Count the number of live neighbours a cell has.
int GameOfLife::get_neighbour_count(int x, int y) {
        int count = 0;
        int adj[8][2] = {
            // Horizontal neighbours
            {x + 1, y},
            {x - 1, y},

            // Vertical neighbours
            {x, y + 1},
            {x, y - 1},

            // Diagonal neighbours
            {x + 1, y + 1},
            {x + 1, y - 1},
            {x - 1, y + 1},
            {x - 1, y - 1},
        };

        for (int i = 0; i < 8; i++) {
                int x = adj[i][0];
                int y = adj[i][1];
                if (x >= 0 && x < height && y >= 0 && y < width &&
                    board[x][y]) {
                        count++;
                }
        }
        return count;
}

// Bring a cell back from the dead.
void GameOfLife::resurect_cell(int x, int y) {
        assert(board[x][y] == false);
        board[x][y] = true;
}

// Kill a cell.
void GameOfLife::kill_cell(int x, int y) {
        assert(board[x][y]);
        board[x][y] = false;
}

std::vector<std::vector<bool>> GameOfLife::get_board() { return board; }
