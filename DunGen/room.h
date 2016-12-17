#pragma once
#ifndef ROOM_H
#define ROOM_H

#include "stdafx.h"
#include "randomizer.h"
#include "map.h"
#include <vector>

using namespace std;

class Room {
private:
	uint32_t seed;
	Randomizer randomizer;
	uint32_t id;
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
public:
	static vector<Room*> rooms;
	bool overlap;
	Room::Room(uint32_t seed, unsigned int maxX, unsigned int maxY, Map* map, int key);
	Room::~Room();
};

#endif