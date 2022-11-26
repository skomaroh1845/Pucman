#pragma once
#include "../Primitives/DrawingObject.h"
#include "Wall.h"

#include <vector>

using namespace std;


class Creature :
    public DrawingObject
{
 public:   
     
    int direction;  // in degrees

    float speed;   // px per tick

    float distToWall; //

    float size;  

    bool canMove(const vector<Wall*>& objs) const;

    void move();

    void moveBy(double x, double y) override;
};