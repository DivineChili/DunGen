#include "stdafx.h"
#include "room.h"
#include <iostream>

vector<Room*> Room::rooms;
Room::Room(uint32_t seed, unsigned int maxX, unsigned int maxY): randomizer(seed) {
	cout << "Creating room!" << endl;
	this->seed = seed;
	this->id = Room::rooms.size();//Set id
	this->rooms.push_back(this);//Push to static vector
	cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;
	this->x = this->randomizer.randomizeFromKey(0);
	this->y = this->randomizer.randomizeFromKey(1);
	this->width = this->randomizer.randomizeFromKey(2);
	this->height = this->randomizer.randomizeFromKey(3);
}
Room::~Room() {
	cout << "Destroying room!" << endl;
}
void createRooms(int attempts) {
	
};
