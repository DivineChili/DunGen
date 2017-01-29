#include "stdafx.h"
#include "item_food.h"

Item_food::Item_food(int amount, int foodValue):
	Item(amount),
	foodValue(foodValue){
}

void Item_food::eat() {
	//Eat the food, use foodValue for the amount of healing.
}

Item_food::~Item_food()
{
}
