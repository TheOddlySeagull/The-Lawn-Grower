#ifndef _CANVAS
#define _CANVAS

#include <iostream>
#include <fstream>

#include "Image.hpp"

class Canvas : public Image
{
private:
    int scale;
public:
    // Constructors
    Canvas();
    Canvas(int w, int h, int scale);
    Canvas(const Canvas &other);
    ~Canvas();

    // Getters
    int getScale() const;

    // Setters
    void setScale(int s);

};

#endif