#pragma once

#include <string>
#include <vector>

using namespace std;

class SubCell{
protected:
	char type;
	int posX;
	int posY;
public:
	//These are all the existing SubCells
	static vector<SubCell*> subCells;
	SubCell();
	SubCell(int posX, int posY);
	~SubCell();
	char getChar();
};

