#include "Canvas.hpp"

// Constructors

Canvas::Canvas()
{
    width = 0;
    height = 0;
    pixels = new Pixel[width * height];
}

Canvas::Canvas(int w, int h, int _scale)
{
    width = w;
    height = h;
    this->scale = _scale;
    pixels = new Pixel[width * height];
}

Canvas::~Canvas()
{
    delete[] pixels;
}

// Getters

const int Canvas::getWidth()
{
    return width;
}

const int Canvas::getHeight()
{
    return height;
}

Pixel *Canvas::getPixels()
{
    return pixels;
}

Pixel Canvas::getPixel(int w, int h)
{
    return pixels[h * width + w];
}

// Setters

void Canvas::setWidth(int w)
{
    width = w;

    // Create new array of pixels
    Pixel *newPixels = new Pixel[width * height];

    // Delete old array of pixels
    delete[] pixels;

    // Assign new array to pixels
    pixels = newPixels;
}

void Canvas::setHeight(int h)
{
    height = h;

    // Create new array of pixels
    Pixel *newPixels = new Pixel[width * height];

    // Delete old array of pixels
    delete[] pixels;

    // Assign new array to pixels
    pixels = newPixels;
}

void Canvas::setPixel(Pixel p, int w, int h)
{
    w = w % width;
    h = h % height;
    if (w < 0) {
        w = width + w;
        }
    if (h < 0) {
        h = height + h;
        }

    pixels[h * width + w] = p;
}

void Canvas::replacePixel(Pixel replacement, Pixel replaced, int w, int h)
{
    w = w % width;
    h = h % height;
    if (w < 0) {
        w = width + w;
        }
    if (h < 0) {
        h = height + h;
        }

    if (pixels[h * width + w] == replaced) {
        pixels[h * width + w] = replacement;
    }
}

void Canvas::setNoRepPixel(Pixel p, int w, int h, bool vertical, bool horizontal)
{
    if (w < 0 && !vertical) {
        w = w + width;
    } else if (w > width && !vertical) {
        w = w % width;
    }

    if (h < 0 && !horizontal) {
        h = h + height;
    } else if (h > height && !horizontal) {
        h = h % height;
    }


    
}

void Canvas::exportImage(std::string filename, int width_repititions, int height_repititions) {
    // Open the output file for writing
    std::ofstream outputFile(filename, std::ios::binary);

    if (!outputFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Calculate the new width and height based on repetitions
    int newWidth = width * width_repititions;
    int newHeight = height * height_repititions;

    // Write the image header (assuming a simple BMP format)
    // You may need to adapt this part based on your image format
    // Here's a very basic example for a 24-bit BMP header
    int fileSize = 54 + (3 * newWidth * newHeight);
    char header[54] = {
        'B', 'M', // BMP magic number
        fileSize & 0xFF, (fileSize >> 8) & 0xFF, (fileSize >> 16) & 0xFF, (fileSize >> 24) & 0xFF, // File size
        0, 0, 0, 0, // Reserved
        54, 0, 0, 0, // Header size
        40, 0, 0, 0, // DIB header size
        newWidth & 0xFF, (newWidth >> 8) & 0xFF, (newWidth >> 16) & 0xFF, (newWidth >> 24) & 0xFF, // Canvas width
        newHeight & 0xFF, (newHeight >> 8) & 0xFF, (newHeight >> 16) & 0xFF, (newHeight >> 24) & 0xFF, // Canvas height
        1, 0, // Number of color planes (1)
        24, 0, // Bits per pixel (24-bit)
        0, 0, 0, 0, // Compression (none)
        0, 0, 0, 0, // Canvas size (none)
        0, 0, 0, 0, // Horizontal resolution (none)
        0, 0, 0, 0, // Vertical resolution (none)
        0, 0, 0, 0, // Colors in palette (none)
        0, 0, 0, 0  // Important colors (none)
    };

    outputFile.write(header, 54);

    // Write the image data, repeating it width_repititions and height_repititions times
    for (int h_rep = 0; h_rep < height_repititions; h_rep++) {
        for (int h = height - 1; h > -1; h--) {
            for (int w_rep = 0; w_rep < width_repititions; w_rep++) {
                for (int w = 0; w < width; w++) {
                    Pixel& pixel = pixels[h * width + w];
                    // Write the pixel color data (BGR order for BMP)
                    outputFile.put(pixel.getBlue());
                    outputFile.put(pixel.getGreen());
                    outputFile.put(pixel.getRed());
                }
            }
        }
    }

    // Close the output file
    outputFile.close();
}

void Canvas::setScale(int s)
{
    scale = s;
}

// Procedure to return scale
int Canvas::getScale()
{
    return scale;
}

