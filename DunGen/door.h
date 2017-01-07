#pragma once
#include "subcell.h"
#include <vector>

class Door : public SubCell {
public:
	static vector<Door*> doors;
	Door(int posX, int posY);
	virtual ~Door();
};

