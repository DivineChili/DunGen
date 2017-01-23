#include "stdafx.h"
#include "subcell_loot.h"


SubCell_loot::SubCell_loot(int posX, int posY) :
	SubCell::SubCell(posX, posY){

	this->type = 'l';
}


SubCell_loot::~SubCell_loot(){
}
