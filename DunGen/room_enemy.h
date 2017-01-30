#pragma once
#ifndef ROOM_ENEMY_H
#define ROOM_ENEMY_H

#include "stdafx.h"
#include "room.h"
#include <vector>

class Room_enemy : public Room {
public:
	Room_enemy(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY);
	virtual ~Room_enemy();
	virtual void printType();
	static vector<Room_enemy*> enemyRooms;
	uint32_t enemyId;
};
#endif
