#pragma once
#ifndef ROOM_H
#define ROOM_H

#include "stdafx.h"
#include "randomizer.h"
#include "map.h"
#include <vector>

using namespace std;

static enum TYPE {DEFAULT = 0, LOOT = 1, BOSS = 2};

class Room {
private:
	uint32_t seed;
	Randomizer randomizer;
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
public:
	static vector<Room*> rooms;
	bool overlap;
	uint32_t id;
	Room::Room(uint32_t seed, pair<int, int> min, pair<int, int> max, Map* map, int key);
	Room::Room(uint32_t seed, int type, Map* map, int key);
	virtual Room::~Room();
	virtual void printType() = 0;
	void Room::construct(Map* map);
	int Room::getSizeFromType(char xy, int type, bool _max);
};

#endif