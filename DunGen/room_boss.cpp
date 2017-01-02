#include "stdafx.h"
#include "room_boss.h"


Room_boss::Room_boss(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY) :
	Room::Room(seed, map, key, 'B', maxX, maxY, minX, minY),
	bossId(Room_boss::bossRooms.size()){

	bossRooms.push_back(this);

	int doorSide = this->randomizer.randomizeInRange(0, 3, 0);
	if (doorSide == 0) {
		if (this->width % 2) { //True if odd
			//cout << "lkajfsd;lkfajsl;kdfjlkasj;lfjalsk;djfl;kajl;kfjl;askdj;fklaklfjsal;jdf;lkajfkl;adsj" << endl;
			//cout << "x:" << this->x + ((this->width / 2)) << " y:" << this->y << endl;
			//map->setCellStructureAtPos(this->x + (floor(this->width / 2)), this->y, "DDDDDDDDD");
		}
	}

	cout << "Creating a boss room!" << endl;
}


Room_boss::~Room_boss(){
	cout << "Deleting boss room!" << endl;
	Room_boss::bossRooms.pop_back();
}
void Room_boss::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
}

vector<Room_boss*> Room_boss::bossRooms;