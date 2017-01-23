#include "stdafx.h"
#include "room_loot.h"
#include "wall.h"
#include "floor.h"
#include "chest.h"

Room_loot::Room_loot(uint32_t seed, Map* map, int key, unsigned int maxX, unsigned int maxY, unsigned int minX, unsigned int minY):
	Room::Room(seed, map, key, 'L',maxX, maxY, minX, minY),
	lootId(Room_loot::lootRooms.size()){
	
	lootRooms.push_back(this);
}

void Room_loot::build() {
	// Loop through and generate the cells at positions in map
	//cout << this->width << this->height << this->x << this->y << endl;
	for (int posY = this->y; posY <= (this->y + this->height); posY++) { // Loops through the cells aalong the y-axis, starting from the starting y-position
		for (int posX = this->x; posX <= (this->x + this->width); posX++) { // Loops through the cells along the x-axis starting from the starting x-position
																			// Visit cell
			this->map->getCellAtPos(posX, posY)->setVisited(true);
			// Construct the 4 corners of the room
			if (posY == this->y && posX == this->x) {// Top Left 
				this->map->getCellAtPos(posX, posY)->setCellStructure("####--#--");
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][0] = new Wall(j, 0);
						this->map->getCellAtPos(posX, posY)->subCell_grid[0][j] = new Wall(0, j);
					}
				}
				for (int i = 1; i < 5; i++) {
					for (int j = 1; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
			else if (posY == (this->y + this->height) && posX == this->x) {// Bottom Left
				this->map->getCellAtPos(posX, posY)->setCellStructure("#--#--###");
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][0] = new Wall(j, 0);
						this->map->getCellAtPos(posX, posY)->subCell_grid[4][j] = new Wall(0, j);
					}
				}
				for (int i = 1; i < 5; i++) {
					for (int j = 0; j < 4; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
			else if (posY == this->y && posX == (this->x + this->width)) {// Top Right
				this->map->getCellAtPos(posX, posY)->setCellStructure("###--#--#");
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][4] = new Wall(j, 0);
						this->map->getCellAtPos(posX, posY)->subCell_grid[0][j] = new Wall(0, j);
					}
				}
				for (int i = 0; i < 4; i++) {
					for (int j = 1; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
			else if (posY == (this->y + this->height) && posX == (this->x + this->width)) {// Bottom Right
				this->map->getCellAtPos(posX, posY)->setCellStructure("--#--####");
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][4] = new Wall(j, 0);
						this->map->getCellAtPos(posX, posY)->subCell_grid[4][j] = new Wall(0, j);
					}
				}
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			} 																																			   // Construct the 4 walls
			else if (posY == this->y && (posX != this->x || posX != (this->x + this->width))) { // Top wall
				this->map->getCellAtPos(posX, posY)->setCellStructure("###------");
				for (int i = 0; i < 5; i++) {
					this->map->getCellAtPos(posX, posY)->subCell_grid[0][i] = new Wall(0, i);
				}
				for (int i = 0; i < 5; i++) {
					for (int j = 1; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
			else if (posX == this->x && (posY != this->y || posY != (this->y + this->height))) {// Left Wall
				this->map->getCellAtPos(posX, posY)->setCellStructure("#--#--#--");
				for (int i = 0; i < 5; i++) {
					this->map->getCellAtPos(posX, posY)->subCell_grid[i][0] = new Wall(i, 0);
				}
				for (int i = 1; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
			else if (posY == (this->y + this->height) && (posX != this->x || posX != (this->x + this->width))) {// Bottom wall
				this->map->getCellAtPos(posX, posY)->setCellStructure("------###");
				for (int i = 0; i < 5; i++) {
					this->map->getCellAtPos(posX, posY)->subCell_grid[4][i] = new Wall(4, i);
				}
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 4; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
			else if (posX == (this->x + this->width) && (posY != this->y || posY != (this->y + this->height))) {// Right wall
				this->map->getCellAtPos(posX, posY)->setCellStructure("--#--#--#");
				for (int i = 0; i < 5; i++) {
					this->map->getCellAtPos(posX, posY)->subCell_grid[i][4] = new Wall(i, 4);
				}
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
			// Else, construct middle room
			else {
				this->map->getCellAtPos(posX, posY)->setCellStructure("---------");
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						this->map->getCellAtPos(posX, posY)->subCell_grid[j][i] = new Floor(j, i);
					}
				}
			}
		}
	}

	int doorSide = this->randomizer.randomizeInRange(0,4,this->id);
	
	for (int i = 0; i < 4; i++) {
		if (this->doorIsValid()) {
			int chestOffset = 0; //Random number for space from wall
			switch (doorSide) {
			case UP:
				cout << "loot on top wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->width + 1, i);
				if (this->chestIsValid()) {
					this->map->getCellAtPos(this->x + chestOffset, this->y)->setCellStructure("lllllllll");
					this->map->getCellAtPos(this->x + chestOffset, this->y)->subCell_grid[1][2/* Put random numbers here */] = new Chest(this->id, 0, 0);
					i = 10;
					break;
				}
			case LEFT:
				cout << "loot on left wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->height + 1, i);
				if (this->chestIsValid()) {
					this->map->getCellAtPos(this->x, this->y + chestOffset)->setCellStructure("lllllllll");
					this->map->getCellAtPos(this->x, this->y + chestOffset)->subCell_grid[2][1/* Put random numbers here */] = new Chest(this->id, 0, 0);
					i = 10;
					break;
				}
			case DOWN:
				cout << "loot on bottom wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->width + 1, i);
				if (this->chestIsValid()) {
					this->map->getCellAtPos(this->x + chestOffset, this->y + this->height)->setCellStructure("lllllllll");
					this->map->getCellAtPos(this->x + chestOffset, this->y + this->height)->subCell_grid[Cell::gridSize - 1][2/* Put random numbers here */] = new Chest(this->id, 0, 0);
					i = 10;
					break;
				}
			case RIGHT:
				cout << "loot on right wall" << endl;
				chestOffset = this->randomizer.randomizeInRange(0, this->height + 1, i);
				if (this->chestIsValid()) {
					this->map->getCellAtPos(this->x + this->width, this->y + chestOffset)->setCellStructure("lllllllll");
					this->map->getCellAtPos(this->x + this->width, this->y + chestOffset)->subCell_grid[2][Cell::gridSize - 1/* Put random numbers here */] = new Chest(this->id, 0, 0);
					i = 10;
					break;
				}
			default:
				cout << "Room side is not between 0 and 3." << endl;
			}
		}
	}


	//Code for labeling the rooms by type with a character.
	string cell;
	cell += "////";	cell += letter;	cell += "////";
	this->map->getCellAtPos(this->x + this->width / 2, this->y + this->height / 2)->setCellStructure(cell);

	buildDoors();
}

Room_loot::~Room_loot(){
	Room_loot::lootRooms.pop_back();
}

bool Room_loot::chestIsValid() {
	return true;
}

void Room_loot::printType() {
	string roomtype = typeid(this->rooms[this->id]).name();
	cout << "This room is of type: " << roomtype << endl;
}

vector<Room_loot*> Room_loot::lootRooms;