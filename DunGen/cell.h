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
	char wall   = '#';
	char noWall = ',';
	char corner = '#';
	char noCorner=',';
	char floor  = '-';
	char block  = '=';
	char door   = '/';
	// grid of subcells
	vector<vector<SubCell>> subCell_grid;
public:
	//These are the subCells contained within one cell
	//vector<SubCell*> subCells;
	Cell::Cell();
	void Cell::rebuild();
	
	//Draws a row of subcells to the terminal.
	void Cell::drawSubCellRow(int row);

	void Cell::setSubCellAtPos(SubCell* subCell);
	
	void Cell::toggleSide(int side, bool state);
	
	char Cell::getCharAtPos(int x, int y);

	// Used for generation algorithms. Used to determine if the cell has been visited or not.
	bool _visited = false;
	void Cell::setVisited(bool state);
	
	// Sets the Cellstructure. Used to create rooms and other custom cells.
	void Cell::setCellStructure(string structure);
	
	// Returns the cell structure
	string Cell::getCellStruct();


	vector<char> Cell::getCellRow(int rowIndex);
	
	// Independent function to draw cell
	void Cell::drawCell();
};

#endif // !CELL_H