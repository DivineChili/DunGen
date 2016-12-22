#pragma once
#ifndef ROOM_LOOT_H
#define ROOM_LOOT_H

#include "room.h"

class Room_loot : public Room {
public:
	Room_loot(uint32_t seed, unsigned int maxX, unsigned int maxY, Map* map, int key);
	~Room_loot();
	bool test;
	void Room_loot::printType();
};
#endif