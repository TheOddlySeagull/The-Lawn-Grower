#ifndef _FLOWERCOLORS
#define _FLOWERCOLORS

#include <map>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>


#include "Color.hpp"


/**
 * @brief Enum for Flower Colors
 * 
 */
enum FlowerColors {
    LIGHT_RED = 0,
    DARK_RED = 1,
    ORANGE = 2,
    YELLOW = 3,
    PINK = 4,
    WHITE = 5,
    LIGHT_BLUE = 6,
    LAVENDER = 7,
    LIGHT_MAUVE = 8,
    LIGHT_ORANGE = 9,
    FLASHY_YELLOW = 10,
    DARK_PURPLE = 11,
};

// Dictionary mapping FlowerColors to Color
extern std::map<FlowerColors, Color> FlowerColorsMap;

void printFlowerColorsMap();
Color getRandomFlowerColor();
Color getRandomFlowerColorExcept(Color color);
Color getRandomFlowerColorExcept(std::vector<Color> colors);
Color getFlowerColor(FlowerColors color);
FlowerColors getFlowerColor(Color color);


struct petal_values
{
    int length;
    int topWidth;
    int topCurvature;
    int pointOffset;
    double sideCurveFactor;
    Color color;
};

#endif