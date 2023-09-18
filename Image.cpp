#include "Image.hpp"



// Private Methods
Point Image::makePointRep(Point pos)
{
    Point newPoint;
    newPoint.x = pos.x % width;
    newPoint.y = pos.y % height;
    if (pos.x < 0) {
        newPoint.x += width;
    }
    if (pos.y < 0) {
        newPoint.y += height;
    }
    return newPoint;
}

void Image::floodRepPixelHelper(Pixel filler, Pixel replaced, Point pos, std::vector<Point> &visited)
{
    // If current point is not in visited
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == pos) {
            return;
        }
    }
    // Add current point to visited
    visited.push_back(pos);

    // if current point is replaced
    if (pixels[pos.y * width + pos.x] == replaced) {
        // replace current point with filler
        pixels[pos.y * width + pos.x] = filler;

        // For all 4 adjascent pixels
        floodRepPixelHelper(filler, replaced, makePointRep(Point(pos.x + 1, pos.y)), visited);
        floodRepPixelHelper(filler, replaced, makePointRep(Point(pos.x - 1, pos.y)), visited);
        floodRepPixelHelper(filler, replaced, makePointRep(Point(pos.x, pos.y + 1)), visited);
        floodRepPixelHelper(filler, replaced, makePointRep(Point(pos.x, pos.y - 1)), visited);
    }
}

// Constructors

Image::Image()
{
    width = 0;
    height = 0;
    pixels = new Pixel[width * height];
}

Image::Image(int w, int h)
{
    width = w;
    height = h;
    pixels = new Pixel[width * height];
}

Image::~Image()
{
    delete[] pixels;
}

// Getters

const int Image::getWidth()
{
    return width;
}

const int Image::getHeight()
{
    return height;
}

Pixel *Image::getPixels()
{
    return pixels;
}

Pixel Image::getPixel(Point pos)
{
    return pixels[pos.y * width + pos.x];
}

// Setters
void Image::updateImageWidth(int w)
{
    width = w;

    // Create new array of pixels
    Pixel *newPixels = new Pixel[width * height];

    // Delete old array of pixels
    delete[] pixels;

    // Assign new array to pixels
    pixels = newPixels;
}

void Image::updateImageHeight(int h)
{
    height = h;

    // Create new array of pixels
    Pixel *newPixels = new Pixel[width * height];

    // Delete old array of pixels
    delete[] pixels;

    // Assign new array to pixels
    pixels = newPixels;
}


// Pixel Methods
void Image::setRepPixel(Pixel p, Point pos)
{
    pos.x = pos.x % width;
    pos.y = pos.y % height;
    if (pos.x < 0) {
        pos.x += width;
    }
    if (pos.y < 0) {
        pos.y += height;
    }
    // Set pixel at pos to p
    pixels[pos.y * width + pos.x] = p;
}

void Image::setNoRepPixel(Pixel p, Point pos)
{
    if (pos.x >= 0 || pos.x < width || pos.y >= 0 || pos.y < height) {
        // Set pixel at pos to p
        pixels[pos.y * width + pos.x] = p;
    }
}

void Image::replaceRepPixel(Pixel replacement, Pixel replaced, Point pos)
{
    pos.x = pos.x % width;
    pos.y = pos.y % height;
    if (pos.x < 0) {
        pos.x += width;
    }
    if (pos.y < 0) {
        pos.y += height;
    }
    // Replace pixel at pos with replacement if it is replaced
    if (pixels[pos.y * width + pos.x] == replaced) {
        pixels[pos.y * width + pos.x] = replacement;
    }
}

void Image::replaceNoRepPixel(Pixel replacement, Pixel replaced, Point pos)
{
    if (pos.x >= 0 || pos.x < width || pos.y >= 0 || pos.y < height) {
        // Replace pixel at pos with replacement if it is replaced
        if (pixels[pos.y * width + pos.x] == replaced) {
            pixels[pos.y * width + pos.x] = replacement;
        }
    }
}

void Image::oldFloodRepPixel(Pixel filler, Point pos)
{
    // Define all 4 adjascent pixels
    Point north = Point(pos.x, pos.y + 1);
    Point east = Point(pos.x + 1, pos.y);
    Point south = Point(pos.x, pos.y - 1);
    Point west = Point(pos.x - 1, pos.y);

    north = makePointRep(north);
    east = makePointRep(east);
    south = makePointRep(south);
    west = makePointRep(west);

    exportImage("test.bmp", 1, 1);

    // Flood fill pixel at pos with filler
    Pixel replaced = pixels[pos.y * width + pos.x];
    pixels[pos.y * width + pos.x] = filler;

    if (getPixel(north) == replaced) {
        std::cout << "north: " << north << std::endl;
        floodRepPixel(filler, north);
    }
    if (getPixel(east) == replaced) {
        floodRepPixel(filler, east);
        std::cout << "east: " << east << std::endl;
    }
}

void Image::floodRepPixel(Pixel filler, Point pos)
{
    // Make an array of visited pixels
    std::vector<Point> visited;

    // for all 4 adjascent pixels
    floodRepPixelHelper(filler, pixels[pos.y * width + pos.x], makePointRep(Point(pos.x - 1, pos.y)), visited);
    floodRepPixelHelper(filler, pixels[pos.y * width + pos.x], makePointRep(Point(pos.x + 1, pos.y)), visited);
    floodRepPixelHelper(filler, pixels[pos.y * width + pos.x], makePointRep(Point(pos.x, pos.y - 1)), visited);
    floodRepPixelHelper(filler, pixels[pos.y * width + pos.x], makePointRep(Point(pos.x, pos.y + 1)), visited);

}

void Image::floodNoRepPixel(Pixel filler, Point pos)
{
    if (pos.x >= 0 || pos.x < width || pos.y >= 0 || pos.y < height) {
        // Flood fill pixel at pos with filler
        Pixel replaced = pixels[pos.y * width + pos.x];
        pixels[pos.y * width + pos.x] = filler;

        if (pos.x + 1 < width && pixels[pos.y * width + pos.x + 1] == replaced) {
            floodNoRepPixel(filler, Point(pos.x + 1, pos.y));
        }
        if (pos.x - 1 >= 0 && pixels[pos.y * width + pos.x - 1] == replaced) {
            floodNoRepPixel(filler, Point(pos.x - 1, pos.y));
        }
        if (pos.y + 1 < height && pixels[(pos.y + 1) * width + pos.x] == replaced) {
            floodNoRepPixel(filler, Point(pos.x, pos.y + 1));
        }
        if (pos.y - 1 >= 0 && pixels[(pos.y - 1) * width + pos.x] == replaced) {
            floodNoRepPixel(filler, Point(pos.x, pos.y - 1));
        }
    }
}


void Image::exportImage(std::string filename, int width_repititions, int height_repititions) {
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
        newWidth & 0xFF, (newWidth >> 8) & 0xFF, (newWidth >> 16) & 0xFF, (newWidth >> 24) & 0xFF, // Image width
        newHeight & 0xFF, (newHeight >> 8) & 0xFF, (newHeight >> 16) & 0xFF, (newHeight >> 24) & 0xFF, // Image height
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



