#include "stdafx.h"
#include "subcell.h"
#include <vector>
#include <iostream>

using namespace std;

vector<SubCell*> SubCell::subCells;

SubCell::SubCell() {
	cout << "SubCell created without arguments. type: " << this->type << endl;
}

SubCell::SubCell(int posX, int posY) :
	posX(posX), posY(posY), type(' ') {
	this->subCells.push_back(this);
}


SubCell::~SubCell(){
}

char SubCell::getChar() {
	return this->type;
}
