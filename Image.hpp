#ifndef _IMAGE
#define _IMAGE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

#include "Pixel.hpp"
#include "Point.hpp"

class Image
{
protected:
    int width;
    int height;
    Pixel *pixels;

    void makePointRep(Point* pos);
    bool isPointInImage(Point pos);
    void floodRepPixelHelper(Pixel filler, Pixel replaced, Point pos, std::vector<Point> &points);
public:
    // Constructors
    Image();
    Image(int w, int h);
    Image(const Image &other);
    ~Image();

    // Getters
    int getWidth() const;
    int getHeight() const;

    // Pixel Getters
    Pixel getPixels() const;
    Pixel getPixel(Point pos) const;
    Pixel getPixel(int w, int h) const;

    // Pixel Methods
    void setRepPixel(Pixel p, Point* pos);
    void setNoRepPixel(Pixel p, Point pos);
    void replaceRepPixel(Pixel replacement, Pixel replaced, Point* pos);
    void replaceNoRepPixel(Pixel replacement, Pixel replaced, Point pos);
    void oldFloodRepPixel(Pixel filler, Point pos);
    void floodRepPixel(Pixel filler, Point pos);
    void floodNoRepPixel(Pixel filler, Point pos);

    // Image Methods
    void exportImage(std::string filename, int width_repititions, int height_repititions);
    void printImageConsole();

    // Color and noise
    void colorFilter(float amount);
    void addNoise(double noiseDensity, int noiseSpread, int noiseColorfulness, int noiseSaturation);

    // Drawing
    void drawLine(Pixel color, Point p1, Point p2, int thickness);
    void drawCurve(Pixel color, Point p1, Point p2, int offset);
    void drawCircle(Pixel color, Point center, int radius);
    void drawPartialEmptyCircle(int radius, double startAngle, double endAngle, Point center, Pixel color);
    void drawPartialCheeseWheel(int radius, double startAngle, double endAngle, Point center, Pixel color);
    void drawFilledCircleWithBorder(int radius, Point center, Pixel fillColor, Pixel borderColor);

    // Rotating
    void rotate(float angleDegrees);

    // Trimming
    void trim(int newWidth, int newHeight);

    //Scaling
    void scale(int new_scale);

    //Resize
    void resize(int new_width, int new_height);

    // Merging
    void merge(const Image &other);
    void merge(const Image &other, Point pos);
    void mergeExcept(const Image &other, const Image &except);
    void mergeExcept(const Image &other, const Image &except, Point pos);
    void mergeLayerRep(const Image &other, Point pos);
    void mergeLayerNoRep(const Image &other, Point pos);
    void expand(const Image &other);

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const Image &img);

};

#endif