#pragma once
#ifndef ROOM_H
#define ROOM_H

#include "stdafx.h"
#include "randomizer.h"
#include "map.h"
#include "cell.h"
#include <vector>

using namespace std;

class Room {
private:
	uint32_t seed;
public:
	Randomizer randomizer;
	uint32_t x;
	uint32_t y;
	unsigned int maxX;
	unsigned int maxY;
	uint32_t width;
	uint32_t height;
	Map* map;
	static vector<Room*> rooms;
	int key;
	bool overlap;
	uint32_t id;
	char letter;
	Room(uint32_t seed, Map* map, int key, char letter, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY);
	virtual ~Room();
	virtual void printType() = 0;
	virtual bool isOverlapping();
	virtual void build();
	virtual void buildDoors();
	void buildDoors_SubCell(Cell* cell, int side);
        void openDoorWall();
        bool doorIsValid();
	void updateRandomizerSeed();
};

#endif
