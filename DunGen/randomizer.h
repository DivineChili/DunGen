#pragma once
#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "stdafx.h"
#include "xxHash32.h"
#include <iostream>

using namespace std;

class Randomizer {
private:
	uint32_t seed;
	XXHash32 hash;
	uint32_t result;
public:
	Randomizer::Randomizer(uint32_t seed); //initialize with seed
	Randomizer::~Randomizer();
	uint32_t Randomizer::randomizeAtPos(uint32_t x, uint32_t y); //Returns a random number for the specified position
	uint32_t Randomizer::randomizeFromKey(uint32_t key);
	bool Randomizer::randomizeFromChance(int chance, uint32_t key);
	uint32_t Randomizer::randomizeInRange(uint32_t min, uint32_t max, uint32_t key);
	void Randomizer::setSeed(uint32_t seed);
	uint32_t Randomizer::getSeed();
	void Randomizer::updateSeed();
};

#endif // !RANDOMIZER_H