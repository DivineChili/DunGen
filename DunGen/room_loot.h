#pragma once
#ifndef ROOM_LOOT_H
#define ROOM_LOOT_H

#include "room.h"

class Room_loot : public Room {
public:
	string test;
	Room_loot(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY);
	virtual ~Room_loot();
	virtual void Room_loot::printType();
private:
};
#endif