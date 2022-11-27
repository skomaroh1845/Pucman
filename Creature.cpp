#include "Creature.h"

#include "../Primitives/DrawingObject.h"
#include "Wall.h"
#include <vector>

using namespace std;

void Creature::updateView(const Wall* wall)
{
	auto chooseLine = [](const Wall* wall, float y) {

		if (wall->getCenter().y > y) 
		{
			if (wall->getCenter().y > y + wall->getSizeY() * 1.2)
				return 0;
			else
				return 1;
		}
		else
		{
			if (wall->getCenter().y < y - wall->getSizeY() * 1.2)
				return 3;
			else
				return 2;
		}
	};
	
	if (wall->getCenter().x < getCenter().x)  // 3 col
	{
		if (wall->getCenter().x < getCenter().x - wall->getSizeX() * 1.2)
			view[chooseLine(wall, getCenter().y)][0] = 1;
		else
			view[chooseLine(wall, getCenter().y)][1] = 1;
	}
	else
	{
		if (wall->getCenter().x > getCenter().x + wall->getSizeX() * 1.2)
			view[chooseLine(wall, getCenter().y)][3] = 1;
		else
			view[chooseLine(wall, getCenter().y)][2] = 1;
	}
}

bool Creature::canMove(int direction) const
{	
	if (direction == 0) 
	{
		if (view[1][3] || view[2][3])  // true = wall is seen
			return false;
		return true;
	} 
	else if (direction == 180) 
	{
		if (view[1][0] || view[2][0])  // true = wall is seen
			return false;
		return true;
	} 
	else if (direction == 90) 
	{
		if (view[0][1] || view[0][2])  // true = wall is seen
			return false;
		return true;
	}
	else 
	{
		if (view[3][1] || view[3][2])  // true = wall is seen
			return false;
		return true;
	}
}

void Creature::move()
{
	moveBy(speed * cos(direction * 3.14 / 180), speed * sin(direction * 3.14 / 180));
}