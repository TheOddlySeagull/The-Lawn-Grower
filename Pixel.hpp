#include <iostream>

#pragma once

class Pixel
{
private:
    // Create 3 ints for each color
    int red;
    int green;
    int blue;

public:
    // Constructors
    Pixel();
    Pixel(int r, int g, int b);
    Pixel(const Pixel &p);

    // Getters
    const int getRed();
    const int getGreen();
    const int getBlue();

    // Setters
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    void setColor(int r, int g, int b);

    // Methods
    void darken(double factor);
    Pixel getDarkened(double factor);

    // operators
    Pixel operator*(const double &d);
    Pixel operator+(const Pixel &p);
    bool operator==(const Pixel &p);
    bool operator!=(const Pixel &p);
    friend std::ostream &operator<<(std::ostream &os, const Pixel &p);
};



