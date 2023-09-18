#include "TextureZone.hpp"

/**
 * @brief Construct a new Texture Zone object
 * 
 * @param top_left The point at the top left of the zone (Point object)
 * @param bottom_right The point at the bottom right of the zone (Point object)
 */
TextureZone::TextureZone(Point top_left, Point bottom_right)
{
    this->top_left = top_left;
    this->bottom_right = bottom_right;
}

TextureZone::~TextureZone()
{
}

/**
 * @brief Get a random position within the zone
 * 
 * @param img The canvas where the zone is located (Canvas object)
 * @return The random position (Point object)
 */
Point TextureZone::GetRandomAvailablePosition(Canvas *img)
{
    Point p;
    
    p.x = rand() % (this->bottom_right.x - this->top_left.x) + this->top_left.x;
    p.y = rand() % (this->bottom_right.y - this->top_left.y) + this->top_left.y;

    return p;
}

/**
 * @brief Get a random height that fits within the zone
 * 
 * @param factor The size factor (from 0) of the returned height. 0.5 will return a max height of half the size of the zone. (float)
 * @return The random height (int)
 */
int TextureZone::GetRandomHeight(float factor)
{
    // get the difference between top and bottom
    int difference = this->bottom_right.y - this->top_left.y;

    // get random number between 0 and difference
    int random = rand() % difference;

    // multiply random by factor
    int new_random = (int)(random * factor);

    if (new_random < 1)
    {
        new_random = 1;
    }

    std::cout << "Random height: " << new_random << std::endl;

    // return new random
    return new_random;
}

/**
 * @brief Gets the surface area of the zone
 * 
 * @return The surface area (int)
 */
int TextureZone::GetSurfaceArea()
{
    return (this->bottom_right.x - this->top_left.x) * (this->bottom_right.y - this->top_left.y);
}
