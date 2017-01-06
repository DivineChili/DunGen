#include "stdafx.h"
#include "subcell.h"
#include <vector>

vector<SubCell*> SubCell::subCells;

SubCell::SubCell(){
	this->type = 'k';
	this->subCells.push_back(this);
}


SubCell::~SubCell(){
}

char SubCell::getChar() {
	return this->type;
}
