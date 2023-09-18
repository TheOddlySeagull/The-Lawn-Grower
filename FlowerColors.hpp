#pragma once // Only include this header once when compiling

#include <map>
#include "Pixel.hpp"

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
    LIGHT_ORANGE = 9
};

// Dictionary mapping FlowerColors to Pixel
extern std::map<FlowerColors, Pixel> FlowerColorsMap;

void printFlowerColorsMap();
Pixel getFlowerColor(FlowerColors color);
FlowerColors getFlowerColor(Pixel color);
Pixel getRandomFlowerColor();
Pixel getRandomFlowerColorExcept(FlowerColors color);