#include "stdafx.h"
#include "room_loot.h"


Room_loot::Room_loot(uint32_t seed, Map* map, int key) : Room::Room(seed, DEFAULT, map, key), test("hello") {
	cout << "Making room: Loot" << endl;
}

Room_loot::~Room_loot(){
}

void Room_loot::printType() {
	//string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << typeid(this->rooms[this->id]).name() << endl;
	cout << "Test: " << test << endl;
}
