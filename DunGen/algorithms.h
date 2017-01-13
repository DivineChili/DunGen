#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include "cell.h"
#include "map.h"
#include "randomizer.h"

class Algorithms
{
public:

	static void recursive_backtracking(int * start_pos, Map * grid, Randomizer mazeRandomizer) {
		using namespace std;
		// Create vector for recursive-backtracking history.
		cout << "Generating..." << endl;
		bool running = true;
		vector<pair<int, int>> history;
		int c = start_pos[0];
		int r = start_pos[1];

		history.push_back({ start_pos[0], start_pos[1] }); // Start at the startingposistion

														   // Recursive backtracing starts here!
		while (running) {

			(*grid).visitCell(c, r);
			//cout << "Visited: [" << c << "][" << r << "]   \t|| ";

			vector<int> check;

			// Check blocks!
			// Check Right
			try {
				if (!(*grid).cellVisited(c + 1, r)) {
					check.push_back(RIGHT);
				}
			}
			catch (const out_of_range& e) { e.what(); }

			// Check Left
			try {
				if (!(*grid).cellVisited(c - 1, r)) {
					check.push_back(LEFT);
				}
			}
			catch (const out_of_range& e) { e.what(); }

			// Check Up
			try {
				if (!(*grid).cellVisited(c, r - 1)) {
					check.push_back(UP);
				}
			}
			catch (const out_of_range& e) { e.what(); }

			// Check Down
			try {
				if (!(*grid).cellVisited(c, r + 1)) {
					check.push_back(DOWN);
				}
			}
			catch (const out_of_range& e) { e.what(); }

			// Choose one of the options!
			//cout << "Avalable options:" << check.size() << "   \t|| ";
			if (check.size() > 0) {

				history.push_back({ c , r });
				//uint32_t mazeHash = XXHash32::hash(mazeKey_p, 4, mazeSeed);
				//mazeKey++;
				//cout << mazeKey << endl;
				//cout << mazeHash << endl;
				uint32_t result = mazeRandomizer.randomizeAtPos(c, r);

				int move_direction = check[static_cast<int>(result) % check.size()];	 // Randomly pick a cell! For use of hash-functions, put stuff here!

																						 //cout << "Moving:  " << move_direction << "   !!!";
				if (move_direction == UP)
				{
					(*grid).toggleCellSideAtPos(c, r, UP, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(UP, true);
					--r;
					(*grid).toggleCellSideAtPos(c, r, DOWN, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(DOWN, true);
				}
				else if (move_direction == DOWN) {

					(*grid).toggleCellSideAtPos(c, r, DOWN, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(DOWN, true);
					++r;
					(*grid).toggleCellSideAtPos(c, r, UP, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(UP, true);
				}
				else if (move_direction == LEFT) {

					(*grid).toggleCellSideAtPos(c, r, LEFT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(LEFT, true);
					--c;
					(*grid).toggleCellSideAtPos(c, r, RIGHT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(RIGHT, true);
				}
				else if (move_direction == RIGHT) {
					(*grid).toggleCellSideAtPos(c, r, RIGHT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(RIGHT, true);
					++c;
					(*grid).toggleCellSideAtPos(c, r, LEFT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(LEFT, true);
				}
			}
			else {
				if (history.size() > 1) {
					//cout << "Backtracking !!!";
					history.pop_back();
					c = history.back().first;
					r = history.back().second;
				}
				else {
					cout << "\nDONE!" << endl;
					running = false;
				}
			}
			//cout << endl;
		}

	}

	static void deadend_remover(Map * grid, int iterations) {
		vector< vector<pair<int, int>>> dead_ends_it;

		dead_ends_it.push_back(grid->dead_ends);

		vector<vector<pair<int, int>>>::iterator it = dead_ends_it.begin();

		// Loop through deadends
		for (; it != dead_ends_it.end(); it++) {
			
			vector<pair<int, int>> sub_dead_ends_it = *it;
			vector<pair<int, int>> new_sub_dead_ends;
			vector<pair<int, int>>::iterator sub_it = sub_dead_ends_it.begin();

			
			for (; sub_it != sub_dead_ends_it.end(); sub_it++) {

				int x = sub_it->first;
				int y = sub_it->second;

				grid->setCellStructureAtPos(x, y, string(9, Cell::empty)); // Just makes the whole cell blank (or to Cell::empty)

				vector<int> openings = grid->getCellopeningsAtPos(x, y);

				if (openings.size() == 1) { // Check if current cell is a deadend. Usefull for iterations > 1
					// Jump to the previous cell and close the opening to this cell. Then check if the cell is a deadend aswell
					if (openings[0] == UP) { --y; grid->toggleCellSideAtPos(x, y, DOWN, false); openings = grid->getCellopeningsAtPos(x, y); if (openings.size() <= 1 && dead_ends_it.size() != iterations) new_sub_dead_ends.push_back({ x,y }); } // The previous cell is above, y-1
					else if (openings[0] == DOWN) { ++y; grid->toggleCellSideAtPos(x, y, UP, false); openings = grid->getCellopeningsAtPos(x, y); if (openings.size() <= 1 && dead_ends_it.size() != iterations) new_sub_dead_ends.push_back({ x,y }); } // The previous cell is bellow, y+1
					else if (openings[0] == LEFT) { --x; grid->toggleCellSideAtPos(x, y, RIGHT, false); openings = grid->getCellopeningsAtPos(x, y); if (openings.size() <= 1 && dead_ends_it.size() != iterations) new_sub_dead_ends.push_back({ x,y }); }  // The previous cell is to the left, x-1
					else if (openings[0] == RIGHT) { ++x; grid->toggleCellSideAtPos(x, y, LEFT, false); openings = grid->getCellopeningsAtPos(x, y); if (openings.size() <= 1 && dead_ends_it.size() != iterations) new_sub_dead_ends.push_back({ x,y }); } // The previous cell is to the right, x+1

				}
			}
			
			// When done with one main iteration, put the new created ends into the main vector. Repeat until iterations are reached or no more dead ends exists.
			if (new_sub_dead_ends.size() != 0 && dead_ends_it.size() != iterations) { dead_ends_it.push_back(new_sub_dead_ends); }
		}
	}
};

#endif // !ALGORITHMS_H