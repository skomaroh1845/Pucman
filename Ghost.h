#pragma once

#include "../Primitives/Primitives.h"
#include "Creature.h"
#include "Pucman.h"
#include "Wall.h"
#include <vector>

// Enemy class
class Ghost : 
	public Creature
{
	circle eye[2];
	circle pupil[2];
	circle head;
	rectangle body;
	circle skirt[7];

	bool skirtFlag;
	int animationTimer;

	static T playerPos;

public:

	Ghost() = delete;

	Ghost(const T& center, float size, float r = 1, float g = 1, float b = 1);
	
	void print() const override;

	void moveBy(double x, double y) override;

	void moveTo(double x, double y) override;

	void rotate(double angle) override;  // only 0, 90, 180, 270 

	void animate(float speed = 1) override;

	static void getPlayerPos(const Pucman& P);

	void chooseDirection(const vector<Wall*>& objs);
};

