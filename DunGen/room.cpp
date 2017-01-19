#include "stdafx.h"
#include "room.h"
#include "room_loot.h"
#include "door.h"
#include <string>

vector<Room*> Room::rooms;

Room::Room(uint32_t seed, Map* map, int key, char letter, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY) :
	seed(seed),
	randomizer(seed),
	id(Room::rooms.size()),
	map(map),
	key(key),
	letter(letter),
	x(this->randomizer.randomizeFromKey(key) % (map->getSize().first - maxX)),
	y(this->randomizer.randomizeFromKey(key + 1) % (map->getSize().second - maxY)),
	width((this->randomizer.randomizeFromKey(key + 2) % (maxX - minX)) + minX),
	height((this->randomizer.randomizeFromKey(key+ 3) % (maxY - minY)) + minY),
	overlap(false) {

	this->rooms.push_back(this);
}

Room::~Room() {
	Room::rooms.pop_back(); //Remove last element of vector.
}

bool Room::isOverlapping() {
	//Check for any cells already visited.
	for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
		for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
			if (map->getCellAtPos(posX, posY)->_visited) {
				//This will make the while-loop delete the room to prevent overlapping.
				this->overlap = true;//Room is overlapping
				return true;
			}
		}
	}
	return false;//Room is not overlapping
}

void Room::build() {
	// Loop through and generate the cells at positions in map
	//cout << this->width << this->height << this->x << this->y << endl;
	for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
		for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
																			// Visit cell
			this->map->getCellAtPos(posX, posY)->setVisited(true);
			// Construct the 4 corners of the room
			if (posY == this->y && posX == this->x) this->map->getCellAtPos(posX, posY)->setCellStructure("####--#--"); // Top Left
			else if (posY == (this->y + this->height) && posX == this->x) this->map->getCellAtPos(posX, posY)->setCellStructure("#--#--###"); // Bottom Left
			else if (posY == this->y && posX == (this->x + this->width)) this->map->getCellAtPos(posX, posY)->setCellStructure("###--#--#"); // Top Right
			else if (posY == (this->y + this->height) && posX == (this->x + this->width)) this->map->getCellAtPos(posX, posY)->setCellStructure("--#--####"); // Bottom Right
																																							   // Construct the 4 walls
			else if (posY == this->y && (posX != this->x || posX != (this->x + this->width))) this->map->getCellAtPos(posX, posY)->setCellStructure("###------"); // Top wall
			else if (posX == this->x && (posY != this->y || posY != (this->y + this->height))) this->map->getCellAtPos(posX, posY)->setCellStructure("#--#--#--"); // Left Wall
			else if (posY == (this->y + this->height) && (posX != this->x || posX != (this->x + this->width))) this->map->getCellAtPos(posX, posY)->setCellStructure("------###"); // Bottom wall
			else if (posX == (this->x + this->width) && (posY != this->y || posY != (this->y + this->height))) this->map->getCellAtPos(posX, posY)->setCellStructure("--#--#--#"); // Right wall
																																													// Else, construct middle room
			else this->map->getCellAtPos(posX, posY)->setCellStructure("---------");

		}
	}
	//Code for labeling the rooms by type with a character.
	string cell;
	cell += "////";	cell += letter;	cell += "////";
	this->map->getCellAtPos(this->x + this->width / 2, this->y + this->height / 2)->setCellStructure(cell);

	buildDoors();
}

void Room::buildDoors() {
	for (int i = 0; i < 2; i++) {
		int sideNum = this->randomizer.randomizeInRange(0, 3, this->id + i);

		int j = 0;
		if (sideNum == 0) {
			j = 0;
			do {
				this->map->getCellAtPos((this->x + floor(this->width / 2)) + j, this->y)->setCellStructure("/D///////");
				this->buildDoors_SubCell(this->map->getCellAtPos((this->x + floor(this->width / 2)) + j, this->y),0);
				j++;
			} while ((this->width + j) % 2 != 1);
		}
		else if (sideNum == 1) {
			j = 0;
			do {
				this->map->getCellAtPos(this->x, (this->y + floor(this->height / 2)) + j)->setCellStructure("///D/////");
				this->buildDoors_SubCell(this->map->getCellAtPos(this->x, (this->y + floor(this->height / 2)) + j), 1);
				j++;
			} while ((this->height + j) % 2 != 1);
		}
		else if (sideNum == 2) {
			j = 0;
			do {
				this->map->getCellAtPos((this->x + floor(this->width / 2)) + j, (this->y + this->height))->setCellStructure("///////D/");
				this->buildDoors_SubCell(this->map->getCellAtPos((this->x + floor(this->width / 2)) + j, (this->y + this->height)), 2);
				j++;
			} while ((this->width + j) % 2 != 1);
		}
		else if (sideNum == 3) {
			j = 0;
			do {
				this->map->getCellAtPos((this->x + this->width), this->y + floor(this->height / 2) + j)->setCellStructure("/////D///");
				this->buildDoors_SubCell(this->map->getCellAtPos((this->x + this->width), this->y + floor(this->height / 2) + j), 3);
				j++;
			} while ((this->height + j) % 2 != 1);
		}
	}
}

void Room::buildDoors_SubCell(Cell* cell, int side) {
	switch (side) {
	case 0://North
		for (int i = 1; i < 4; i++) {
			cell->setSubCellAtPos(new Door(i, 0));
		}
		break;
	case 1://West
		for (int i = 1; i < 4; i++) {
			cell->setSubCellAtPos(new Door(0, i));
		}
		break;
	case 2://South
		for (int i = 1; i < 4; i++) {
			cell->setSubCellAtPos(new Door(i, 4));
		}
		break;
	case 3://East
		for (int i = 1; i < 4; i++) {
			cell->setSubCellAtPos(new Door(4, i));
		}
		break;
	}


}

bool Room::doorIsValid() {
	return true;
}

void Room::updateRandomizerSeed() {
	this->randomizer.updateSeed();
}
