#include "FlowerColors.hpp"

#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>


/**
 * @brief Dictionary mapping FlowerColors to Pixel
 * 
 */
std::map<FlowerColors, Pixel> FlowerColorsMap = {
    {LIGHT_RED, Pixel(232, 75, 44)},
    {DARK_RED, Pixel(127, 0, 0)},
    {ORANGE, Pixel(228, 128, 0)},
    {YELLOW, Pixel(228, 223, 68)},
    {PINK, Pixel(255, 56, 94)},
    {WHITE, Pixel(255, 255, 220)},
    {LIGHT_BLUE, Pixel(40, 230, 255)},
    {LAVENDER, Pixel(119, 88, 209)},
    {LIGHT_MAUVE, Pixel(206, 172, 212)},
    {LIGHT_ORANGE, Pixel(229, 191, 150)}
};

/**
 * @brief Prints the FlowerColorsMap
 * 
 */
void printFlowerColorsMap()
{
    for (auto const &pair : FlowerColorsMap)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

/**
 * @brief Get the Flower Color object
 * 
 * @param color The name of the color, from the FlowerColors enum
 * @return The Pixel object representing the color
 */
Pixel getFlowerColor(FlowerColors color)
{
    return FlowerColorsMap[color];
}

/**
 * @brief Get the Flower Color object
 * 
 * @param color The Pixel object representing the color
 * @return The FlowerColors enum representing the color
 */
FlowerColors getFlowerColor(Pixel color)
{
    for (int i = 0; i < FlowerColorsMap.size(); i++)
    {
        if (FlowerColorsMap[static_cast<FlowerColors>(i)] == color)
        {
            return static_cast<FlowerColors>(i);
        }
    }
    return LIGHT_RED;
}

/**
 * @brief Get a Random Flower Color object
 * 
 * @return The Pixel object representing the color
 */
Pixel getRandomFlowerColor()
{
    // Get map length
    int length = FlowerColorsMap.size();
    int random = rand() % length;
    return FlowerColorsMap[static_cast<FlowerColors>(random)];
}

/**
 * @brief Get a Random Flower Color Except the provided color
 * 
 * @param color The color to exclude from the random selection
 * @return The Pixel object representing the color
 */
Pixel getRandomFlowerColorExcept(FlowerColors color)
{
    // Get map length
    int length = FlowerColorsMap.size();
    int random = rand() % length;
    while (static_cast<FlowerColors>(random) == color)
    {
        random = rand() % length;
    }
    return FlowerColorsMap[static_cast<FlowerColors>(random)];
}

/**
 * @brief Get a Random Flower Color Except the provided colors
 * 
 * @param colors The colors to exclude from the random selection
 * @return The Pixel object representing the color
 */
Pixel getRandomFlowerColorExcept(FlowerColors colors[])
{
    // Get map length
    int length = FlowerColorsMap.size();
    int random = rand() % length;

    std::cout << "Random: " << random << " out of " << length << std::endl;

    // Get a random color
    Pixel randomColor = FlowerColorsMap[static_cast<FlowerColors>(random)];

    std::cout << "Random Color: " << randomColor << std::endl; 

    // Check if the random color is in the colors array
    bool wip = true;

    while (wip)
    {
        // Check if the random color is in the colors array
        for (int i = 0; i < FlowerColorsMap.size(); i++)
        {
            if (randomColor == FlowerColorsMap[colors[i]])
            {
                // Get a new random color
                random = rand() % length;
                randomColor = FlowerColorsMap[static_cast<FlowerColors>(random)];
                break;
            }
            else if (i == FlowerColorsMap.size() - 1)
            {
                // The random color is not in the colors array
                wip = false;
            }
        }
    }
    
    return randomColor;
    
}