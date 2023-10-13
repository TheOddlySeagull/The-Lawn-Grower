#include "Color.hpp"

// Constructors

Color::Color()
{
    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
}

Color::Color(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
    alpha = 0;
}

Color::Color(int r, int g, int b, int a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

Color::~Color()
{
}

// Getters

const int Color::getRed()
{
    return red;
}

const int Color::getGreen()
{
    return green;
}

const int Color::getBlue()
{
    return blue;
}

const int Color::getAlpha()
{
    return alpha;
}

// Setters

void Color::setRed(int r)
{
    red = r;
}

void Color::setGreen(int g)
{
    green = g;
}

void Color::setBlue(int b)
{
    blue = b;
}

void Color::setAlpha(int a)
{
    alpha = a;
}

void Color::setColor(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
}

void Color::setColor(int r, int g, int b, int a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

// Methods

void Color::darken(double factor)
{
    red = (int)(red * factor);
    green = (int)(green * factor);
    blue = (int)(blue * factor);
}

Color Color::getDarkened(double factor)
{
    return Color((int)(red * factor), (int)(green * factor), (int)(blue * factor));
}

// Operators

Color Color::operator+(const Color &c)
{
    return Color(red + c.red, green + c.green, blue + c.blue, alpha + c.alpha);
}

Color Color::operator-(const Color &c)
{
    return Color(red - c.red, green - c.green, blue - c.blue, alpha - c.alpha);
}

Color Color::operator*(const Color &c)
{
    return Color(red * c.red, green * c.green, blue * c.blue, alpha * c.alpha);
}

Color Color::operator/(const Color &c)
{
    return Color(red / c.red, green / c.green, blue / c.blue, alpha / c.alpha);
}

Color Color::operator%(const Color &c)
{
    return Color(red % c.red, green % c.green, blue % c.blue, alpha % c.alpha);
}

Color Color::operator+=(const Color &c)
{
    red += c.red;
    green += c.green;
    blue += c.blue;
    alpha += c.alpha;
    return *this;
}

Color Color::operator-=(const Color &c)
{
    red -= c.red;
    green -= c.green;
    blue -= c.blue;
    alpha -= c.alpha;
    return *this;
}

Color Color::operator*=(const Color &c)
{
    red *= c.red;
    green *= c.green;
    blue *= c.blue;
    alpha *= c.alpha;
    return *this;
}

Color Color::operator/=(const Color &c)
{
    red /= c.red;
    green /= c.green;
    blue /= c.blue;
    alpha /= c.alpha;
    return *this;
}

Color Color::operator%=(const Color &c)
{
    red %= c.red;
    green %= c.green;
    blue %= c.blue;
    alpha %= c.alpha;
    return *this;
}

bool Color::operator==(const Color &c)
{
    return (red == c.red && green == c.green && blue == c.blue && alpha == c.alpha);
}

bool Color::operator!=(const Color &c)
{
    return (red != c.red || green != c.green || blue != c.blue || alpha != c.alpha);
}

std::ostream &operator<<(std::ostream &os, const Color &c)
{
    os << "(" << c.red << ", " << c.green << ", " << c.blue << ") \033[48;2;" << c.red << ";" << c.green << ";" << c.blue << "m  \033[0m";
    return os;
}

Color Color::operator*(const double &d)
{
    return Color((int)(red * d), (int)(green * d), (int)(blue * d), (int)(alpha * d));
}


//Tests

bool Color::isBlack()
{
    return (red == 0 && green == 0 && blue == 0);
}