#include "stdafx.h"
#include "room_boss.h"


Room_boss::Room_boss(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY) :
	Room::Room(seed, map, key, 'B', maxX, maxY, minX, minY),
	bossId(Room_boss::bossRooms.size()){

	bossRooms.push_back(this);

	//cout << "Creating a boss room!" << endl;
}


Room_boss::~Room_boss(){
	//cout << "Deleting boss room!" << endl;
	Room_boss::bossRooms.pop_back();
}
void Room_boss::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
}

void Room_boss::build() {
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

	//This will place columns along the long sides of boss rooms.

	if (this->width > this->height) {
		if (width > 8) {
			if ((this->width % 2) == 1) {
				//Place a column at every other corner.

				for (int i = 0; i < this->width; i += 2) {
					this->map->setCellStructureAtPos(this->x + i, this->y + 1,"        C");
					this->map->setCellStructureAtPos(this->x + i, this->y + 2,"  C      ");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + 1,"      C  ");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + 2,"C        ");

					this->map->setCellStructureAtPos(this->x + i, this->y + this->height - 1,"  C      ");
					this->map->setCellStructureAtPos(this->x + i, this->y + this->height - 2,"        C");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + this->height - 1,"C        ");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + this->height - 2,"      C  ");
				}				
			}
			else {
				//Place a column at every corner.
				for (int i = 0; i < this->width; i += 1) {
					this->map->setCellStructureAtPos(this->x + i, this->y + 1, "        C");
					this->map->setCellStructureAtPos(this->x + i, this->y + 2, "  C      ");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + 1, "      C  ");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + 2, "C        ");

					this->map->setCellStructureAtPos(this->x + i, this->y + this->height - 1, "  C      ");
					this->map->setCellStructureAtPos(this->x + i, this->y + this->height - 2, "        C");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + this->height - 1, "C        ");
					this->map->setCellStructureAtPos(this->x + i + 1, this->y + this->height - 2, "      C  ");
				}
			}
		}
		else {
			//Place a column at every corner.
			for (int i = 0; i < this->width; i += 1) {
				this->map->setCellStructureAtPos(this->x + i, this->y + 1, "        C");
				this->map->setCellStructureAtPos(this->x + i, this->y + 2, "  C      ");
				this->map->setCellStructureAtPos(this->x + i + 1, this->y + 1, "      C  ");
				this->map->setCellStructureAtPos(this->x + i + 1, this->y + 2, "C        ");

				this->map->setCellStructureAtPos(this->x + i, this->y + this->height - 1, "  C      ");
				this->map->setCellStructureAtPos(this->x + i, this->y + this->height - 2, "        C");
				this->map->setCellStructureAtPos(this->x + i + 1, this->y + this->height - 1, "C        ");
				this->map->setCellStructureAtPos(this->x + i + 1, this->y + this->height - 2, "      C  ");
			}
		}
	}
	else if (this->width < this->height) {
		if (width > 8) {
			if ((this->height % 2) == 1) {
				//Place a column at every other corner.
				for (int i = 0; i < this->height; i += 2) {
					this->map->setCellStructureAtPos(this->x + 1, this->y + i,     "        C");
					this->map->setCellStructureAtPos(this->x + 2, this->y + i,     "      C  ");
					this->map->setCellStructureAtPos(this->x + 1, this->y + i + 1, "  C      ");
					this->map->setCellStructureAtPos(this->x + 2, this->y + i + 1, "C        ");
				
					this->map->setCellStructureAtPos(this->x + this->width - 1, this->y + i,     "      C  ");
					this->map->setCellStructureAtPos(this->x + this->width - 2, this->y + i,     "        C");
					this->map->setCellStructureAtPos(this->x + this->width - 1, this->y + i + 1, "C        ");
					this->map->setCellStructureAtPos(this->x + this->width - 2, this->y + i + 1, "  C      ");
				}
			}
			else {
				//Place a column at every corner.
				for (int i = 0; i < this->height; i += 1) {
					this->map->setCellStructureAtPos(this->x + 1, this->y + i, "        C");
					this->map->setCellStructureAtPos(this->x + 2, this->y + i, "      C  ");
					this->map->setCellStructureAtPos(this->x + 1, this->y + i + 1, "  C      ");
					this->map->setCellStructureAtPos(this->x + 2, this->y + i + 1, "C        ");

					this->map->setCellStructureAtPos(this->x + this->width - 1, this->y + i, "      C  ");
					this->map->setCellStructureAtPos(this->x + this->width - 2, this->y + i, "        C");
					this->map->setCellStructureAtPos(this->x + this->width - 1, this->y + i + 1, "C        ");
					this->map->setCellStructureAtPos(this->x + this->width - 2, this->y + i + 1, "  C      ");
				}
			}
		}
		else {
			//Place a column at every corner.
			for (int i = 0; i < this->height; i += 1) {
				this->map->setCellStructureAtPos(this->x + 1, this->y + i, "        C");
				this->map->setCellStructureAtPos(this->x + 2, this->y + i, "      C  ");
				this->map->setCellStructureAtPos(this->x + 1, this->y + i + 1, "  C      ");
				this->map->setCellStructureAtPos(this->x + 2, this->y + i + 1, "C        ");

				this->map->setCellStructureAtPos(this->x + this->width - 1, this->y + i, "      C  ");
				this->map->setCellStructureAtPos(this->x + this->width - 2, this->y + i, "        C");
				this->map->setCellStructureAtPos(this->x + this->width - 1, this->y + i + 1, "C        ");
				this->map->setCellStructureAtPos(this->x + this->width - 2, this->y + i + 1, "  C      ");
			}
		}
	}
	else if (this->width == this->height) {
		cout << "width = height" << endl;
	}

	//Code for labeling the rooms by type with a character.
	string cell;
	cell += "----";	cell += letter;	cell += "----";
	this->map->setCellStructureAtPos(this->x + this->width / 2, this->y + this->height / 2, cell);
	cout << "Rooms[" << this->id << "]->id: " << this->rooms[this->id]->id << endl;

	buildDoors();
}

void Room_boss::buildDoors() {
	for (int i = 0; i < 1; i++) {
		int sideNum = this->randomizer.randomizeInRange(0, 3, this->id + i);
		int j = 0;
		if (sideNum == 0) {
			j = 0;
			do {
				this->map->setCellStructureAtPos((this->x + floor(this->width / 2)) + j, this->y, "DDDDDDDDD");
				j++;
			} while ((this->width + j) % 2 != 1);
		}
		else if (sideNum == 1) {
			j = 0;
			do {
				this->map->setCellStructureAtPos(this->x, (this->y + floor(this->height / 2)) + j, "DDDDDDDDD");
				j++;
			} while ((this->height + j) % 2 != 1);
		}
		else if (sideNum == 2) {
			j = 0;
			do {
				this->map->setCellStructureAtPos((this->x + floor(this->width / 2)) + j, (this->y + this->height), "DDDDDDDDD");
				j++;
			} while ((this->width + j) % 2 != 1);
		}
		else if (sideNum == 3) {
			j = 0;
			do {
				this->map->setCellStructureAtPos((this->x + this->width), this->y + floor(this->height / 2) + j, "DDDDDDDDD");
				j++;
			} while ((this->height + j) % 2 != 1);
		}
	}
}

vector<Room_boss*> Room_boss::bossRooms;