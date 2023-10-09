#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>

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
    Pixel getPixel(Point pos) const;

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
    Image clone() const;

    // Methods
    void exportImage(std::string filename, int width_repititions, int height_repititions);
    void printImageConsole();

    // Color and noise
    void darken(float amount);
    void addNoise(double noiseDensity, int noiseSpread, int noiseColorfulness, int noiseSaturation);

    // Drawing
    void drawLine(Pixel color, Point p1, Point p2, int thickness);
    void drawCurve(Pixel color, Point p1, Point p2, int offset);
    void drawCircle(Pixel color, Point center, int radius);

    // Rotate
    void rotate(float angleDegrees);
    void trim(int newWidth, int newHeight);

    // Merging
    void merge(const Image &other);

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const Image &img);

};
