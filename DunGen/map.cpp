#include "stdafx.h"
#include "map.h"
#include <string>
#include <iostream>																										   
#include <vector>

using namespace std;

// Just a constructor
Map::Map(unsigned int sizeX, unsigned int sizeY) {
	this->size_x = sizeX; this->size_y = sizeY;	  // Set the private fields size_x and size_y to the sepsified parameters.
	this->map_grid = vector< vector<Cell>>(this->size_y, vector<Cell>(this->size_x));   // Initialize the map_grid with 
											    //2. dimensional vectors containing cell-objects
	for (int i = 0; i < this->map_grid.size(); i++) // Loop through the first vector
	{
		vector<Cell>::iterator it = this->map_grid[i].begin(); // Create an iterator to loop through second vector
		for (; it < this->map_grid[i].end(); ++it) 	// Loop through iterator
		{
			*it = Cell(); // Set the iterator's referenced value to a new cell-object
			//it->setFloorChar('-');
			//it->setWallChar('#');
		}
	}
}
Map::~Map() { cout << "Deleting map!" << endl; }	// Just a destructor

													// Returns the cell at a spesified position in the map. (X and Y values)
Cell Map::getCellAtPos(int x, int y)
{
	return this->map_grid.at(y).at(x);	// Using .at() instead of Operator[] to throw exceptions and bypass errors!
}

// Draws an induvidual cell at a spesific point in the grid
void Map::drawCellAtPos(int x, int y) {
	this->map_grid.at(y).at(x).drawCell();	// Draws the cell at a posistion in the map_grid.
}

// Simply draws the hole map and all of it's cell-data to the terminal
void Map::drawMap() {
	int mapX, mapY, cellRow = 0;  // Initialize the loop-counters. Optional!
	for (mapY = 0; mapY < this->size_y; mapY++) {   // Loop through map_grid rows
													// cout << "Map Y: " << mapY << endl;	 // For debugging 
		for (cellRow = 0; cellRow < 3; cellRow++) {   // Loop through the cellRows within each map_grid.
			for (mapX = 0; mapX < this->size_x; mapX++) {   // Loop through the colums in the map_grid
				vector<char> temp_char = this->map_grid[mapY][mapX].getCellRow(cellRow); // Get the char_vector of the first row in cell
				vector<char>::iterator it = temp_char.begin();	// Create iterator pointer at the begining of vector
				for (; it < temp_char.end(); ++it)	// Loop through vector using the iterator
				{
					cout << *it; // Print out the value of the iterator
				}
				cout << "";  // Used for debug-purposes!
			}
			cout << endl; // Newline for new cellrow
		}
		cout << "";
	}
}

void Map::drawSubCellMap() {
	//this->map_grid[0][0].drawSubCellRow(5);
	for (int i = 0; i < this->size_y; i++) { //map y
		for (int j = 0; j < 5; j++){ //subcell row number
			for (int k = 0; k < this->size_x - 1; k++) { //map x
				this->map_grid[k][i].drawSubCellRow(j);
				cout << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void Map::outputMap(string filename) {
	ofstream outfile;

	outfile.open(filename + ".txt", std::ios_base::app);
	
	int mapX, mapY, cellRow = 0;  // Initialize the loop-counters. Optional!
	for (mapY = 0; mapY < this->size_y; mapY++) {   // Loop through map_grid rows
													// cout << "Map Y: " << mapY << endl;	 // For debugging 
		for (cellRow = 0; cellRow < 3; cellRow++) {   // Loop through the cellRows within each map_grid.
			for (mapX = 0; mapX < this->size_x; mapX++) {   // Loop through the colums in the map_grid
				vector<char> temp_char = this->map_grid[mapY][mapX].getCellRow(cellRow); // Get the char_vector of the first row in cell
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

// Cell-change functions
void Map::setCellStructureAtPos(int x, int y, string newCellStruct) {
	this->map_grid[y][x].setCellStructure(newCellStruct);
}

void Map::toggleCellSideAtPos(int x, int y, int side, bool state) {
	this->map_grid[y][x].toggleSide(side, state);
}

// Marks cell to be visited.
void Map::visitCell(int x, int y) {
	this->map_grid[y][x].setVisited(true);
}

// Checks if the cell is visited.
bool Map::cellVisited(int x, int y) {
	return this->map_grid.at(y).at(x)._visited;   // Using .at() insted of Operator[] to throw exceptions needed to bypass errors!
}

vector<int> Map::getCellopeningsAtPos(int x, int y)
{
	return this->map_grid[y][x].sides_opened();
}


// Returns the x,y size of map
pair<int,int> Map::getSize() {
	return{ this->size_x, this->size_y };
}
