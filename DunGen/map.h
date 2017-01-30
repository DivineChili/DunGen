#pragma once
#ifndef MAP_H
#define MAP_H

#include "stdafx.h"
#include "cell.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Map {
private:
	unsigned int size_x, size_y; //Declaration for the size of the map
	vector< vector<Cell>> map_grid; //The map itself
	
public:
	static vector<Cell*> dead_ends;
	
	Map(unsigned int sizeX, unsigned int sizeY);
	~Map();

	// Returns the cell at xy-coordinates
	Cell* getCellAtPos(int x, int y);
	Cell* getCellAtPos(pair<int, int> pos);

	// Draws the cell at a specific xy-coordinate
	void drawCellAtPos(int x, int y);

	// Draws the entire map.
	void drawMap();

	void drawSubCellMap();

	// Writes the enitre map to .txt file
	void outputMap(string filename);

	//Returns the size of the map
	pair<int, int> getSize();
};

#endif // !MAP_H
