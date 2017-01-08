#include "stdafx.h"
#include "subcell.h"
#include <vector>
#include <iostream>

using namespace std;

vector<SubCell*> SubCell::subCells;

SubCell::SubCell() {
	//cout << "called without arguments" << endl;
	cout << "type " << this->type << endl;
}

SubCell::SubCell(int posX, int posY) :
	posX(posX), posY(posY), type('f') {
	//cout << "type " << this->type << endl;
	//cout << "called with arguments" << endl;
	this->subCells.push_back(this);
}


SubCell::~SubCell(){
}

char SubCell::getChar() {
	return this->type;
}
