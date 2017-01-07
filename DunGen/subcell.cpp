#include "stdafx.h"
#include "subcell.h"
#include <vector>
#include <iostream>

using namespace std;

vector<SubCell*> SubCell::subCells;

SubCell::SubCell() {
	cout << "called without arguments" << endl;
}

SubCell::SubCell(int posX, int posY) :
	posX(posX), posY(posY), type('k') {

	cout << "called with arguments" << endl;
	this->subCells.push_back(this);
}


SubCell::~SubCell(){
}

char SubCell::getChar() {
	return this->type;
}
