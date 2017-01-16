#include "stdafx.h"
#include "floor.h"


Floor::Floor(int posX, int posY) :
	SubCell(posX, posY){

	this->type = '#';
}


Floor::~Floor()
{
}
