// Fill out your copyright notice in the Description page of Project Settings.

#include "DunGen.h"
#include "Algorithms.h"

#include <iostream>
#include <vector>

#include "Cell.h"
#include "Cell_Map.h"
#include "Randomizer.h"

Algorithms::Algorithms()
{
}

void Algorithms::recursive_backtracking(int * start_pos, Cell_Map * grid, Randomizer MazeRandomizer) {
	using namespace std;
	// Create vector for recursive-backtracking history.
	bool running = true;
	vector<pair<int, int>> history;
	int c = start_pos[0];
	int r = start_pos[1];

	history.push_back({ start_pos[0], start_pos[1] }); // Start at the startingposistion

													   // Recursive backtracing starts here!
	while (running) {

		//grid->drawMap();
		//grid->drawSubCellMap();
		(*grid).getCellAtPos(c, r)->_visited = true;
		cout << "Visited: [" << c << "][" << r << "]   \t|| ";

		vector<int> check;

		// Check blocks!
		// Check Right
		try {
			if (!(*grid).getCellAtPos(c + 1, r)->_visited) {
				check.push_back(Dir_RIGHT);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Check Left
		try {
			if (!(*grid).getCellAtPos(c - 1, r)->_visited) {
				check.push_back(Dir_LEFT);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Check Up
		try {
			if (!(*grid).getCellAtPos(c, r - 1)->_visited) {
				check.push_back(Dir_UP);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Check Down
		try {
			if (!(*grid).getCellAtPos(c, r + 1)->_visited) {
				check.push_back(Dir_DOWN);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Choose one of the options!
		cout << "Avalable options:" << check.size() << "   \t|| ";
		if (check.size() > 0) {

			history.push_back({ c , r });
			//uint32_t mazeHash = XXHash32::hash(mazeKey_p, 4, mazeSeed);
			//mazeKey++;
			//cout << mazeKey << endl;
			//cout << mazeHash << endl;
			uint32_t result = MazeRandomizer.randomizeAtPos(c, r);

			int move_direction = check[result % check.size()];

			cout << "Moving:  " << move_direction << "   !!!";
			if (move_direction == Dir_UP) {
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_UP, false);
				--r;
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_DOWN, false);
			}
			else if (move_direction == Dir_DOWN) {
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_DOWN, false);
				++r;
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_UP, false);
			}
			else if (move_direction == Dir_LEFT) {
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_LEFT, false);
				--c;
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_RIGHT, false);
			}
			else if (move_direction == Dir_RIGHT) {
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_RIGHT, false);
				++c;
				(*grid).getCellAtPos(c, r)->toggleSide(Dir_LEFT, false);
			}
		}
		else {
			if (history.size() > 1) {
				cout << "Backtracking !!!";
				history.pop_back();
				c = history.back().first;
				r = history.back().second;
			}
			else {
				cout << "\nDONE!" << endl;
				running = false;
			}
		}
		cout << endl;
	}

}

Algorithms::~Algorithms()
{
}
