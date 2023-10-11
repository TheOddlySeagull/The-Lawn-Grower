#include "Canvas.hpp"

// Constructors

Canvas::Canvas() : Image()
{
    scale = 1;
}

Canvas::Canvas(int w, int h, int _scale) : Image(w, h)
{
    scale = _scale;
}

Canvas::Canvas(const Canvas &other) : Image(other)
{
    scale = other.scale;
}

Canvas::~Canvas()
{
}

// Getters
int Canvas::getScale() const
{
    return scale;
}

// Setters
void Canvas::setScale(int s)
{
    scale = s;
}