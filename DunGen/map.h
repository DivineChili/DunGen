#pragma once
#include "stdafx.h"
#include "cell.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Map {
private:
	unsigned int size_x, size_y; //Declaration for the size of the map
	vector< vector<Cell>> map_grid; //The map itself
public:
	Map::Map(unsigned int sizeX, unsigned int sizeY);
	Map::~Map();

	// Returns the cell at xy-coordinates
	Cell Map::getCellAtPos(int x, int y);

	// Draws the cell at a specific xy-coordinate
	void Map::drawCellAtPos(int x, int y);

	// Draws the entire map.
	void Map::drawMap();

	/* The following functions is used for generating algorithms and indirect methods of changing cells. */
	// Set cell-struct at a spesific position
	void Map::setCellStructureAtPos(int x, int y, string newCellStruct);
	// Toggles a specific side of cell. Indirect method of Cell::toggleSide()
	void Map::toggleCellSideAtPos(int x, int y, int side, bool state);
	// Sets the cell at [y][x] to be visited. Indirect method of Cell::setVisited(true)
	void Map::visitCell(int x, int y);
	// Returns the visited-state of cell at [y][x] coordinates.
	bool Map::cellVisited(int x, int y);
};
