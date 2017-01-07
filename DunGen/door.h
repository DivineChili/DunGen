#pragma once
#include "subcell.h"
#include <vector>

class Door : public SubCell {
public:
	static vector<Door*> doors;
	Door();
	virtual ~Door();
};

