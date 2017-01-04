#include "stdafx.h"
#include "default_room.h"


Default_room::Default_room(uint32_t seed, Map* map, int key) : Room::Room(seed, DEFAULT, map, key) {
	cout << "Making Room: Default" << endl;
}


Default_room::~Default_room() {
}

void Default_room::printType() {
	//string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << typeid(this->rooms[this->id]).name() << endl;
}