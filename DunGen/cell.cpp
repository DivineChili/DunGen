// MapAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cell.h"
#include <string>
#include <iostream>																										   
#include <vector>

using namespace std;

// Initializes the cell and builds the base structure!
Cell::Cell() {
	int i = 0;

	// Create upper row (y=0)
	for (i = 0; i < 3; i++) {
		this->cell_struct += this->wall;
	}

	// Create middlerow (y=1)
	for (i = 0; i < 3; i++) {
		if (i == 1 && this->_visited) this->cell_struct += this->floor;
		else this->cell_struct += this->wall;
	}

	// Create bottom row
	for (i = 0; i < 3; i++) {
		this->cell_struct += this->wall;
	}
}

// Rebuilds the cell. NB! All changes done to the cell will be lost!
void Cell::rebuild() {
	this->cell_struct = "";
	int i = 0;

	// Create upper row (y=0)
	for (i = 0; i < 3; i++) {
		this->cell_struct += this->wall;
	}

	// Create middlerow (y=1)
	for (i = 0; i < 3; i++) {
		if (i == 1) this->cell_struct += this->floor;
		else this->cell_struct += this->wall;
	}

	// Create bottom row
	for (i = 0; i < 3; i++) {
		this->cell_struct += this->wall;
	}
}
// Sets the Wall-Char. NB! Rebuilds the cell! All changes done to the cell will be lost!
void Cell::setWallChar(char newChar){
	this->wall = newChar;
	rebuild();
}

// Sets the Floor-Char. NB! Rebuilds the cell! All changes done to the cell will be lost!
void Cell::setFloorChar(char newChar)
{
	this->floor = newChar;
	rebuild();
}

// Toggles one of the sides of the cell. Changes are lost if cell is rebuilt!
void Cell::toggleSide(int side, bool state /*true is floor, false is wall*/) {
	switch (side)
	{
	case(UP):
		if (state) { this->cell_struct[1] = this->floor; }
		else { this->cell_struct[1] = this->wall; }
		break;
	case(DOWN):
		if (state) { this->cell_struct[7] = this->floor; }
		else { this->cell_struct[7] = this->wall; }
		break;
	case(LEFT):
		if (state) { this->cell_struct[3] = this->floor; }
		else { this->cell_struct[3] = this->wall; }
		break;
	case(RIGHT):
		if (state) { this->cell_struct[5] = this->floor; }
		else { this->cell_struct[5] = this->wall; }
		break;
	}
}

// Gets the char at a specific position in the cell
char Cell::getCharAtPos(int x, int y) {
	return this->cell_struct[(y * 3) + x];
}



void Cell::setVisited(bool state) { this->_visited = state; this->cell_struct[4] = '-'; }

// Dangerous function! Use at own risk!
void Cell::setCellStructure(string structure) {
	this->cell_struct = structure;
}


// Returns the structe of the cell reperisented in a string
string Cell::getCellStruct() { return this->cell_struct; }

// Gets a vector of all the chars in a row
vector<char> Cell::getCellRow(int rowIndex)
{
	vector<char> result(3);
	for (int i = 0; i < 3; i++) {
		result[i] = this->cell_struct[(rowIndex * 3) + i];
	}

	return result;
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
