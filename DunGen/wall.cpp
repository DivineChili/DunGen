#include "stdafx.h"
#include "wall.h"


Wall::Wall(int posX, int posY):
	SubCell(posX, posY){

	this->type = '#';
}


Wall::~Wall(){
}
