#include <iostream>

#include "Canvas.hpp"

#pragma once

class Point
{
public:
    int x;
    int y;
    
    // Constructors
    Point();
    Point(int _x, int _y);
    ~Point();

    // Methods
    void insureWithinBounds(Canvas &img);
    void insureWithinBounds(int width, int height);

    // Operators
    bool operator==(const Point &p);
    bool operator!=(const Point &p);
    friend std::ostream &operator<<(std::ostream &os, const Point &p);
    friend std::istream &operator>>(std::istream &is, Point &p);
    Point operator+(const Point &p);
    Point operator-(const Point &p);
    Point operator*(const double &d);
    Point operator/(const double &d);

};
