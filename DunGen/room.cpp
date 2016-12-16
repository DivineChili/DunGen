#include "stdafx.h"
#include "room.h"
#include <iostream>

vector<Room*> Room::rooms;

Room::Room(uint32_t seed, unsigned int maxX, unsigned int maxY, Map* map, int key) : randomizer(seed) {
	this->overlap = false;
	this->id = Room::rooms.size(); //Set id
	this->rooms.push_back(this); //Push to static vector
	cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;
	this->x = (this->randomizer.randomizeFromKey(key) % (map->getSize().first - maxX));
	this->y = (this->randomizer.randomizeFromKey(key + 1) % (map->getSize().second - maxY));
	this->width = (this->randomizer.randomizeFromKey(key + 2) % maxX);
	this->height = (this->randomizer.randomizeFromKey(key + 3) % maxY);

	if (this->width <= 2) this->width = 2;
	if (this->height <= 2) this->height = 2;

	/*
		Map construction here
	*/
	for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
		for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
			if (map->cellVisited(posX, posY)) {
				this->overlap = true;
				//Room(seed, maxX, maxY, map, key + 4);
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
		cout << "Room Generation Complete!\n";
	} else {
		cout << "Room overlapping" << endl << "Reconstructing room!" << endl;
	}
}

Room::~Room() {
	cout << "Destroying room!" << endl;
}


