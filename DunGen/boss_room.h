#pragma once
#include "room.h"
class Boss_room :
	public Room
{
public:
	Boss_room(uint32_t seed, Map* map, int key);
	~Boss_room();
	virtual void printType();
};

