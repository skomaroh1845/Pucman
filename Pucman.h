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

	int turnDirection;

	int damageTimer;  // while timer > 0 pucman takes no damage

	bool deathFlag;

	struct P {
		float x;
		float y;
		float vx;
		float vy;
		float R;
		float G;
		float B;
	}* particles;

public:

	Pucman(const T& center, float size);

	~Pucman();

	void print() const override;

	void moveBy(double x, double y) override;

	void moveTo(double x, double y) override;

	void rotate(double angle) override;  // only 0, 90, 180, 270 

	void animate(float speed = 1) override;
	
	void setTurnDirection(int direction);

	void turn();

	bool death();   // draw explosion

	bool canTakeDamage() const;  // if damage timer run out when returns true, else - false

	void takeDamage();  // starts damage timer
};

