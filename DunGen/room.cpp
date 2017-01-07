#include "stdafx.h"
#include "room.h"
#include "room_loot.h"
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
	//cout << "Creating room!" << endl;
}

Room::~Room() {
	//cout << "Destroying room!" << endl;
	Room::rooms.pop_back(); //Remove last element of vector.
}

bool Room::isOverlapping() {
	//Check for any cells already visited.
	//cout << "height:" << this->height << " width:" << this->width << " x:" << this->x << " y:" << this->y << endl;
	for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
		for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
			if (map->cellVisited(posX, posY)) {
				//This will make the while-loop delete the room to prevent overlapping.
				//cout << "Room overlapping!!!!!!!" << endl;
				this->overlap = true;
				return true;
			}
		}
	}
	//cout << "Room not overlapping !!!!!!" << endl;
	return false;
}

void Room::build() {
	// Loop through and generate the cells at positions in map
	//cout << this->width << this->height << this->x << this->y << endl;
	for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
		for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
																			// Visit cell
			this->map->visitCell(posX, posY);
			// Construct the 4 corners of the room
			if (posY == this->y && posX == this->x) this->map->setCellStructureAtPos(posX, posY, "####--#--"); // Top Left
			else if (posY == (this->y + this->height) && posX == this->x) this->map->setCellStructureAtPos(posX, posY, "#--#--###"); // Bottom Left
			else if (posY == this->y && posX == (this->x + this->width)) this->map->setCellStructureAtPos(posX, posY, "###--#--#"); // Top Right
			else if (posY == (this->y + this->height) && posX == (this->x + this->width)) this->map->setCellStructureAtPos(posX, posY, "--#--####"); // Bottom Right
																																							   // Construct the 4 walls
			else if (posY == this->y && (posX != this->x || posX != (this->x + this->width))) this->map->setCellStructureAtPos(posX, posY, "###------"); // Top wall
			else if (posX == this->x && (posY != this->y || posY != (this->y + this->height))) this->map->setCellStructureAtPos(posX, posY, "#--#--#--"); // Left Wall
			else if (posY == (this->y + this->height) && (posX != this->x || posX != (this->x + this->width))) this->map->setCellStructureAtPos(posX, posY, "------###"); // Bottom wall
			else if (posX == (this->x + this->width) && (posY != this->y || posY != (this->y + this->height))) this->map->setCellStructureAtPos(posX, posY, "--#--#--#"); // Right wall
																																													// Else, construct middle room
			else this->map->setCellStructureAtPos(posX, posY, "---------");

		}
	}
	//Code for labeling the rooms by type with a character.
	string cell;
	cell += "////";	cell += letter;	cell += "////";
	this->map->setCellStructureAtPos(this->x + this->width / 2, this->y + this->height / 2, cell);
	//cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;

	buildDoors();
}

void Room::buildDoors() {
	for (int i = 0; i < 2; i++) {
		int sideNum = this->randomizer.randomizeInRange(0, 3, this->id + i);
		int j = 0;
		if (sideNum == 0) {
			j = 0;
			do {
				this->map->setCellStructureAtPos((this->x + floor(this->width / 2)) + j, this->y, "/D///////");
				j++;
			} while ((this->width + j) % 2 != 1);
		}
		else if (sideNum == 1) {
			j = 0;
			do {
				this->map->setCellStructureAtPos(this->x, (this->y + floor(this->height / 2)) + j, "///D/////");
				j++;
			} while ((this->height + j) % 2 != 1);
		}
		else if (sideNum == 2) {
			j = 0;
			do {
				this->map->setCellStructureAtPos((this->x + floor(this->width / 2)) + j, (this->y + this->height), "///////D/");
				j++;
			} while ((this->width + j) % 2 != 1);
		}
		else if (sideNum == 3) {
			j = 0;
			do {
				this->map->setCellStructureAtPos((this->x + this->width), this->y + floor(this->height / 2) + j, "/////D///");
				j++;
			} while ((this->height + j) % 2 != 1);
		}
	}
}

bool Room::doorIsValid() {
	return true;
}

void Room::updateRandomizerSeed() {
	this->randomizer.updateSeed();
}
