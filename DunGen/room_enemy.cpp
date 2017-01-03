#include "stdafx.h"
#include "room_enemy.h"


Room_enemy::Room_enemy(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY) :
	Room::Room(seed, map, key, 'E', maxX, maxY, minX, minY),
	enemyId(Room_enemy::enemyRooms.size()){

	enemyRooms.push_back(this);
	//cout << "Creating an enemy room!" << endl;
}


Room_enemy::~Room_enemy(){
	//cout << "Deleting enemy room!" << endl;
	Room_enemy::enemyRooms.pop_back();
}
void Room_enemy::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
}
vector<Room_enemy*> Room_enemy::enemyRooms;