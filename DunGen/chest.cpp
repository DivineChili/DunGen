#include "stdafx.h"
#include "randomizer.h"
#include "chest.h"


Chest::Chest(uint32_t lootSeed, int posX, int posY) :
	SubCell(posX, posY),
	lootSeed(lootSeed),
	lootRandomizer(lootSeed){

	this->type = 'c';

	
}


Chest::~Chest() {

}
