// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

/**
 * 
 */

using namespace std;

enum DIRECTIONS { Dir_UP = 0, Dir_DOWN = 1, Dir_LEFT = 2, Dir_RIGHT = 3 };

class Cell
{
private:
	char cell_structure[5][5];

	int pos_x; 
	int pos_y;

public:

	bool _visited = false;
	bool opened_sides[4];

	Cell(int _x, int _y);
	Cell();
	
	void rebuild();

	void toggleSide(int side, bool state); // true: wall, false: no wall
	void updateSides();

	char getCharAtPos(int _x, int _y);
	
	void setCellStructure(char* structure);
	char* getCellStructure();

	vector<char> getCellRow(int row);

	void drawCell();
};
