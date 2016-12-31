#include "stdafx.h"
#include "room_boss.h"


Room_boss::Room_boss(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY) :
	Room::Room(seed, map, key, 'B', maxX, maxY, minX, minY){
	cout << "Creating a boss room!" << endl;
}


Room_boss::~Room_boss()
{
}
void Room_boss::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
	//cout << "Test: " << test << endl;
}