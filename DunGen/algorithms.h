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
	static vector<Cell*> dead_ends;

	static void recursive_backtracking(int * start_pos, Map * grid, Randomizer mazeRandomizer, int deadend_logging_chance) {
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

			(*grid).getCellAtPos(c, r)->setVisited(true);
			//cout << "Visited: [" << c << "][" << r << "]   \t|| ";

			vector<int> check;

			// Check blocks!
			// Check Right
			try {
				if (!(*grid).getCellAtPos(c + 1, r)->_visited) {
					check.push_back(RIGHT);
				}
			}
			catch (const out_of_range& e) { e.what(); }

			// Check Left
			try {
				if (!(*grid).getCellAtPos(c - 1, r)->_visited) {
					check.push_back(LEFT);
				}
			}
			catch (const out_of_range& e) { e.what(); }

			// Check Up
			try {
				if (!(*grid).getCellAtPos(c, r - 1)->_visited) {
					check.push_back(UP);
				}
			}
			catch (const out_of_range& e) { e.what(); }

			// Check Down
			try {
				if (!(*grid).getCellAtPos(c, r + 1)->_visited) {
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

				int move_direction = check[static_cast<int>(result) % check.size()];

				//cout << "Moving:  " << move_direction << "   !!!";
				if (move_direction == UP)
				{
					(*grid).getCellAtPos(c,r)->toggleSide(UP, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(UP, true);
					--r;
					(*grid).getCellAtPos(c, r)->toggleSide(DOWN, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(DOWN, true);
				}
				else if (move_direction == DOWN) {

					(*grid).getCellAtPos(c, r)->toggleSide(DOWN, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(DOWN, true);
					++r;
					(*grid).getCellAtPos(c, r)->toggleSide(UP, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(UP, true);
				}
				else if (move_direction == LEFT) {

					(*grid).getCellAtPos(c, r)->toggleSide(LEFT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(LEFT, true);
					--c;
					(*grid).getCellAtPos(c, r)->toggleSide(RIGHT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(RIGHT, true);
				}
				else if (move_direction == RIGHT) {
					(*grid).getCellAtPos(c, r)->toggleSide(RIGHT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(RIGHT, true);
					++c;
					(*grid).getCellAtPos(c, r)->toggleSide(LEFT, true);
					(*grid).getCellAtPos(c, r)->toggleSubCellSide(LEFT, true);
				}
			}
			else {
				if (history.size() > 1) {
					//cout << "Backtracking !!!";
					if(mazeRandomizer.randomizeFromChance(deadend_logging_chance, mazeRandomizer.randomizeAtPos(c,r)) == 1)
						grid->dead_ends.push_back(grid->getCellAtPos(c, r));
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

	static void deadend_remover(Map * grid, vector<Cell*> dead_ends, int iterations) {
		vector<Cell*> local_ends = dead_ends;
		vector<Cell*> temp_ends;
		for (int i = 0; i < iterations; i++) {

		}
	}
};

#endif // !ALGORITHMS_H