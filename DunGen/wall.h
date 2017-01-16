#pragma once
#include "subcell.h"

class Wall : public SubCell {
public:
	Wall(int posX, int posY);
	virtual ~Wall();
};

