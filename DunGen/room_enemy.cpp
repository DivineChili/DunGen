#include "stdafx.h"
#include "room_enemy.h"


Room_enemy::Room_enemy(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY) :
	Room::Room(seed, map, key, 'E', maxX, maxY, minX, minY) {
	cout << "Creating an enemy room!" << endl;
}


Room_enemy::~Room_enemy()
{
}
void Room_enemy::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
	//cout << "Test: " << test << endl;
}