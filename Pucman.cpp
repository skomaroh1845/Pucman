#include "Pucman.h"
#include "../Primitives/Primitives.h"


Pucman::Pucman(const T& center, float size) : score(0), lives(3),
		body(circle(center, size, 1, 1, 0)), eye(circle(T(center.x, center.y + size/2), 2, 0, 0, 0)),
		up(false), down(false), right(true), left(false), angle1(45), angle2(360-45), mouth_open(false)
{
}

void Pucman::print() const
{
	body.print(angle1, angle2);
	eye.print();
}

void Pucman::moveBy(double x, double y)
{
	body.moveBy(x, y);
	eye.moveBy(x, y);
}

void Pucman::moveTo(double x, double y)
{
	body.moveTo(x, y);

	if (right || left)
		eye.moveTo(x, y + body.R / 2);
	else 
		eye.moveTo(x - body.R / 2, y);
}

void Pucman::rotate(double angle)
{
	if (angle == 90) {
		up = true; down = false; right = false; left = false;
		eye.moveTo(body.getCenter().x - body.R / 2, body.getCenter().y);
	}
	if (angle == 0) {
		up = false; down = false; right = true; left = false;
		eye.moveTo(body.getCenter().x, body.getCenter().y + body.R / 2);
	}
	if (angle == 180) {
		up = false; down = false; right = false; left = true;
		eye.moveTo(body.getCenter().x, body.getCenter().y + body.R / 2);
	}
	if (angle == 270) {
		up = false; down = true; right = false; left = false;
		eye.moveTo(body.getCenter().x - body.R / 2, body.getCenter().y);
	}
	angle1 = angle + 45;
	angle2 = angle - 45;
}

void Pucman::animate(float speed)
{
	if (mouth_open) 
	{
		angle1 += speed * 2;
		angle2 -= speed * 2;
		if (angle2 - angle1 < 270) mouth_open = false;
	} else {
		angle1 -= speed * 2;
		angle2 += speed * 2;
		if (angle2 - angle1 > 359) mouth_open = true;
	}
}

void Pucman::death()
{
}
