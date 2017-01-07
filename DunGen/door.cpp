#include "stdafx.h"
#include "door.h"
#include <vector>

vector<Door*> Door::doors;

Door::Door(){
	doors.push_back(this);
}


Door::~Door()
{
}
