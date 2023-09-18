#include <iostream>
#include <fstream>
#include "Pixel.hpp"

#pragma once

class Canvas
{
private:
    int width;
    int height;
    int scale;
    Pixel *pixels;
public:
    // Constructors
    Canvas();
    Canvas(int w, int h, int scale);
    ~Canvas();

    // Getters
    const int getWidth();
    const int getHeight();
    Pixel *getPixels();
    Pixel getPixel(int w, int h);

    // Setters
    void setWidth(int w);
    void setHeight(int h);
    void setPixel(Pixel p, int w, int h);
    void replacePixel(Pixel replacement, Pixel replaced, int w, int h);
    void setNoRepPixel(Pixel p, int w, int h, bool vertical, bool horizontal);
    void setScale(int s);

    // Procedure to export image
    void exportImage(std::string filename, int width_repititions, int height_repititions);

    // Procedure to return scale
    int getScale();

};
