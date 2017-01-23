#pragma once
#include "subcell.h"
#include "randomizer.h"

class Chest : public SubCell {
private:
	uint32_t lootSeed;
	Randomizer lootRandomizer;
public:
	Chest(uint32_t lootSeed, int posX, int posY);
	
	virtual ~Chest();
};

