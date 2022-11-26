#pragma once

#include "../Primitives/Primitives.h"
#include "Creature.h"

using namespace std;

// Player class
class Pucman: 
	public Creature
{
	circle body;
	circle mouth;
	circle eye;

	float angle;  // used for animation
	bool mouth_open; 

	int score;
	int lives;	

public:
	Pucman(const T& center, float size);

	void print() const override;

	void moveBy(double x, double y) override;

	void moveTo(double x, double y) override;

	void rotate(double angle) override;  // only 0, 90, 180, 270 

	void animate(float speed = 1) override;
	
	void death();
};

