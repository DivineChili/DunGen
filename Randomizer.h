// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "xxHash32.h"
#include <iostream>

/**
 * 
 */

class DUNGEN_API Randomizer {
private:
	uint32_t seed;
	XXHash32 hash;
	uint32_t result;
public:
	Randomizer(uint32_t seed); //initialize with seed
	~Randomizer();
	uint32_t randomizeAtPos(uint32_t x, uint32_t y); //Returns a random number for the specified position
	uint32_t randomizeFromKey(uint32_t key);
	bool randomizeFromChance(uint32_t chance, uint32_t key);
	uint32_t randomizeInRange(uint32_t min, uint32_t max, uint32_t key);
	void setSeed(uint32_t seed);
	uint32_t getSeed();
	void updateSeed();
};

