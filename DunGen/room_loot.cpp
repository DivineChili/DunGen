#include "stdafx.h"
#include "room_loot.h"


Room_loot::Room_loot(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY):
	Room::Room(seed, map, key, 'L',maxX, maxY, minX, minY),
	lootId(Room_loot::lootRooms.size()){
	
	lootRooms.push_back(this);

	cout << "Making a loot room" << endl;
}

Room_loot::~Room_loot(){
	//cout << "Deleting loot room" << endl;
	Room_loot::lootRooms.pop_back();
}

void Room_loot::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
	//cout << "Test: " << test << endl;
}

vector<Room_loot*> Room_loot::lootRooms;