#pragma once
#ifndef ROOM_TRAP_H
#define ROOM_TRAP_H

#include "stdafx.h"
#include "room.h"
#include <vector>

class Room_trap : public Room {
public:
	Room_trap(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY);
	virtual ~Room_trap();
	virtual void Room_trap::printType();
	static vector<Room_trap*> trapRooms;
	uint32_t trapId;
private:
};
#endif