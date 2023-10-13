#ifndef _COLOR
#define _COLOR

#include <iostream>

class Color
{
private:
    int red;
    int green;
    int blue;
    int alpha;

public:
    // Constructors
    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    ~Color();

    // Getters
    const int getRed();
    const int getGreen();
    const int getBlue();
    const int getAlpha();

    // Setters
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    void setAlpha(int a);

    void setColor(int r, int g, int b);
    void setColor(int r, int g, int b, int a);

    // Methods
    void darken(double factor);
    Color getDarkened(double factor);
    
    // Operators
    Color operator+(const Color &c);
    Color operator-(const Color &c);
    Color operator*(const Color &c);
    Color operator/(const Color &c);
    Color operator%(const Color &c);
    Color operator+=(const Color &c);
    Color operator-=(const Color &c);
    Color operator*=(const Color &c);
    Color operator/=(const Color &c);
    Color operator%=(const Color &c);
    bool operator==(const Color &c);
    bool operator!=(const Color &c);

    friend std::ostream &operator<<(std::ostream &os, const Color &c);

    Color operator*(const double &d);

    //Tests
    bool isBlack();
};

#endif
