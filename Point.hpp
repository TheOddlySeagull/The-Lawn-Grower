#ifndef _POINT
#define _POINT

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

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
    //void insureWithinBounds(Image &img);
    void insureWithinBounds(int width, int height);
    Point rotate(const Point &center, double angleRadians) const;

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

#endif
