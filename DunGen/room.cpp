#include "stdafx.h"
#include "room.h"
#include <iostream>

vector<Room*> Room::rooms;
Room::Room(uint32_t seed) {
	this->seed = seed;
	this->id = Room::rooms.size();//Set id
	this->rooms.push_back(this);//Push to static vector
	cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;
}