#include "stdafx.h"
#include "item.h"

using namespace std;

Item::Item(int amount) : amount(amount) {}
Item::Item() {
	cout << "default constructor!!!" << endl;
}
void Item::drop() {
	//drops the item on the ground
}

Item::~Item()
{
}
