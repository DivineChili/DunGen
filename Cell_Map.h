// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "Cell.h"
/**
 * 
 */

using namespace std;

class Cell_Map
{
private:
	int size_x, size_y;
	vector< vector<Cell>> grid;
public:
	Cell_Map(int sizeX, int sizeY);
	Cell_Map();
	~Cell_Map();

	Cell* getCellAtPos(int x, int y);
	void outputMap(string filename);
};
