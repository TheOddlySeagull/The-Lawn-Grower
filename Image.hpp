#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Pixel.hpp"
#include "Point.hpp"

#pragma once

class Image
{
private:
    int width;
    int height;
    Pixel *pixels;

    Point makePointRep(Point pos);
    void floodRepPixelHelper(Pixel filler, Pixel replaced, Point pos, std::vector<Point> &points);
public:
    // Constructors
    Image();
    Image(int w, int h);
    ~Image();

    // Getters
    const int getWidth();
    const int getHeight();
    Pixel *getPixels();
    Pixel getPixel(Point pos);

    // Setters
    void updateImageWidth(int w);
    void updateImageHeight(int h);

    // Pixel Methods
    void setRepPixel(Pixel p, Point pos);
    void setNoRepPixel(Pixel p, Point pos);
    void replaceRepPixel(Pixel replacement, Pixel replaced, Point pos);
    void replaceNoRepPixel(Pixel replacement, Pixel replaced, Point pos);
    void oldFloodRepPixel(Pixel filler, Point pos);
    void floodRepPixel(Pixel filler, Point pos);
    void floodNoRepPixel(Pixel filler, Point pos);

    // Methods
    void exportImage(std::string filename, int width_repititions, int height_repititions);

};
