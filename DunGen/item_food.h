#pragma once
#include "item.h"
class Item_food : public Item {
protected:
	int foodValue;
	Item_food(int foodValue);
	void Item_food::eat();
public:
	virtual ~Item_food();
};

