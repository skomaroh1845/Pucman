#include "Wall.h"

Wall::Wall(const T& center, float sizeX, float sizeY, float r, float g, float b) : 
		R(rectangle(center, sizeX, sizeY, r, g, b))
{
	setCenter(center);
}

void Wall::print() const
{
	R.print();
}

float Wall::getSizeX() const
{
	return R.sideSizeX;
}

float Wall::getSizeY() const
{
	return R.sideSizeY;
}