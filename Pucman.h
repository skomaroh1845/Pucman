#pragma once

#include "../Primitives/DrawingObject.h"
#include "../Primitives/Primitives.h"


// Player class
class Pucman: 
	public DrawingObject
{
	circle body;
	circle eye;

	bool up, down, right, left;  // direction

	int score;
	int lives;

	float angle1, angle2;  // used for animation
	bool mouth_open; 

public:
	Pucman(const T& center, float size);

	void print() const override;

	void moveBy(double x, double y) override;

	void moveTo(double x, double y) override;

	void rotate(double angle) override;  // only 0, 90, 180, 270 

	void animate(float speed = 1);

	void death();
};

