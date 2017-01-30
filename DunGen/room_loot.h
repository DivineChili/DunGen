#pragma once
#ifndef ROOM_LOOT_H
#define ROOM_LOOT_H

#include "stdafx.h"
#include "room.h"
#include <vector>

class Room_loot : public Room {
public:
	Room_loot(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY);
	virtual ~Room_loot();
	virtual void build();
	bool chestIsValid();
	virtual void printType();
	static vector<Room_loot*> lootRooms;
	uint32_t lootId;
private:
};
#endif
