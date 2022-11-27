#pragma once
#include "../Primitives/DrawingObject.h"
#include "Wall.h"

#include <vector>

using namespace std;


class Creature :
    public DrawingObject
{
protected:

    float speed;   // px per tick

    float size;

 public:

    bool view[4][4];  
     
    int direction;  // in degrees

    bool canMove(int direction) const;

    void move();

    virtual void moveBy(double x, double y) = 0;

    void updateView(const Wall* wall);
};