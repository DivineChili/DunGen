#pragma once
#include "item.h"
class Item_food : public Item {
protected:
	int foodValue;
	Item_food(int amount, int foodValue);
	void eat();
public:
	virtual ~Item_food();
};

