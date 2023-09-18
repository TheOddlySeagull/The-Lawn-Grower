#include "point.hpp"

//----------------------------------------------------------------------------------------------------
// Constructors and Destructors
//----------------------------------------------------------------------------------------------------

Point::Point()
{
    this->x = 0;
    this->y = 0;
}
Point::Point(int _x, int _y)
{
    this->x = _x;
    this->y = _y;
}
Point::~Point()
{
}

//----------------------------------------------------------------------------------------------------
// Methods
//----------------------------------------------------------------------------------------------------

/**
 * @brief Makes sure the point is within the bounds of the canvas
 * 
 * @param img The canvas to insure the point is within (Canvas object)
 */
void Point::insureWithinBounds(Canvas &img)
{
    this->x = this->x % img.getWidth();
    this->y = this->y % img.getHeight();

    if (this->x < 0)
    {
        this->x += img.getWidth();
    }
    if (this->y < 0)
    {
        this->y += img.getHeight();
    }
}

//----------------------------------------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------------------------------------

bool Point::operator==(const Point &p)
{
    return (this->x == p.x && this->y == p.y);
}
bool Point::operator!=(const Point &p)
{
    return (this->x != p.x || this->y != p.y);
}
std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
std::istream &operator>>(std::istream &is, Point &p)
{
    is >> p.x >> p.y;
    return is;
}
Point Point::operator+(const Point &p)
{
    Point temp;
    temp.x = this->x + p.x;
    temp.y = this->y + p.y;
    return temp;
}
Point Point::operator-(const Point &p)
{
    Point temp;
    temp.x = this->x - p.x;
    temp.y = this->y - p.y;
    return temp;
}
Point Point::operator*(const double &d)
{
    Point temp;
    temp.x = this->x * d;
    temp.y = this->y * d;
    return temp;
}
Point Point::operator/(const double &d)
{
    Point temp;
    temp.x = this->x / d;
    temp.y = this->y / d;
    return temp;
}