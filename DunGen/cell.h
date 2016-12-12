#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum DIRECTIONS { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 }; // Used to reference the different directions reperesented by integers

class Cell {
private:
	string cell_struct = "";
	char wall = '-';
	char floor = '-';
public:
	Cell::Cell();
	void Cell::rebuild();
	void Cell::setWallChar(char newChar);
	void Cell::setFloorChar(char newChar);
	void Cell::toggleSide(int side, bool state);
	char Cell::getCharAtPos(int x, int y);
	// Used for generation algorithms. Used to determine if the cell has been visited or not.
	bool _visited = false;
	void Cell::setVisited(bool state);
	void Cell::setCellStructure(string structure);
	string Cell::getCellStruct();
	vector<char> Cell::getCellRow(int rowIndex);
	void Cell::drawCell();
};
