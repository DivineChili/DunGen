#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include <vector>
#include "stdafx.h"
#include "cell.h"
#include "chest.h"
#include "item.h"
#include "item_gold.h"
#include "item_food.h"
#include "food_apple.h"
#include "map.h"
#include "randomizer.h"

class Algorithms {
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

			//grid->drawMap();
			//grid->drawSubCellMap();
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
				if (move_direction == UP) {
					(*grid).getCellAtPos(c, r)->toggleSide(UP, true);
					--r;
					(*grid).getCellAtPos(c, r)->toggleSide(DOWN, true);
				}
				else if (move_direction == DOWN) {
					(*grid).getCellAtPos(c, r)->toggleSide(DOWN, true);
					++r;
					(*grid).getCellAtPos(c, r)->toggleSide(UP, true);
				}
				else if (move_direction == LEFT) {
					(*grid).getCellAtPos(c, r)->toggleSide(LEFT, true);
					--c;
					(*grid).getCellAtPos(c, r)->toggleSide(RIGHT, true);
				}
				else if (move_direction == RIGHT) {
					(*grid).getCellAtPos(c, r)->toggleSide(RIGHT, true);
					++c;
					(*grid).getCellAtPos(c, r)->toggleSide(LEFT, true);
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

		for (int i = 0; i < iterations; i++) { // The removing iterations
			
			for (int j = 0; j < local_ends.size(); j++) { // Each dead end
				Cell* current_end = local_ends.at(j);
				if (current_end->sides_opened().size() == 1) { // Check if only one side is opened. Usefull for iterations > 1
					current_end->setCellStructure(string(9, ' '));

					// Check if ajasent cell is dead end aswell!
					switch (current_end->sides_opened().at(0)) {
					case(UP):
						
						break;
					case(DOWN):

						break;
					case(LEFT):

						break;
					case(RIGHT):

						break;
					}

				}
			}
		}
	}

	static void lootSpawner(Map* map, vector<Chest*> chests, Randomizer lootRandomizer){
		for (int i = 0; i < chests.size(); i++) {
			//cout << chests[i]->getChar() << endl;
			if (lootRandomizer.randomizeFromChance(50, (uint32_t) i)){ // 50 percent chance of having gold.
				int amount = floor(pow(lootRandomizer.randomizeInRange(1, 100, (uint32_t) i + 100), 2.5) * .001 + 3);
				chests[i]->items.push_back(new Item_gold(amount));
				//Print amount of gold.
				cout << "gold" << chests[i]->items[0]->amount << endl;
			}
			if (lootRandomizer.randomizeFromChance(60, (uint32_t)i + 1000)) {
				int amount = lootRandomizer.randomizeInRange(1, 4, i + 1100);
				chests[i]->items.push_back(new Food_apple(amount));
				cout << "apples" << amount << endl;
			}
			int randomIndex = lootRandomizer.randomizeInRange(0, chests.size() - 1, i + 10000);
			cout << "index: " << randomIndex << endl;
			//if (chests[i]->items[randomIndex]) {
				//Item* loot = chests[i]->items[randomIndex];
				//chests[i]->items[randomIndex] = chests[i]->items[chests[i]->items.size() - 1];
				//chests[i]->items[chests[i]->items.size() - 1] = loot;
			//}
		}
	}
};

#endif // !ALGORITHMS_H
