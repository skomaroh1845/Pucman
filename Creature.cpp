#include "Creature.h"

#include "../Primitives/DrawingObject.h"
#include "Wall.h"
#include <vector>

using namespace std;

bool Creature::canMove(const vector<Wall*>& objs) const
{
	for (Wall* el : objs) {

		if ((el->getCenter() - getCenter()).length() > distToWall * 2) continue;

		if (direction == 0 &&                        // move right
			el->getCenter().x > getCenter().x + el->getSizeX() / 2 + size &&     // check walls which are righter
			abs(el->getCenter().y - getCenter().y) < el->getSizeY() / 2 + size &&  // check walls on the same height
			el->getCenter().x - getCenter().x < el->getSizeX() / 2 + distToWall) // check how far are they
		{
			return false;
		}
		else if (direction == 180 &&
				el->getCenter().x + el->getSizeX() / 2 + size < getCenter().x &&
				abs(el->getCenter().y - getCenter().y) < el->getSizeY() / 2 + size &&
				getCenter().x - el->getCenter().x < el->getSizeX() / 2 + distToWall)
		{
			return false;
		}
		else if (direction == 90 &&
				el->getCenter().y > getCenter().y + el->getSizeY() / 2 + size &&
				abs(el->getCenter().x - getCenter().x) < el->getSizeX() / 2 + size &&
				el->getCenter().y - getCenter().y < el->getSizeY() / 2 + distToWall)
		{
			return false;
		}
		else if (direction == 270 &&
				el->getCenter().y + el->getSizeY() / 2 + size < getCenter().y &&
				abs(el->getCenter().x - getCenter().x) < el->getSizeX() / 2 + size &&
				getCenter().y - el->getCenter().y < el->getSizeY() / 2 + distToWall)
		{
			return false;
		}
	}
	return true;
}

void Creature::move()
{
	moveBy(speed * cos(direction * 3.14 / 180), speed * sin(direction * 3.14 / 180));
}

void Creature::moveBy(double x, double y)
{
}