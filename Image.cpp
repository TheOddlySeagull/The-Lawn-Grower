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
    pos.insureWithinBounds(width, height);
    std::cout << "floodRepPixelHelper pos: " << pos << std::endl;
    // If current point is not in visited
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == pos) {
            std::cout << "visited" << std::endl;
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
    std::cout << "Image created with width " << width << " and height " << height << std::endl;
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
    pos.x = pos.x % width-1;
    pos.y = pos.y % height-1;
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

    // Calculate the file size
    int fileSize = 54 + (3 * newWidth * newHeight);

    // BMP header data (54 bytes)
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
        0, 0, 0, 0, // Image size (none)
        0, 0, 0, 0, // Horizontal resolution (none)
        0, 0, 0, 0, // Vertical resolution (none)
        0, 0, 0, 0, // Colors in palette (none)
        0, 0, 0, 0  // Important colors (none)
    };

    // Write the BMP header to the output file
    outputFile.write(header, 54);

    // Loop to write the image data, repeating it width_repititions times
    for (int h_rep = 0; h_rep < height_repititions; h_rep++) {
        for (int h = height - 1; h > -1; h--) {
            for (int w_rep = 0; w_rep < width_repititions; w_rep++) {
                for (int w = 0; w < width; w++) {
                    Pixel& pixel = pixels[h * width+1 + w];
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

void Image::printImageConsole()
{
    // Loop to print the image data
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            try
            {
                std::cout << "\033[48;2;" << pixels[h * width + w].getRed() << ";" << pixels[h * width + w].getGreen() << ";" << pixels[h * width + w].getBlue() << "m  \033[0m";
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        std::cout << std::endl;
    }
}


// Drawing
void Image::drawLine(Pixel color, Point p1, Point p2, int thickness) {

    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;
    int err2;
    
    while (true) {
        // Draw the central pixel
        setRepPixel(color, p1);

        // Draw additional pixels for thickness
        for (int t = 1; t <= thickness; t++) {
            int xt = p1.x + t * sx;
            int yt = p1.y + t * sy;

            setRepPixel(color, Point(xt, yt));
        }

        if (p1.x == p2.x && p1.y == p2.y) {
            break;
        }

        err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            p1.x += sx;
        }
        if (err2 < dx) {
            err += dx;
            p1.y += sy;
        }
    }
}

void Image::drawCurve(Pixel color, Point p1, Point p2, int offset) {
    // Calculate the direction vector of the line from p1 to p2
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    // Calculate the length of the line
    double lineLength = sqrt(dx * dx + dy * dy);

    // Normalize the direction vector
    double dirX = dx / lineLength;
    double dirY = dy / lineLength;

    // Calculate the perpendicular vector
    double perpX = -dirY;
    double perpY = dirX;

    // Calculate the control point position based on the offset
    double controlX = (p1.x + p2.x) / 2 + offset * perpX;
    double controlY = (p1.y + p2.y) / 2 + offset * perpY;

    // Calculate the number of segments for the curve
    int numSegments = 500;  // Increase the number of segments for higher resolution

    for (int i = 0; i <= numSegments; ++i) {
        double t = static_cast<double>(i) / numSegments;
        double u = 1 - t;

        // Calculate the Bézier curve point
        double x = u * u * p1.x + 2 * u * t * controlX + t * t * p2.x;
        double y = u * u * p1.y + 2 * u * t * controlY + t * t * p2.y;

        // Draw the point using setRepPixel
        setRepPixel(color, Point(static_cast<int>(x), static_cast<int>(y)));
    }
}


// Rotating
void Image::rotateImage(double angle)
{
    // Calculate the new width and height
    int newWidth = static_cast<int>(width * cos(angle) + height * sin(angle));
    int newHeight = static_cast<int>(width * sin(angle) + height * cos(angle));

    // Create a new array of pixels
    Pixel *newPixels = new Pixel[newWidth * newHeight];

    // Loop to rotate the image
    for (int w = 0; w < newWidth; w++) {
        for (int h = 0; h < newHeight; h++) {
            // Calculate the original position of the pixel
            double x = (w - newWidth / 2) * cos(angle) - (h - newHeight / 2) * sin(angle) + width / 2;
            double y = (w - newWidth / 2) * sin(angle) + (h - newHeight / 2) * cos(angle) + height / 2;

            // Set the pixel at the new position to the pixel at the original position
            newPixels[h * newWidth + w] = getPixel(Point(static_cast<int>(x), static_cast<int>(y)));
        }
    }

    // Delete the old array of pixels
    delete[] pixels;

    // Assign the new array to pixels
    pixels = newPixels;

    // Update the width and height
    width = newWidth;
    height = newHeight;
}



// Operators
std::ostream &operator<<(std::ostream &os, const Image &img)
{
    os << img.width << "x" << img.height;
    return os;
}

