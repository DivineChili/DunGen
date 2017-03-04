// Fill out your copyright notice in the Description page of Project Settings.

#include "DunGen.h"
#include "Cell_Map.h"
#include <iostream>
#include <fstream>

Cell_Map::Cell_Map(int sizeX, int sizeY)
{
	this->size_x = sizeX;
	this->size_y = sizeY;

	this->grid = vector<vector<Cell>>(this->size_x, vector<Cell>(this->size_y));

	for (int x = 0; x < this->grid.size(); x++)
	{
		for (int y = 0; y < this->grid.at(x).size(); y++)
		{
			this->grid[x][y] = Cell(x, y);
		}
	}
}

Cell_Map::~Cell_Map()
{
}

Cell* Cell_Map::getCellAtPos(int _x, int _y) {
	return &(this->grid.at(_x).at(_y));
}

void Cell_Map::outputMap(string filename) {
	using namespace std;

	ofstream outfile;

	outfile.open(filename + ".txt", std::ios_base::app);

	int mapX, mapY, cellRow = 0;  // Initialize the loop-counters. Optional!
	for (mapY = 0; mapY < this->size_y; mapY++) {   // Loop through map_grid rows
													// cout << "Map Y: " << mapY << endl;	 // For debugging 
		for (cellRow = 0; cellRow < 5; cellRow++) {   // Loop through the cellRows within each map_grid.
			for (mapX = 0; mapX < this->size_x; mapX++) {   // Loop through the colums in the map_grid
				vector<char> temp_char = this->grid[mapY][mapX].getCellRow(cellRow); // Get the char_vector of the first row in cell
				vector<char>::iterator it = temp_char.begin();	// Create iterator pointer at the begining of vector
				for (; it < temp_char.end(); ++it)	// Loop through vector using the iterator
				{
					outfile << *it; // Print out the value of the iterator
				}
				outfile << "";  // Used for debug-purposes!
			}
			outfile << endl; // Newline for new cellrow
		}
		outfile << ""; // Also used for debugging!
	}
}