#pragma once

#include <string>
#include <vector>

using namespace std;

class SubCell{
private:
	char type;
public:
	//These are all the existing SubCells
	static vector<SubCell*> subCells;
	SubCell();
	~SubCell();
	char getChar();
};

