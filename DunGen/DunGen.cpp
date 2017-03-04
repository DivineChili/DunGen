// Fill out your copyright notice in the Description page of Project Settings.

#include "DunGen.h"

#include <iostream>
#include <vector>

#include "Cell.h"
#include "Algorithms.h"
#include "Cell_Map.h"

int main() {
	int size_x = 50;
	int size_y = 50;

	Cell_Map grid = Cell_Map(size_x, size_y);

	// [0] = x; [1] = y
	int start_pos[2] = { 2,2 }; // Start backtracking from cell at this xy-coordinate
	char empty_space[5][5] = { { ' ',' ',' ', ' ', ' ' },{ ' ',' ',' ', ' ', ' ' },{ ' ',' ',' ', ' ', ' ' },{ ' ',' ',' ', ' ', ' ' },{ ' ',' ',' ', ' ', ' ' } };
	grid.getCellAtPos(start_pos[0], start_pos[1])->setCellStructure(*empty_space);
	grid.getCellAtPos(start_pos[0], start_pos[1])->_visited = true;

	grid.getCellAtPos(5, 5)->drawCell();

	grid.outputMap("No-Algorithm");

	Algorithms::recursive_backtracking(start_pos, &grid);

	grid.outputMap("Algorithm");
}