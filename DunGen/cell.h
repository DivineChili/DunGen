#pragma once
#ifndef CELL_H
#define CELL_H

#include "stdafx.h"
#include "subcell.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Used to reference the different directions reperesented by integers
enum DIRECTIONS { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 }; 

class Cell {
private:
	string cell_struct = "";
	pair<int, int> position;
	bool opened_sides[4];
	int x;
	int y;
public:
	static const char wall = '#';
	static const char noWall = ',';
	static const char corner = '#';
	static const char noCorner = ',';
	static const char floor = '-';
	static const char block = '=';
	static const char door = '/';
	static const char empty = ' ';

	static const int gridSize = 5;

	vector<vector<SubCell*>> subCell_grid;
	//These are the subCells contained within one cell
	//vector<SubCell*> subCells;
	Cell::Cell(int x, int y);
	Cell::Cell();
	void Cell::rebuild();
	
	//Draws a row of subcells to the terminal.
	void Cell::drawSubCellRow(int row);

	void Cell::setSubCellAtPos(SubCell* subCell);
	
	void Cell::toggleSide(int side, bool state);

	void Cell::updateSubCellSides();

	void Cell::updateSides();
	
	char Cell::getCharAtPos(int x, int y);

	// Used for generation algorithms. Used to determine if the cell has been visited or not.
	bool _visited = false;
	void Cell::setVisited(bool state);
	
	// Sets the Cellstructure. Used to create rooms and other custom cells.
	void Cell::setCellStructure(string structure);
	
	// Returns the cell structure
	string Cell::getCellStruct();

	vector<char> Cell::getCellRow(int rowIndex);

	// Returns all opened sides. (Use Cell::Directions enum for side-references!)
	vector<int> sides_opened();
		
	// Independent function to draw cell
	void Cell::drawCell();

	void Cell::drawSubCell();
};

#endif // !CELL_H
