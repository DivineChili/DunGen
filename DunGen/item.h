#pragma once
#include <iostream>

class Item {
public:
	int value;
	int amount;
	Item(int amount);
	Item();
	void drop();
	~Item();
};

