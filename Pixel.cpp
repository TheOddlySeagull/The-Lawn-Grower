#include "Pixel.hpp"

// Constructors

Pixel::Pixel()
{
    red = 0;
    green = 0;
    blue = 0;
}

Pixel::Pixel(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
}

Pixel::Pixel(const Pixel &p)
{
    red = p.red;
    green = p.green;
    blue = p.blue;
}

// Getters

const int Pixel::getRed()
{
    return red;
}

const int Pixel::getGreen()
{
    return green;
}

const int Pixel::getBlue()
{
    return blue;
}

// Setters

void Pixel::setRed(int r)
{
    red = r;
}

void Pixel::setGreen(int g)
{
    green = g;
}

void Pixel::setBlue(int b)
{
    blue = b;
}

void Pixel::setColor(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
}

// Methods
void Pixel::darken(double factor)
{
    red = (int)(red * factor);
    green = (int)(green * factor);
    blue = (int)(blue * factor);
}
Pixel Pixel::getDarkened(double factor)
{
    return Pixel((int)(red * factor), (int)(green * factor), (int)(blue * factor));
}

// operator
Pixel Pixel::operator*(const double &d)
{
    return Pixel((int)(red * d), (int)(green * d), (int)(blue * d));
}
bool Pixel::operator==(const Pixel &p)
{
    return (red == p.red && green == p.green && blue == p.blue);
}
bool Pixel::operator!=(const Pixel &p)
{
    return (red != p.red || green != p.green || blue != p.blue);
}
std::ostream &operator<<(std::ostream &os, const Pixel &p)
{
    os << "(" << p.red << ", " << p.green << ", " << p.blue << ") \033[48;2;" << p.red << ";" << p.green << ";" << p.blue << "m  \033[0m";
    return os;
}

