#include "stdafx.h"
#include "randomizer.h"
#include "chest.h"

vector<Chest*> Chest::chests;

Chest::Chest(uint32_t lootSeed, int posX, int posY) :
	SubCell(posX, posY),
	lootSeed(lootSeed),
	lootRandomizer(lootSeed){

	this->type = 'c';
	
	this->chests.push_back(this);
}


Chest::~Chest() {

}
