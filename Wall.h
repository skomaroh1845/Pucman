#pragma once
#include "../Primitives/Primitives.h"

class Wall :
    public rectangle
{
    rectangle R;
public:

    Wall(const T& center, float sizeX, float sizeY, float r, float g, float b);
    
    void print() const override;

    float getSizeX() const;

    float getSizeY() const;
};

