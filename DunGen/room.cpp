#include "stdafx.h"
#include "room.h"
#include <iostream>

Room::Room() {
	this->id = Room::rooms.size();
	cout << this->id << endl;
	this->rooms.push_back(this);
}