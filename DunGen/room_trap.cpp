#include "stdafx.h"
#include "room_trap.h"


Room_trap::Room_trap(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY) :
	Room::Room(seed, map, key, 'T', maxX, maxY, minX, minY),
	trapId(Room_trap::trapRooms.size()) {

	trapRooms.push_back(this);
	cout << "Creating a trap room!" << endl;
}


Room_trap::~Room_trap() {
	cout << "Deleting trap room!" << endl;
	Room_trap::trapRooms.pop_back();
}
void Room_trap::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
}

vector<Room_trap*> Room_trap::trapRooms;