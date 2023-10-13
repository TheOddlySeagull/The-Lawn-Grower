#include "FlowerColors.hpp"


/**
 * @brief Dictionary mapping FlowerColors to Color
 * 
 */
std::map<FlowerColors, Color> FlowerColorsMap = {
    {LIGHT_RED, Color(232, 75, 44)},
    {DARK_RED, Color(127, 0, 0)},
    {ORANGE, Color(228, 128, 0)},
    {YELLOW, Color(228, 223, 68)},
    {PINK, Color(255, 56, 94)},
    {WHITE, Color(255, 255, 220)},
    {LIGHT_BLUE, Color(40, 230, 255)},
    {LAVENDER, Color(119, 88, 209)},
    {LIGHT_MAUVE, Color(206, 172, 212)},
    {LIGHT_ORANGE, Color(229, 191, 150)},
    {FLASHY_YELLOW, Color(255, 216, 0)},
    {DARK_PURPLE, Color(23, 0, 86)},
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
 * @brief Returns a random FlowerColor
 * 
 * @return Color 
 */
Color getRandomFlowerColor()
{
    int random = rand() % FlowerColorsMap.size();
    return FlowerColorsMap[static_cast<FlowerColors>(random)];
}

/**
 * @brief Returns a random FlowerColor except the given color
 * 
 * @param color 
 * @return Color 
 */
Color getRandomFlowerColorExcept(Color color)
{
    Color randomColor = getRandomFlowerColor();
    while (randomColor == color)
    {
        randomColor = getRandomFlowerColor();
    }
    return randomColor;
}

/**
 * @brief Returns a random FlowerColor except the given colors
 * 
 * @param colors 
 * @return Color 
 */
Color getRandomFlowerColorExcept(std::vector<Color> colors)
{
    Color randomColor = getRandomFlowerColor();
    bool found = false;
    while (!found)
    {
        for (int i = 0; i < colors.size(); i++)
        {
            if (randomColor == colors[i])
            {
                randomColor = getRandomFlowerColor();
                break;
            }
            else
            {
                found = true;
            }
        }
    }
    return randomColor;
}

/**
 * @brief Returns the Color of the given FlowerColor
 * 
 * @param color 
 * @return Color 
 */
Color getFlowerColor(FlowerColors color)
{
    return FlowerColorsMap[color];
}

/**
 * @brief Returns the FlowerColor of the given Color
 * 
 * @param color 
 * @return FlowerColors 
 */
FlowerColors getFlowerColor(Color color)
{
    for (int i = 0; i < FlowerColorsMap.size(); i++)
    {
        if (FlowerColorsMap[static_cast<FlowerColors>(i)] == color)
        {
            return static_cast<FlowerColors>(i);
        }
    }
    return static_cast<FlowerColors>(-1);
}