#include "stdafx.h"
#include "cell.h"
#include "map.h"

using namespace std;

void recursive_backtracking(int * start_pos, Map * grid) {
	// Create vector for recursive-backtracking history.
	bool running = true;
	vector<pair<int, int>> history;
	int c = start_pos[0];
	int r = start_pos[1];

	history.push_back({ start_pos[0], start_pos[1] }); // Start at the startingposistion
	(*grid).setCellStructureAtPos(start_pos[0], start_pos[1], "---------");

	// Recursive backtracing starts here!
	while (running) {

		(*grid).visitCell(c, r);
		cout << "Visited: [" << c << "][" << r << "]   \t|| ";

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
		cout << "Avalable options:" << check.size() << "   \t|| ";
		if (check.size() > 0) {

			history.push_back({ c , r });
			int move_direction = check[rand() % check.size()];	 // Randomly pick a cell! For use of hash-functions, put stuff here!

			cout << "Moving:  " << move_direction << "   !!!";
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

int main()
{
	int size_x = 38;	   // Size of map's width. (Multiply by 3 to get width in chars!)
	int size_y = 20;	   // Size of map's height. (Multiply by 3 to get height in chars!)
						   // Recommended X-size = 38
	Map grid = Map(size_x, size_y);
	// [0] = x; [1] = y
	int start_pos[2] = { 2,2 }; // Start backtracking from cell [0,3]

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
	grid.drawMap();
	cout << endl;

	return 0;
}