#include "Wall.h"

Wall::Wall(const T& center, float sizeX, float sizeY, float r, float g, float b) : 
		R(rectangle(center, sizeX, sizeY, r, g, b))
{
}

void Wall::print() const
{
	R.print();
}

//void Wall::animate(float speed) 
//{
//}
