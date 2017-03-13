// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Cell_Map.h"
#include "Randomizer.h"

/**
 * 
 */
class Algorithms
{
public:
	static void recursive_backtracking(int * start_pos, Cell_Map * grid, Randomizer MazeRandomizer);

	Algorithms();
	~Algorithms();
};
