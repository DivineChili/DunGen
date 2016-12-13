#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Room {
private:
	uint32_t seed;
	int id;
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
public:
	vector<Room*> rooms;
	Room::Room();
};