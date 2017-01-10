// MapAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cell.h"
#include <string>
#include <iostream>																										   
#include <vector>
#include "door.h"

using namespace std;


// Initializes the cell and builds the base structure!
Cell::Cell(pair<int,int> pos) : subCell_grid(vector< vector<SubCell*>>(5, vector<SubCell*>(5))){

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			this->subCell_grid[j][i] = new SubCell(j, i);
		}
	}

	int i = 0;

	// Create upper row (y=0)
	for (i = 0; i < 3; i++) {
		if (i == 0 || i == 2) this->cell_struct += this->corner;
		else this->cell_struct += this->wall;
	}

	// Create middlerow (y=1)
	for (i = 0; i < 3; i++) {
		if (i == 1 && this->_visited) this->cell_struct += this->block;
		else this->cell_struct += this->wall;
	}

	// Create bottom row
	for (i = 0; i < 3; i++) {
		if (i == 0 || i == 2) this->cell_struct += this->corner;
		else this->cell_struct += this->wall;
	}

	this->opened_sides[0] = false;
	this->opened_sides[1] = false;
	this->opened_sides[2] = false;
	this->opened_sides[3] = false;
	
	this->position = pos;
}

// Rebuilds the cell. NB! All changes done to the cell will be lost!
void Cell::rebuild() {
	this->cell_struct = "";
	int i = 0;

	// Create upper row (y=0)
	for (i = 0; i < 3; i++) {
		if (i == 1 || i == 2) this->cell_struct += this->corner;
		else this->cell_struct += this->wall;
	}

	// Create middlerow (y=1)
	for (i = 0; i < 3; i++) {
		if (i == 1) this->cell_struct += this->block;
		else this->cell_struct += this->wall;
	}

	// Create bottom row
	for (i = 0; i < 3; i++) {
		if (i == 0 || i == 2) this->cell_struct += this->corner;
		else this->cell_struct += this->wall;
	}

	this->opened_sides[0] = false;
	this->opened_sides[1] = false;
	this->opened_sides[2] = false;
	this->opened_sides[3] = false;
}

// Toggles one of the sides of the cell. Changes are lost if cell is rebuilt!
void Cell::toggleSide(int side, bool state /*true is floor, false is wall*/) {
	switch (side)
	{
	case(UP):
		if (state) { this->cell_struct[1] = this->floor;}
		else { this->cell_struct[1] = this->wall; }
		this->opened_sides[UP] = state;
		break;
	case(DOWN):
		if (state) { this->cell_struct[7] = this->floor; }
		else { this->cell_struct[7] = this->wall; }
		this->opened_sides[DOWN] = state;
		break;
	case(LEFT):
		if (state) { this->cell_struct[3] = this->floor; }
		else { this->cell_struct[3] = this->wall; }
		this->opened_sides[LEFT] = state;
		break;
	case(RIGHT):
		if (state) { this->cell_struct[5] = this->floor; }
		else { this->cell_struct[5] = this->wall; }
		this->opened_sides[RIGHT] = state;
		break;
	}
}

// Gets the char at a specific position in the cell
char Cell::getCharAtPos(int x, int y) {
	return this->cell_struct[(y * 3) + x];
}



void Cell::setVisited(bool state) { this->_visited = state; this->cell_struct[4] = this->floor; }

// Dangerous function! Use at own risk!
void Cell::setCellStructure(string structure) {
	int i = 0;
	for (char c : structure) {
		if (c != '/') { // If replaced by slash, do not replace.
			this->cell_struct[i] = c;
		}
		i++;
	}
}


// Returns the structe of the cell reperisented in a string
string Cell::getCellStruct() { return this->cell_struct; }

void Cell::drawSubCellRow(int row) {
	for (int i = 0; i < 5; i++) {
		cout << this->subCell_grid[i][row]->getChar();
	}
}

void Cell::setSubCellAtPos(SubCell* subCell) {
	if (subCell->getChar() == 'D') {
		cout << "door" << endl;
		for (int i = 0; i < this->subCell_grid[0].size(); i++) {
			for (int j = 0; j < this->subCell_grid.size(); j++) {
				cout << this->subCell_grid[j][i]->getChar();
			}
			cout << endl;
		}
	}
	this->subCell_grid[subCell->posX][subCell->posY] = subCell;
}

// Gets a vector of all the chars in a row
vector<char> Cell::getCellRow(int rowIndex)
{
	vector<char> result(3);
	for (int i = 0; i < 3; i++) {
		result[i] = this->cell_struct[(rowIndex * 3) + i];
	}

	return result;
}

vector<int> Cell::sides_opened()
{
	vector<int> opened_sides;
	for (int i = 0; i < sizeof(this->opened_sides); i++) {
		if (this->opened_sides[i])
			opened_sides[i] = i;
	}
	return opened_sides;
}

// Draws the cell induvidually
void Cell::drawCell(){
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			cout << this->cell_struct[(3 * y) + x];
		}
		cout << endl;
	}
}

