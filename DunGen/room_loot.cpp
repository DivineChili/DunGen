#include "stdafx.h"
#include "room_loot.h"


Room_loot::Room_loot(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY):
	Room::Room(seed, map, key, 'L',maxX, maxY, minX, minY),
	lootId(Room_loot::lootRooms.size()){
	
	lootRooms.push_back(this);

	//cout << "Making a loot room" << endl;
}

void Room_loot::build() {
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

	int doorSide = this->randomizer.randomizeInRange(0,4,this->id);
	
	for (int i = 0; i < 4; i++) {
		if (this->doorIsValid()) {
			int chestOffset = 0;
			switch (doorSide) {
			case 0:
				cout << "loot on top wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->width, i);
				if (this->chestIsValid()) {
					this->map->setCellStructureAtPos(this->x + chestOffset, this->y, "111llllll");
					break;
				}
			case 1:
				cout << "loot on left wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->height, i);
				if (this->chestIsValid()) {
					this->map->setCellStructureAtPos(this->x, this->y + chestOffset, "lllllllll");
					break;
				}
			case 2:
				cout << "loot on bottom wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->width, i);
				if (this->chestIsValid()) {
					this->map->setCellStructureAtPos(this->x + chestOffset, this->y + this->height, "lllllllll");
					break;
				}
			case 3:
				cout << "loot on right wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->height, i);
				if (this->chestIsValid()) {
					this->map->setCellStructureAtPos(this->x + this->width, this->y + chestOffset, "lllllllll");
					break;
				}
			default:
				cout << "Room side is not between 0 and 3." << endl;
			}
		}
	}


	//Code for labeling the rooms by type with a character.
	string cell;
	cell += "----";	cell += letter;	cell += "----";
	this->map->setCellStructureAtPos(this->x + this->width / 2, this->y + this->height / 2, cell);
	//cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;

	buildDoors();
}

Room_loot::~Room_loot(){
	//cout << "Deleting loot room" << endl;
	Room_loot::lootRooms.pop_back();
}

bool Room_loot::chestIsValid() {
	return true;
}

void Room_loot::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
	//cout << "Test: " << test << endl;
}

vector<Room_loot*> Room_loot::lootRooms;