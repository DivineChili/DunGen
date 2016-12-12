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
	Cell Map::getCellAtPos(int x, int y);
	void Map::drawCellAtPos(int x, int y);
	void Map::drawMap();
	void Map::setCellStructureAtPos(int x, int y, string newCellStruct);
	void Map::toggleCellSideAtPos(int x, int y, int side, bool state);
	void Map::visitCell(int x, int y);
	bool Map::cellVisited(int x, int y);
};
