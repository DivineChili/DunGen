// Fill out your copyright notice in the Description page of Project Settings.

#include "DunGen.h"
#include "Cell.h"
#include <iostream>

Cell::Cell()
{
	// Construct top
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			if (x == 0 || x == 4 || y == 0 || y == 4) {
				this->cell_structure[x][y] = '#';
			}
			else {
				this->cell_structure[x][y] = ' ';
			}
		}
	}

	this->opened_sides[0] = true;
	this->opened_sides[1] = true;
	this->opened_sides[2] = true;
	this->opened_sides[3] = true;
}

Cell::Cell(int _x, int _y)
{
	this->pos_x = _x;
	this->pos_y = _y;

	// Construct top
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			if (x == 0 || x == 4 || y == 0 || y == 4) {
				this->cell_structure[x][y] = '#';
			}
			else {
				this->cell_structure[x][y] = ' ';
			}
		}
	}

	this->opened_sides[0] = true;
	this->opened_sides[1] = true;
	this->opened_sides[2] = true;
	this->opened_sides[3] = true;
}

void Cell::rebuild() {
	
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			if (x == 0 || x == 4 || y == 0 || y == 4) {
				this->cell_structure[x][y] = '#';
			}
			else {
				this->cell_structure[x][y] = ' ';
			}
		}
	}

	this->opened_sides[0] = true;
	this->opened_sides[1] = true;
	this->opened_sides[2] = true;
	this->opened_sides[3] = true;
}

void Cell::toggleSide(int side, bool state /*true is wall, false is floor*/) {
	switch (side) {
	case(Dir_UP):
		this->opened_sides[Dir_UP] = state;
		break;
	case(Dir_DOWN):
		this->opened_sides[Dir_DOWN] = state;
		break;
	case(Dir_LEFT):
		this->opened_sides[Dir_LEFT] = state;
		break;
	case(Dir_RIGHT):
		this->opened_sides[Dir_RIGHT] = state;
		break;
	}
	this->updateSides();
}

void Cell::updateSides() {
	for (int i = 0; i < sizeof(this->opened_sides); i++) {
		switch (i) {
		case 0:
			if (this->opened_sides[Dir_UP]) {
				this->cell_structure[1][0] = '#';
				this->cell_structure[2][0] = '#';
				this->cell_structure[3][0] = '#';
			}
			else {
				this->cell_structure[1][0] = ' ';
				this->cell_structure[2][0] = ' ';
				this->cell_structure[3][0] = ' ';
			}
			break;
		case 1:
			if (this->opened_sides[Dir_DOWN]) {
				this->cell_structure[1][4] = '#';
				this->cell_structure[2][4] = '#';
				this->cell_structure[3][4] = '#';
			}
			else {
				this->cell_structure[1][4] = ' ';
				this->cell_structure[2][4] = ' ';
				this->cell_structure[3][4] = ' ';
			}
			break;
		case 2:
			if (this->opened_sides[Dir_LEFT]) {
				this->cell_structure[0][1] = '#';
				this->cell_structure[0][2] = '#';
				this->cell_structure[0][3] = '#';
			}
			else {
				this->cell_structure[0][1] = ' ';
				this->cell_structure[0][2] = ' ';
				this->cell_structure[0][3] = ' ';
			}
			break;
		case 3:
			if (this->opened_sides[Dir_RIGHT]) {
				this->cell_structure[4][1] = '#';
				this->cell_structure[4][2] = '#';
				this->cell_structure[4][3] = '#';
			}
			else {
				this->cell_structure[4][1] = ' ';
				this->cell_structure[4][2] = ' ';
				this->cell_structure[4][3] = ' ';
			}
			break;
		}
	}
}

char Cell::getCharAtPos(int _x, int _y) {
	return this->cell_structure[_x][_y];
}

void Cell::setCellStructure(char* structure) {
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			this->cell_structure[x][y] = *structure;
		}
	}

}

char* Cell::getCellStructure() {
	return *this->cell_structure;
}

vector<char> Cell::getCellRow(int row) {
	vector<char> result(5);
	
	for (int i = 0; i < 5; i++) {
		result[i] = this->cell_structure[row][i];
	}
	
	return result;
}

void Cell::drawCell()
{
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			std::cout << this->cell_structure[x][y];
		}
		std::cout << std::endl;
	}
}
