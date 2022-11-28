#include "Ghost.h"
#include "../Primitives/Vector2D.h"
#include <algorithm>

using namespace std;

T Ghost::playerPos = T(0, 0);

Ghost::Ghost(const T& center, float size, float r, float g, float b) : 
		head(center, size, r, g, b), body(T(center.x, center.y - size/4), size*2, size/2, r, g, b),
		skirtFlag(rand() % 2), animationTimer(25), grad(T(-1, 1)), chooseTimer(20)
{
	speed = 0.7;
	direction = 0;
	lastDir = direction;
	decisionFlag = true;
	this->size = size;
	setColor(r, g, b);
	setCenter(center);

	// init graphic
	float eyeSize = size / 3;
	eye[0] = circle(T(center.x + size / 2, center.y + size / 4), eyeSize);
	eye[1] = circle(T(center.x - size / 2, center.y + size / 4), eyeSize);

	float pupilSize = eyeSize / 2;
	pupil[0] = circle(T(center.x + size / 2 + pupilSize, center.y + size / 4), pupilSize, 0, 0, 0);
	pupil[1] = circle(T(center.x - size / 2 + pupilSize, center.y + size / 4), pupilSize, 0, 0, 0);

	float skirtSize = size / 3;
	skirt[0] = circle(T(center.x - skirtSize*2, center.y - size/2), skirtSize, r, g, b);
	skirt[1] = circle(T(center.x, center.y - size / 2), skirtSize, r, g, b);
	skirt[2] = circle(T(center.x + skirtSize*2, center.y - size / 2), skirtSize, r, g, b);

	skirt[3] = circle(T(center.x - size, center.y - size / 2), skirtSize, r, g, b);
	skirt[4] = circle(T(center.x - skirtSize, center.y - size / 2), skirtSize, r, g, b);
	skirt[5] = circle(T(center.x + skirtSize, center.y - size / 2), skirtSize, r, g, b);
	skirt[6] = circle(T(center.x + size, center.y - size / 2), skirtSize, r, g, b);
}

void Ghost::print() const
{
	head.print(0, 180);
	body.print();
	eye[0].print();
	eye[1].print();
	pupil[0].print();
	pupil[1].print();

	if (skirtFlag) {
		skirt[0].print(180, 360);
		skirt[1].print(180, 360);
		skirt[2].print(180, 360);
	} else {
		skirt[3].print(270, 360);
		skirt[4].print(180, 360);
		skirt[5].print(180, 360);
		skirt[6].print(180, 270);
	}
}

void Ghost::moveBy(double x, double y)
{
	head.moveBy(x, y);
	body.moveBy(x, y);
	eye[0].moveBy(x, y);
	eye[1].moveBy(x, y);
	pupil[0].moveBy(x, y);
	pupil[1].moveBy(x, y);
	skirt[0].moveBy(x, y);
	skirt[1].moveBy(x, y);
	skirt[2].moveBy(x, y);
	skirt[3].moveBy(x, y);
	skirt[4].moveBy(x, y);
	skirt[5].moveBy(x, y);
	skirt[6].moveBy(x, y);
	setCenter(T(getCenter().x + x, getCenter().y + y));
}

void Ghost::moveTo(double x, double y)
{
	head.moveTo(x, y);
	body.moveTo(x, y);
	setCenter(T(x, y));
	skirt[0].moveTo(x - skirt[0].R * 2, y - head.R / 2);
	skirt[1].moveTo(x, getCenter().y - head.R / 2);
	skirt[2].moveTo(x + skirt[2].R * 2, y - head.R / 2);
	
	skirt[3].moveTo(x - head.R, y - head.R / 2);
	skirt[4].moveTo(x - skirt[4].R, y - head.R / 2);
	skirt[5].moveTo(x - skirt[4].R, y - head.R / 2);
	skirt[6].moveTo(x + head.R, y - head.R / 2);

	eye[0].moveTo(x + head.R / 2, y + head.R / 4);
	eye[1].moveTo(x - head.R / 2, y + head.R / 4);

	pupil[0].moveTo(x + head.R / 2 + pupil[0].R * cos(direction * 3.14 / 180), 
					y + head.R / 4 + pupil[0].R * sin(direction * 3.14 / 180));
	pupil[1].moveTo(x - head.R / 2 + pupil[1].R * cos(direction * 3.14 / 180),
					y + head.R / 4 + pupil[1].R * sin(direction * 3.14 / 180));
}

void Ghost::rotate(double angle)
{
	lastDir = ( int(angle) + 180 ) % 360;
	direction = int(angle);
	pupil[0].moveTo(getCenter().x + head.R / 2 + pupil[0].R * cos(direction * 3.14 / 180),
					getCenter().y + head.R / 4 + pupil[0].R * sin(direction * 3.14 / 180));
	pupil[1].moveTo(getCenter().x - head.R / 2 + pupil[1].R * cos(direction * 3.14 / 180),
					getCenter().y + head.R / 4 + pupil[1].R * sin(direction * 3.14 / 180));
}

void Ghost::animate(float speed)
{
	if (animationTimer > 0) --animationTimer;
	else {
		animationTimer = 25;
		skirtFlag = !skirtFlag;
	}
}

void Ghost::chooseDirection()
{
	--chooseTimer;
	if (it_is_corner() && chooseTimer < 0)
	{
		chooseTimer = 20;
		T _grad = (playerPos - getCenter()) / (playerPos - getCenter()).length();
		
		if (grad * _grad < 0.8 ) 
			grad = _grad;
		
		if (decisionFlag && brainMod)
		{
			decisionFlag = false;
			rotate(checkDirection());
		}
		else
		{
			decisionFlag = true;
			rotate( (rand() % 4) * 90 );
		}
	}
}

int Ghost::checkDirection() const
{
	// compute new direction
	T _grad = grad;  // copy of gradient to player pos
	int direction;   // temporary direction 
	bool toGrad = true;

	vector<int> dirs = { 0, 90, 180, 270 };  // list of posible directions (in radians)

	for (int i = 0; i < 3; ++i)
	{
		if (abs(_grad.x) > abs(_grad.y)) {
			if (_grad.x < 0)
			{
				direction = 180;
				dirs.erase( find(dirs.begin(), dirs.end(), 180) );
			}
			else
			{
				direction = 0;
				dirs.erase( find(dirs.begin(), dirs.end(), 0) );
			}
			_grad.x = 0;
		}
		else if (abs(_grad.y) > abs(_grad.x)) 
		{
				if (_grad.y > 0)
				{
					direction = 90;
					dirs.erase( find(dirs.begin(), dirs.end(), 90) );
				}
				else
				{
					direction = 270;
					dirs.erase( find(dirs.begin(), dirs.end(), 270) );
				}
				_grad.y = 0;
		} 
		else 
		{
			toGrad = false;
			T v1(cos(dirs[0] * 3.14 / 180), sin(dirs[0] * 3.14 / 180));
			T v2(cos(dirs[1] * 3.14 / 180), sin(dirs[1] * 3.14 / 180));

			if ( (v1 * grad) / (v2 * grad) < 1 ) 
			{
				direction = dirs[1];
				dirs.erase( dirs.begin() + 1 );
			}
			else 
			{
				direction = dirs[0];
				dirs.erase( dirs.begin() );
			}				
		}

		if (canMove(direction)) {
			if ( toGrad || direction != lastDir )
			{
				return direction;
			}
			else {
				if (canMove(dirs[0]))
					return dirs[0];
				else
					return direction;
			}
		}
	}
	return dirs[0];
}

bool Ghost::it_is_corner() const
{
	

	if ( canMove( (direction + 90)%360 ) ) return true;
	if ( canMove( (direction + 270)%360 ) ) return true;
	return false;
}
