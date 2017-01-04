#pragma once
#include "room.h"
class Default_room : public Room
{
public:
	Default_room(uint32_t seed, Map* map, int key);
	~Default_room();
	virtual void printType();
};

