#include "stdafx.h"
#include "randomizer.h"
#include "xxHash32.h"
#include <iostream>

using namespace std;

Randomizer::Randomizer(uint32_t seed): hash(seed) {
	this->seed = seed;
}
Randomizer::~Randomizer() {
	cout << "Destroying randomizer!" << endl;
	cout << "seed: " << this->seed << endl;
}
uint32_t Randomizer::randomizeAtPos(uint32_t x, uint32_t y) {
	this->hash.add(&x, 4);
	this->hash.add(&y, 4);
	this->result = this->hash.hash();
	this->updateSeed(); //used to undo add()
	return this->result;
}
//Used for the global randomizer only
uint32_t Randomizer::randomizeFromKey(uint32_t key){
	this->hash.add(&key, 4);
	this->result = this->hash.hash();
	this->updateSeed(); //used to undo add()
	return this->result;
}
void Randomizer::setSeed(uint32_t seed) {
	this->seed = seed;
	this->updateSeed();
}
uint32_t Randomizer::getSeed() {
	return this->seed;
}
void Randomizer::updateSeed() {
	this->hash = XXHash32(this->seed);
}
