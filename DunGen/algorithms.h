#pragma once

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
					--r;
					(*grid).toggleCellSideAtPos(c, r, DOWN, true);
				}
				else if (move_direction == DOWN) {

					(*grid).toggleCellSideAtPos(c, r, DOWN, true);
					++r;
					(*grid).toggleCellSideAtPos(c, r, UP, true);
				}
				else if (move_direction == LEFT) {

					(*grid).toggleCellSideAtPos(c, r, LEFT, true);
					--c;
					(*grid).toggleCellSideAtPos(c, r, RIGHT, true);
				}
				else if (move_direction == RIGHT) {
					(*grid).toggleCellSideAtPos(c, r, RIGHT, true);
					++c;
					(*grid).toggleCellSideAtPos(c, r, LEFT, true);
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

};

