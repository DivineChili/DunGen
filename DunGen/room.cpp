#include "stdafx.h"
#include "room.h"
#include <iostream>

vector<Room*> Room::rooms;
int Room::test;
Room::Room() {
	this->id = Room::rooms.size();
	cout << this->id << endl;
	this->rooms.push_back(this);
	cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;
}