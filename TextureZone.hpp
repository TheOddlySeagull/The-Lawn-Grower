#include <iostream>

#include "Point.hpp"
#include "Canvas.hpp"

#pragma once

class TextureZone
{
private:
    Point top_left;
    Point bottom_right;

public:
    TextureZone(Point top_left, Point bottom_right);
    ~TextureZone();

    Point GetRandomAvailablePosition(Canvas *img);
    int GetRandomHeight(float factor);

    int GetSurfaceArea();
};
