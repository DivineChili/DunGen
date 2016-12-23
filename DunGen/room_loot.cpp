#include "stdafx.h"
#include "room_loot.h"


Room_loot::Room_loot(uint32_t seed, unsigned int maxX, unsigned int maxY, Map* map, int key): Room::Room(seed, maxX, maxY, map, key), test("hello"){
	cout << "Making a loot room" << endl;
}

Room_loot::~Room_loot(){
	cout << "Deleting loot room" << "-----------------------------------" << endl;
}

void Room_loot::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
	cout << "Test: " << test << endl;
}
