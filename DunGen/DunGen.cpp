#include "stdafx.h"
#include "DunGen.h"
#include "cell.h"
#include "map.h"
#include "room.h"
#include "room_loot.h"
#include "randomizer.h"
#include "xxHash32.h"
#include <cmath>

using namespace std;

//Randomizer for generating seeds
uint32_t globalSeed = 655863;
Randomizer globalRandomizer(globalSeed);

//Randomizer for the maze generation
uint32_t mazeSeed = globalRandomizer.randomizeFromKey(0);
Randomizer mazeRandomizer(mazeSeed);

uint32_t roomSeed = globalRandomizer.randomizeFromKey(1);
Randomizer roomRandomizer(roomSeed);

void recursive_backtracking(int * start_pos, Map * grid) {
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

int main()
{
	int size_x = 30;	   // Size of map's width. (Multiply by 3 to get width in chars!)
	int size_y = 100;	   // Size of map's height. (Multiply by 3 to get height in chars!)
						   // Recommended X-size for teminal is 38, for output to .txt opened in notepad 341!

	cout << "This map size (" << size_x << "x" << size_y << "), will be: " << (48 * (size_x*size_y))/1024 << " KB!" << endl;
	cout << "Are you sure you wish to continue (Y/n)?";
	string input;
	cin >> input;
	if (input[0] == 'n' || input[0] == 'N') exit(1);
	Map grid = Map(size_x, size_y);

	// [0] = x; [1] = y
	int start_pos[2] = { 2,2 }; // Start backtracking from cell at this xy-coordinate
	grid.setCellStructureAtPos(start_pos[0], start_pos[1], "---------");
	grid.visitCell(start_pos[0], start_pos[1]);

	// Generate rooms
	int key = 0;
	do {
		//Room::rooms.push_back(new Room(roomRandomizer.randomizeFromKey(Room::rooms.size()), 4, 4, &grid, key));
		cout << endl << endl << endl;
		//switch (roomRandomizer.randomizeFromChance(100, 0)) {
		//case(1):
		//}
		new Room_loot(roomRandomizer.randomizeFromKey(Room::rooms.size()), &grid, key, 4, 4);//Uses the new keyword, so the room does not get deleted instantly.
		Room::rooms[Room::rooms.size() - 1]->printType();
		cout << Room::rooms[Room::rooms.size() - 1]->isOverlapping() << endl;
		//cout << Room::rooms[Room::rooms.size() - 1]->overlap << endl;
		if (!Room::rooms[Room::rooms.size() - 1]->isOverlapping()) {
			Room::rooms[Room::rooms.size() - 1]->build();
		} else {
			Room::rooms[Room::rooms.size() - 1]->~Room(); //Delete the room.
			Room::rooms.pop_back(); //Remove last element of vector.
			key += 4; //Increment the room by 4 so the size of the room and position of the room are generated with new values.
			continue;
		}
		cout << "	Amount of rooms: " << Room::rooms.size() << endl;
	} while (Room::rooms.size() < (size_x*size_y) / 30);

	

	//vector<Room*>::iterator it = Room::rooms.begin();
	//for (; it < Room::rooms.end(); it++) {
	//	cout << "Deleting: " << (*it). << endl;
	//	delete(*it);
	//}

	cout << "Rooms generated: " << Room::rooms.size() << endl;
	
	recursive_backtracking(start_pos, &grid);
	
	/* // Cell Debug!
	Cell newCell = Cell();
	cout << "Pure Cell:\n";
	newCell.drawCell();
	cout << "Rebuilt visited cell:\n";
	newCell.setVisited(true);
	newCell.rebuild();
	newCell.drawCell();
	cout << "Opened top and bottom cell:\n";
	newCell.toggleSide(UP, true);
	newCell.toggleSide(DOWN, true);
	newCell.drawCell();
	cout << "Rebuilt cell:\n";
	newCell.rebuild();
	newCell.drawCell();
	*/
	cout << endl;
	cout << "Global seed: " << globalSeed << endl;
	cout << "Maze seed: " << mazeSeed << endl;
	cout << "Room seed: " << roomSeed << endl;


	grid.drawMap();

	for (int i = Room::rooms.size() - 1; i > 0; i--) {
		//cout << Room::rooms.size() << endl;
		Room::rooms[i]->~Room();
		Room::rooms.pop_back();
	}

	return 0;
}