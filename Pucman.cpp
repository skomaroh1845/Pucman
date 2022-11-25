#include "Pucman.h"
#include "../Primitives/Primitives.h"


Pucman::Pucman(const T& center, float size) : score(0), lives(3),
		body(circle(center, size, 1, 1, 0)), eye(circle(T(center.x, center.y + size/2), 2, 0, 0, 0)),
		mouth(circle(center, size, 0, 0, 0)), direction(0), angle(45), mouth_open(false), speed(1)
{
	setCenter(center);
}

void Pucman::print() const
{
	body.print();
	mouth.print(direction - angle, direction + angle);
	eye.print();
}

void Pucman::moveBy(double x, double y)
{
	body.moveBy(x, y);
	mouth.moveBy(x, y);
	eye.moveBy(x, y);
	setCenter( T( getCenter().x + x, getCenter().y + y ) );
}

void Pucman::moveTo(double x, double y)
{
	body.moveTo(x, y);
	mouth.moveTo(x, y);
	if (direction % 180 == 0)
		eye.moveTo(x, y + body.R / 2);
	else 
		eye.moveTo(x - body.R / 2, y);
	setCenter(T(x, y));
}

void Pucman::rotate(double angle)
{
	if (angle == 0) {
		eye.moveTo(body.getCenter().x, body.getCenter().y + body.R / 2);
	} else if (angle == 180) {
		eye.moveTo(body.getCenter().x, body.getCenter().y + body.R / 2);
	} else if (angle == 90) {
		eye.moveTo(body.getCenter().x - body.R / 2, body.getCenter().y);
	} else if (angle == 270) {
		eye.moveTo(body.getCenter().x - body.R / 2, body.getCenter().y);
	}
	direction = angle;
}

void Pucman::animate(float speed)
{
	if (mouth_open) 
	{
		angle += speed * 2;
		if (angle > 45) mouth_open = false;
	} else {
		angle -= speed * 2;
		if (angle < speed * 2) mouth_open = true;
	}
}

void Pucman::move()
{
	moveBy(speed * cos(direction * 3.14 / 180), speed * sin(direction * 3.14 / 180));
}

void Pucman::death()
{
}
