#include "stdafx.h"
#include "room.h"
#include "room_loot.h"

vector<Room*> Room::rooms;

Room::Room(uint32_t seed, unsigned int maxX, unsigned int maxY, Map* map, int key) :
	seed(seed), randomizer(seed), //Initialization list
	x(this->randomizer.randomizeFromKey(key) % (map->getSize().first - maxX)),
	y(this->randomizer.randomizeFromKey(key + 1) % (map->getSize().second - maxY)),
	width(((this->randomizer.randomizeFromKey(key + 2) % (maxX - 2))) + 2),
	height(((this->randomizer.randomizeFromKey(key + 3) % (maxY - 2))) + 2),
	id(Room::rooms.size()),
	overlap(false) {
	
	this->rooms.push_back(this); //Push to static vector
	cout << "Creating room!" << endl;
	/*
		Map construction here
	*/
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
		cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;
	} else {
		cout << "Room overlapping" << endl;
	}
}

Room::~Room() {
	cout << "Destroying room!" << endl;
}



