#include "Pucman.h"
#include "../Primitives/Primitives.h"
#include "Wall.h"

#include <vector>
#include <algorithm>
#include <glut.h>


Pucman::Pucman(const T& center, float size) : damageTimer(0), particles(nullptr), deathFlag(false),
		body(circle(center, size, 1, 1, 0)), eye(circle(T(center.x, center.y + size/2), size/5, 0, 0, 0)),
		mouth(circle(center, size, 0, 0, 0)), angle(45), mouth_open(false)
{
	setCenter(center);
	direction = 0;
	turnDirection = 0;
	speed = 1;
	this->size = size;
}

Pucman::~Pucman()
{
	if (particles != nullptr) {
		delete[] particles;
	}
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
	if (damageTimer > 0) 
	{
		--damageTimer;
		body.setColor((damageTimer % 10) / 10.0, (damageTimer%10) / 10.0, 0);
		if (damageTimer == 0)
			body.setColor(1, 1, 0);
	}
}

void Pucman::setTurnDirection(int direction)
{
	turnDirection = direction;
}

void Pucman::turn()
{
	if (direction != turnDirection && canMove(turnDirection))
		rotate(turnDirection);
}

bool Pucman::death()
{
	if (!deathFlag) {	// init particles
		deathFlag = true;
		particles = new P[500];
		for (int k = 0; k < 500; k++)
		{
			float z = (rand() % 1000 - 500) / 200.0;
			particles[k].vx = cos(3.141 * 2 * k / 500) * z;
			particles[k].vy = sin(3.141 * 2 * k / 500) * z;
			particles[k].x = getCenter().x;
			particles[k].y = getCenter().y;
			particles[k].R = rand() % 100 / 100.0;
			particles[k].G = rand() % 100 / 100.0;
			particles[k].B = rand() % 100 / 100.0;
		}
	}
	bool flag = true;

	// draw particles
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int k = 0; k < 500; k++)
	{
		glColor3f(particles[k].R, particles[k].G, particles[k].B);
		if (particles[k].vx != 0 || particles[k].vy != 0)
		{
			glVertex2f(particles[k].x, particles[k].y);
			flag = false;
		}
	}
	glEnd();

	// update particles
	for (int k = 0; k < 500; k++)
	{
		particles[k].x += particles[k].vx;
		particles[k].y += particles[k].vy;
		particles[k].vx = particles[k].vx / 1.05;
		particles[k].vy = particles[k].vy / 1.05;
		if ( abs(particles[k].vx) < 0.1 ) particles[k].vx = 0;
		if ( abs(particles[k].vy) < 0.1 ) particles[k].vy = 0;
	}

	return flag;  // true if where aren't particles
}

bool Pucman::canTakeDamage() const
{
	if (damageTimer > 0)
		return false;
	else 
		return true;
}

void Pucman::takeDamage()
{
	damageTimer = 100;
}
