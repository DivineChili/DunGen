#include "stdafx.h"
#include "room.h"
#include "room_loot.h"

vector<Room*> Room::rooms;

// Construct map from induvidual min-max values
Room::Room(uint32_t seed, pair<int, int> min, pair<int, int> max, Map* map, int key) :
	seed(seed), randomizer(seed), //Initialization list
	x(this->randomizer.randomizeFromKey(key) % (map->getSize().first - max.first)),
	y(this->randomizer.randomizeFromKey(key + 1) % (map->getSize().second - max.second)),
	width(((this->randomizer.randomizeFromKey(key + 2) % (max.first - min.first))) + min.first),
	height(((this->randomizer.randomizeFromKey(key + 3) % (max.second - min.second))) + min.second),
	id(Room::rooms.size()),
	overlap(false) {

	this->rooms.push_back(this); //Push to static vector
	//cout << "Creating room!" << endl;

	Room::construct(map);
}

// Construct room from type only
Room::Room(uint32_t seed, int type, Map* map, int key) :
	seed(seed), randomizer(seed), //Initialization list
	x(this->randomizer.randomizeFromKey(key) % (map->getSize().first - getSizeFromType('x',type, true))),
	y(this->randomizer.randomizeFromKey(key + 1) % (map->getSize().second - getSizeFromType('y',type, true))),
	width(((this->randomizer.randomizeFromKey(key + 2) % (getSizeFromType('x', type, true) - getSizeFromType('x', type, false)))) + getSizeFromType('x', type, false)),
	height(((this->randomizer.randomizeFromKey(key + 3) % (getSizeFromType('y', type, true) - getSizeFromType('y', type, false)))) + getSizeFromType('y', type, false)),
	id(Room::rooms.size()),
	overlap(false) {

	this->rooms.push_back(this); //Push to static vector
	//cout << "Creating room!" << endl;

	Room::construct(map);
}

void Room::construct(Map* map) {
	//Check for any cells already visited.
	for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
		for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
			if (map->cellVisited(posX, posY)) {
				//This will make the while-loop delete the room to prevent overlapping.
				this->overlap = true;
			}
		}
	}

	if (!this->overlap) {
		// Loop through and generate the cells at positions in map
		for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
			for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
																				// Visit cell
				map->visitCell(posX, posY);

				// Construct the 4 corners of the room
				if (posY == this->y && posX == this->x) map->setCellStructureAtPos(posX, posY, "####--#--"); // Top Left
				else if (posY == (this->y + this->height) && posX == this->x) map->setCellStructureAtPos(posX, posY, "#--#--###"); // Bottom Left
				else if (posY == this->y && posX == (this->x + this->width)) map->setCellStructureAtPos(posX, posY, "###--#--#"); // Top Right
				else if (posY == (this->y + this->height) && posX == (this->x + this->width)) map->setCellStructureAtPos(posX, posY, "--#--####"); // Bottom Right

																																				   // Construct the 4 walls
				else if (posY == this->y && (posX != this->x || posX != (this->x + this->width))) map->setCellStructureAtPos(posX, posY, "###------"); // Top wall
				else if (posX == this->x && (posY != this->y || posY != (this->y + this->height))) map->setCellStructureAtPos(posX, posY, "#--#--#--"); // Left Wall
				else if (posY == (this->y + this->height) && (posX != this->x || posX != (this->x + this->width))) map->setCellStructureAtPos(posX, posY, "------###"); // Bottom wall
				else if (posX == (this->x + this->width) && (posY != this->y || posY != (this->y + this->height))) map->setCellStructureAtPos(posX, posY, "--#--#--#"); // Right wall

																																										// Else, construct middle room
				else map->setCellStructureAtPos(posX, posY, "---------");

			}
		}
		//cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;
	}
	else {
		//cout << "Room overlapping" << endl;
	}
}

Room::~Room() {
	cout << "Destroying room!" << endl;
}


// Function to define what sizes the different room-types use
int Room::getSizeFromType(char xy, int type, bool _max) {
	switch (type)
	{
	case(LOOT):
		     if (xy == 'x' && !_max) return 2; // Min x
		else if (xy == 'y' && !_max) return 2; // Min y
		else if (xy == 'x' &&  _max) return 3; // Max x
		else if (xy == 'y' &&  _max) return 3; // Max y
		else return 2;
		break;
	case(BOSS):
		     if (xy == 'x' && !_max) return 6; // Min x
		else if (xy == 'y' && !_max) return 6; // Min y
		else if (xy == 'x' &&  _max) return 10; // Max x
		else if (xy == 'y' &&  _max) return 8; // Max y
		else return 8;
		break;
	case(DEFAULT):
	default:
	         if (xy == 'x' && !_max) return 2; // Min x
		else if (xy == 'y' && !_max) return 2; // Min y
		else if (xy == 'x' &&  _max) return 4; // Max x
		else if (xy == 'y' &&  _max) return 4; // Max y
		else return 4;
		break;
	}
}

