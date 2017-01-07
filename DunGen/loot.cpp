#include "stdafx.h"
#include "loot.h"


Loot::Loot(int posX, int posY) :
	SubCell::SubCell(posX, posY){

	this->type = 'l';
}


Loot::~Loot(){
}
