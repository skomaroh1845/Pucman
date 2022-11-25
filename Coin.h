#pragma once

#include "../Primitives/Primitives.h"
#include "../Primitives/Vector2D.h"

class Coin :
    public circle
{
    T center;
    
    float y0;       // used for animation
    float y_max;
    float y_min;
    bool move_up;  

    float R;
    circle C[2];
public:
    Coin(const T& center, float R, bool up = 1);

    void print() const override;

    void animate(float speed = 1) override;  // speed = px / tick
};

