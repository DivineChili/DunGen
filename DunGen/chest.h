#pragma once
#include "subcell.h"
#include "Item.h"
#include "randomizer.h"

class Chest : public SubCell {
private:
	uint32_t lootSeed;
	Randomizer lootRandomizer;
public:
	//All existing chests
	static vector<Chest*> chests;
	//Items in chest
	vector<Item*> items;

	Chest(uint32_t lootSeed, int posX, int posY);
	
	virtual ~Chest();
};

