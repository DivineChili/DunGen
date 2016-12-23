#include "stdafx.h"
#include "boss_room.h"


Boss_room::Boss_room(uint32_t seed, Map* map, int key) : Room::Room(seed, DEFAULT, map, key) {
	cout << "Making room: Boss" << endl;
}


Boss_room::~Boss_room(){
}

void Boss_room::printType() {
	//string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << typeid(this->rooms[this->id]).name() << endl;
}