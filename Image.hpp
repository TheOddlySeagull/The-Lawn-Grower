#ifndef _IMAGE
#define _IMAGE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

#include "Color.hpp"
#include "Point.hpp"

class Image
{
protected:
    int width;
    int height;
    Color *Colors;

    void makePointRep(Point* pos);
    bool isPointInImage(Point pos);
    void floodRepColorHelper(Color filler, Color replaced, Point pos, std::vector<Point> &points);
public:
    // Constructors
    Image();
    Image(int w, int h);
    Image(const Image &other);
    ~Image();

    // Getters
    int getWidth() const;
    int getHeight() const;

    // Color Getters
    Color getColors() const;
    Color getColor(Point pos) const;
    Color getColor(int w, int h) const;

    // Color Methods
    void setRepColor(Color p, Point* pos);
    void setNoRepColor(Color p, Point pos);
    void replaceRepColor(Color replacement, Color replaced, Point* pos);
    void replaceNoRepColor(Color replacement, Color replaced, Point pos);
    void oldFloodRepColor(Color filler, Point pos);
    void floodRepColor(Color filler, Point pos);
    void floodNoRepColor(Color filler, Point pos);

    // Image Methods
    void exportImage(std::string filename, int width_repititions, int height_repititions);
    void printImageConsole();

    // Color and noise
    void colorFilter(float amount);
    void addNoise(double noiseDensity, int noiseSpread, int noiseColorfulness, int noiseSaturation);

    // Drawing
    void drawLine(Color color, Point p1, Point p2, int thickness);
    void drawCurve(Color color, Point p1, Point p2, int offset);
    void drawCircle(Color color, Point center, int radius);
    void drawPartialEmptyCircle(int radius, double startAngle, double endAngle, Point center, Color color);
    void drawPartialCheeseWheel(int radius, double startAngle, double endAngle, Point center, Color color);
    void drawFilledCircleWithBorder(int radius, Point center, Color fillColor, Color borderColor);

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