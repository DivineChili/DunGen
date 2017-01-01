#pragma once
#ifndef ROOM_BOSS_H
#define ROOM_BOSS_H

#include "stdafx.h"
#include "room.h"
#include <vector>

class Room_boss : public Room {
public:
	Room_boss(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY);
	virtual ~Room_boss();
	virtual void Room_boss::printType();
	static vector<Room*> bossRooms;
	uint32_t bossId;
private:
};
#endif