#include "Image.hpp"

// Private Methods
void Image::makePointRep(Point* pos)
{
    pos->x = pos->x % width;
    pos->y = pos->y % height;
    if (pos->x < 0) {
        pos->x += width;
    }
    if (pos->y < 0) {
        pos->y += height;
    }
}

bool Image::isPointInImage(Point pos)
{
    if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) {
        return true;
    }
    return false;
}

void Image::floodRepColorHelper(Color filler, Color replaced, Point pos, std::vector<Point> &visited)
{
    pos.insureWithinBounds(width, height);
    //std::cout << "floodRepColorHelper pos: " << pos << std::endl;
    // If current point is not in visited
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == pos) {
            //std::cout << "visited" << std::endl;
            return;
        }
    }
    // Add current point to visited
    visited.push_back(pos);

    // if current point is replaced
    if (Colors[pos.y * width + pos.x] == replaced) {
        // replace current point with filler
        Colors[pos.y * width + pos.x] = filler;

        Point north = Point(pos.x, pos.y + 1);
        Point east = Point(pos.x + 1, pos.y);
        Point south = Point(pos.x, pos.y - 1);
        Point west = Point(pos.x - 1, pos.y);

        makePointRep(&north);
        makePointRep(&east);
        makePointRep(&south);
        makePointRep(&west);

        // For all 4 adjascent Colors
        floodRepColorHelper(filler, replaced, north, visited);
        floodRepColorHelper(filler, replaced, east, visited);
        floodRepColorHelper(filler, replaced, south, visited);
        floodRepColorHelper(filler, replaced, west, visited);
    }
}


// Constructors
Image::Image()
{
    width = 0;
    height = 0;
    Colors = new Color[width * height];
}

Image::Image(int w, int h)
{
    width = w;
    height = h;
    Colors = new Color[width * height];
    //std::cout << "Image created with width " << width << " and height " << height << std::endl;
}

Image::Image(const Image &other)
{
    width = other.width;
    height = other.height;
    Colors = new Color[width * height];
    for (int i = 0; i < width * height; i++) {
        Colors[i] = other.Colors[i];
    }
}

Image::~Image()
{
    delete[] Colors;
}

// Getters
int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

// Color Getters
Color Image::getColors() const
{
    return *Colors;
}

Color Image::getColor(Point pos) const
{
    return Colors[pos.y * width + pos.x];
}

Color Image::getColor(int w, int h) const
{
    return Colors[h * width + w];
}

// Color Methods
void Image::setRepColor(Color p, Point* pos)
{
    makePointRep(pos);

    // Set Color at pos to p
    Colors[pos->y * width + pos->x] = p;
}

void Image::setNoRepColor(Color p, Point pos)
{
    if (isPointInImage(pos)) {
        // Set Color at pos to p
        Colors[pos.y * width + pos.x] = p;
    }
}

void Image::replaceRepColor(Color replacement, Color replaced, Point* pos)
{
    makePointRep(pos);
    // Replace Color at pos with replacement if it is replaced
    if (Colors[pos->y * width + pos->x] == replaced) {
        Colors[pos->y * width + pos->x] = replacement;
    }
}

void Image::replaceNoRepColor(Color replacement, Color replaced, Point pos)
{
    if (isPointInImage(pos)) {
        // Replace Color at pos with replacement if it is replaced
        if (Colors[pos.y * width + pos.x] == replaced) {
            Colors[pos.y * width + pos.x] = replacement;
        }
    }
}

void Image::oldFloodRepColor(Color filler, Point pos)
{
    // Define all 4 adjascent Colors
    Point north = Point(pos.x, pos.y + 1);
    Point east = Point(pos.x + 1, pos.y);
    Point south = Point(pos.x, pos.y - 1);
    Point west = Point(pos.x - 1, pos.y);

    makePointRep(&north);
    makePointRep(&east);
    makePointRep(&south);
    makePointRep(&west);

    exportImage("test.bmp", 1, 1);

    // Flood fill Color at pos with filler
    Color replaced = Colors[pos.y * width + pos.x];
    Colors[pos.y * width + pos.x] = filler;

    if (getColor(north) == replaced) {
        std::cout << "north: " << north << std::endl;
        floodRepColor(filler, north);
    }
    if (getColor(east) == replaced) {
        floodRepColor(filler, east);
        std::cout << "east: " << east << std::endl;
    }
}

void Image::floodRepColor(Color filler, Point pos)
{
    // Make an array of visited Colors
    std::vector<Point> visited;

    Point north = Point(pos.x, pos.y + 1);
    Point east = Point(pos.x + 1, pos.y);
    Point south = Point(pos.x, pos.y - 1);
    Point west = Point(pos.x - 1, pos.y);

    makePointRep(&north);
    makePointRep(&east);
    makePointRep(&south);
    makePointRep(&west);

    // for all 4 adjascent Colors
    floodRepColorHelper(filler, Colors[pos.y * width + pos.x], north, visited);
    floodRepColorHelper(filler, Colors[pos.y * width + pos.x], east, visited);
    floodRepColorHelper(filler, Colors[pos.y * width + pos.x], south, visited);
    floodRepColorHelper(filler, Colors[pos.y * width + pos.x], west, visited);

}

void Image::floodNoRepColor(Color filler, Point pos)
{
    if (pos.x >= 0 || pos.x < width || pos.y >= 0 || pos.y < height) {
        // Flood fill Color at pos with filler
        Color replaced = Colors[pos.y * width + pos.x];
        Colors[pos.y * width + pos.x] = filler;

        if (pos.x + 1 < width && Colors[pos.y * width + pos.x + 1] == replaced) {
            floodNoRepColor(filler, Point(pos.x + 1, pos.y));
        }
        if (pos.x - 1 >= 0 && Colors[pos.y * width + pos.x - 1] == replaced) {
            floodNoRepColor(filler, Point(pos.x - 1, pos.y));
        }
        if (pos.y + 1 < height && Colors[(pos.y + 1) * width + pos.x] == replaced) {
            floodNoRepColor(filler, Point(pos.x, pos.y + 1));
        }
        if (pos.y - 1 >= 0 && Colors[(pos.y - 1) * width + pos.x] == replaced) {
            floodNoRepColor(filler, Point(pos.x, pos.y - 1));
        }
    }
}

// Image Methods
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
        24, 0, // Bits per Color (24-bit)
        0, 0, 0, 0, // Compression (none)
        0, 0, 0, 0, // Image size (none)
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
                    Color& Color = Colors[h * width + w];
                    // Write the Color color data (BGR order for BMP)
                    outputFile.put(Color.getBlue());
                    outputFile.put(Color.getGreen());
                    outputFile.put(Color.getRed());
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
                std::cout << "\033[48;2;" << Colors[h * width + w].getRed() << ";" << Colors[h * width + w].getGreen() << ";" << Colors[h * width + w].getBlue() << "m  \033[0m";
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        std::cout << std::endl;
    }
}


// Color and noise
void Image::colorFilter(float amount) {
    // Iterate through the Colors of the current image
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            Point pos(w, h);
            Color color = getColor(pos);

            // Calculate the new color components
            int newRed = static_cast<int>(color.getRed() * amount);
            int newGreen = static_cast<int>(color.getGreen() * amount);
            int newBlue = static_cast<int>(color.getBlue() * amount);

            // Make sure the new color components are within bounds
            newRed = std::min(std::max(newRed, 0), 255);
            newGreen = std::min(std::max(newGreen, 0), 255);
            newBlue = std::min(std::max(newBlue, 0), 255);

            // Update the Color color
            setRepColor(Color(newRed, newGreen, newBlue), &pos);
        }
    }
}

void Image::addNoise(double noiseDensity, int noiseSpread, int noiseColorfulness, int noiseSaturation) {
    
    // Initialize the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);


    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Color& Color = Colors[y * width + x];
            if (Color.getRed() + Color.getGreen() + Color.getBlue() > 0 && dis(gen) < noiseDensity) {

                // Random value between -noiseSpread and +noiseSpread
                int radius = rand() % (2 * noiseSpread) - noiseSpread;

                int noiseR = Color.getRed() + radius + (rand() % (2 * noiseColorfulness) - noiseColorfulness);
                int noiseG = Color.getGreen() + radius + (rand() % (2 * noiseColorfulness) - noiseColorfulness);
                int noiseB = Color.getBlue() + radius + (rand() % (2 * noiseColorfulness) - noiseColorfulness);

                // Ensure that the noise values do not exceed the specified saturation
                noiseR = std::min(std::max(noiseR, 0), noiseSaturation);
                noiseG = std::min(std::max(noiseG, 0), noiseSaturation);
                noiseB = std::min(std::max(noiseB, 0), noiseSaturation);

                Color.setRed(noiseR);
                Color.setGreen(noiseG);
                Color.setBlue(noiseB);
            }
        }
    }
}


// Drawing
void Image::drawLine(Color color, Point p1, Point p2, int thickness) {

    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;
    int err2;

    makePointRep(&p2);
    
    while (true) {
        // Draw the central Color
        setRepColor(color, &p1);

        // Draw additional Colors for thickness
        for (int t = 1; t <= thickness; t++) {
            int xt = p1.x + t * sx;
            int yt = p1.y + t * sy;

            Point pos(xt, yt);

            setRepColor(color, &pos);
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

void Image::drawCurve(Color color, Point p1, Point p2, int offset) {
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

        // Create a point from the calculated coordinates
        Point pos(static_cast<int>(x), static_cast<int>(y));

        // Draw the point using setRepColor
        setRepColor(color, &pos);
    }
}

void Image::drawCircle(Color color, Point center, int radius) {
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        // Draw horizontal scanlines
        for (int i = center.x - x; i <= center.x + x; i++) {

            Point pos(i, center.y + y);
            setRepColor(color, &pos);
            pos.y = center.y - y;
            setRepColor(color, &pos);
        }

        // Draw vertical scanlines
        for (int i = center.x - y; i <= center.x + y; i++) {

            Point pos(i, center.y + x);
            setRepColor(color, &pos);
            pos.y = center.y - x;
            setRepColor(color, &pos);
        }

        y++;

        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}

void Image::drawPartialEmptyCircle(int radius, double startAngle, double endAngle, Point center, Color color) {
    // Ensure that startAngle and endAngle are within the range [0, 360]
    startAngle = fmod(startAngle, 360.0);
    endAngle = fmod(endAngle, 360.0);

    // Convert startAngle and endAngle to radians
    double startAngleRad = startAngle * M_PI / 180.0;
    double endAngleRad = endAngle * M_PI / 180.0;

    // Draw the partial circle using the specified angles
    for (double angle = startAngleRad; angle <= endAngleRad; angle += 0.01) {
        int x = static_cast<int>(center.x + radius * cos(angle));
        int y = static_cast<int>(center.y + radius * sin(angle));

        // Make sure the calculated Color coordinates are within the image bounds
        if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
            setRepColor(color, new Point(x, y));
        }
    }
}

void Image::drawPartialCheeseWheel(int radius, double startAngle, double endAngle, Point center, Color color) {
    // Value adaptation for this function
    if (startAngle < 0 || endAngle < 0 || startAngle > 360 || endAngle > 360) {
        std::cout << "Invalid angle detected, dividing to 2 itterations." << std::endl;
        int new_startAngle_1 = 0;
        int new_endAngle_1 = 0;
        int new_startAngle_2 = 0;
        int new_endAngle_2 = 0;
        
        // If angle is negative, divide the shape into two parts and draw them separately
        if (startAngle < 0) {
            std::cout << "Start angle less than 0 detected" << std::endl;

            new_startAngle_1 = 360 + startAngle;
            new_endAngle_1 = 360.0;
            new_startAngle_2 = 0;
            new_endAngle_2 = endAngle;

        }
        if (endAngle >= 360) {
            std::cout << "End angle greater than 360 detected" << std::endl;

            new_startAngle_1 = startAngle;
            new_endAngle_1 = 360.0;
            new_startAngle_2 = 0;
            new_endAngle_2 = endAngle - 360;

        }

        // Draw the first part of the circle
        drawPartialCheeseWheel(radius, new_startAngle_1, new_endAngle_1, center, color);
        drawPartialCheeseWheel(radius, new_startAngle_2, new_endAngle_2, center, color);

        return;
    }

    // Calculate the bounding box for the partial circle
    int xMin = center.x - radius;
    int xMax = center.x + radius;
    int yMin = center.y - radius;
    int yMax = center.y + radius;

    // Loop through the bounding box and check each Color if it's inside the partial circle
    for (int x = xMin; x <= xMax; x++) {
        for (int y = yMin; y <= yMax; y++) {
            // Calculate the angle of the current Color relative to the circle's center
            double ColorAngle = atan2(y - center.y, x - center.x) * (180.0 / M_PI);

            // Ensure ColorAngle is within [0, 360] degrees
            ColorAngle = (ColorAngle < 0) ? ColorAngle + 360.0 : ColorAngle;

            // Check if the Color is within the specified angle range
            if (ColorAngle >= startAngle && ColorAngle <= endAngle) {
                // Calculate the distance from the center of the circle to the current Color
                double distance = sqrt(pow(x - center.x, 2) + pow(y - center.y, 2));

                // Check if the Color is within the circle's radius
                if (distance <= radius) {
                    // Set the Color color
                    setRepColor(color, new Point(x, y));
                }
            }
        }
    }
}

void Image::drawFilledCircleWithBorder(int radius, Point center, Color fillColor, Color borderColor) {
    // Draw the filled circle with the fillColor
    drawCircle(fillColor, center, radius);

    // Draw a slightly smaller circle with the borderColor to create the border effect
    drawCircle(borderColor, center, radius - 1);
}

// Rotating
void Image::rotate(float angleDegrees) {
    if (angleDegrees == 0) {
        // No rotation needed
        return;
    }
    // Convert the angle to radians
    float angleRadians = angleDegrees * 3.14159265 / 180.0;

    // Calculate the dimensions of the rotated image
    int newWidth = static_cast<int>(abs(width * cos(angleRadians)) + abs(height * sin(angleRadians)));
    int newHeight = static_cast<int>(abs(width * sin(angleRadians)) + abs(height * cos(angleRadians)));

    // Create a new image buffer for the rotated image and fill it with black Colors
    Color* rotatedColors = new Color[newWidth * newHeight];
    for (int i = 0; i < newWidth * newHeight; i++) {
        rotatedColors[i] = Color(0, 0, 0); // Black Color
    }

    // Calculate the center point of the original image
    Point center(static_cast<int>(width / 2), static_cast<int>(height / 2));

    // Iterate over each Color in the rotated image
    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            // Calculate the corresponding position in the original image
            float srcX = static_cast<float>(x - newWidth / 2);
            float srcY = static_cast<float>(y - newHeight / 2);

            float originalX = center.x + (srcX * cos(-angleRadians) - srcY * sin(-angleRadians));
            float originalY = center.y + (srcX * sin(-angleRadians) + srcY * cos(-angleRadians));

            // Check if the original coordinates are within bounds
            if (originalX >= 0 && originalX < width && originalY >= 0 && originalY < height) {
                // Copy the color from the original image to the rotated image
                rotatedColors[y * newWidth + x] = getColor(Point(static_cast<int>(originalX), static_cast<int>(originalY)));
            }
        }
    }

    // Update the image dimensions and Color buffer
    width = newWidth;
    height = newHeight;
    delete[] Colors;
    Colors = rotatedColors;
}

// Trimming
void Image::trim(int newWidth, int newHeight) {
    if (newWidth <= 0 || newHeight <= 0) {
        // Invalid dimensions
        return;
    }

    // Create a new image buffer for the trimmed image and fill it with black Colors
    Color* trimmedColors = new Color[newWidth * newHeight];
    for (int i = 0; i < newWidth * newHeight; i++) {
        trimmedColors[i] = Color(0, 0, 0); // Black Color
    }

    // Find the size difference between the original image and the trimmed image
    int widthDiff = width - newWidth;
    int heightDiff = height - newHeight;

    // Calculate the starting point of the original image in the trimmed image
    int orStartX = static_cast<int>(width / 2);
    int orStartY = static_cast<int>(height / 2);

    // Calculate the starting point of the trimmed image in the original image
    int nwStartX = static_cast<int>(newWidth / 2);
    int nwStartY = static_cast<int>(newHeight / 2);

    // Copy the Colors from the original image to the trimmed image
    for (int w = 0; w < newWidth; w++) {
        for (int h = 0; h < newHeight; h++) {
            int orX = orStartX + w - nwStartX;
            int orY = orStartY + h - nwStartY;

            //If the Color is within the bounds of the new image, copy it
            if (orX >= 0 && orX < width && orY >= 0 && orY < height) {
                trimmedColors[h * newWidth + w] = getColor(Point(orX, orY));
            }
        }
    }

    // Update the image dimensions and Color buffer
    width = newWidth;
    height = newHeight;
    delete[] Colors;
    Colors = trimmedColors;
}


//Scaling
void Image::scale(int new_scale) {
    int default_scale = 8000;

    int new_height = height * new_scale / default_scale;
    int new_width = width * new_scale / default_scale;

    //std::cout << "Default scale: " << default_scale << " has size: " << width << "x" << height << " and new scale: " << new_scale << " has size: " << new_width << "x" << new_height << std::endl;

    //If resizing in needed:
    if (new_scale != default_scale) {
        resize(new_width, new_height);
    }
}

//Resize
void Image::resize(int new_width, int new_height) {
    //std::cout << "Resizing image from " << width << "x" << height << " to " << new_width << "x" << new_height << std::endl;
    // Create a new image with the desired dimensions
    Image resizedImage(new_width, new_height);

    // Calculate scaling factors for width and height
    double xScale = static_cast<double>(width) / new_width;
    double yScale = static_cast<double>(height) / new_height;

    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            // Calculate the corresponding position in the original image using interpolation
            double srcX = x * xScale;
            double srcY = y * yScale;

            // Calculate the coordinates of the surrounding Colors in the original image
            int x1 = static_cast<int>(srcX);
            int x2 = std::min(x1 + 1, width - 1);
            int y1 = static_cast<int>(srcY);
            int y2 = std::min(y1 + 1, height - 1);

            // Calculate interpolation weights
            double xWeight = srcX - x1;
            double yWeight = srcY - y1;

            // Perform bilinear interpolation to calculate the Color color
            Color interpolatedColor = 
                getColor(x1, y1) * (1 - xWeight) * (1 - yWeight) +
                getColor(x2, y1) * xWeight * (1 - yWeight) +
                getColor(x1, y2) * (1 - xWeight) * yWeight +
                getColor(x2, y2) * xWeight * yWeight;

            // Set the Color in the resized image
            Point pos(x, y);
            resizedImage.setRepColor(interpolatedColor, &pos);
        }
    }

    // Replace the current image with the resized image
    width = new_width;
    height = new_height;
    delete[] Colors;
    Colors = new Color[width * height];

    // Copy the Colors from the resized image to the current image
    for (int i = 0; i < width * height; i++) {
        Colors[i] = resizedImage.Colors[i];
    }
}




// Merging
void Image::merge(const Image &other) {
    // Check if the two images have the same dimensions
    if (width != other.width || height != other.height) {
        std::cerr << "Error: Images have different dimensions and cannot be merged." << std::endl;
        std::cout << "width: " << width << " other.width: " << other.width << std::endl;
        std::cout << "height: " << height << " other.height: " << other.height << std::endl;
        return;
    }

    // Iterate through the Colors of the parameter image
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            Point pos(w, h);
            Color Color = other.getColor(pos);

            // Only merge non-black Colors
            if (!Color.isBlack()) {
                setRepColor(Color, &pos);
            }
        }
    }
}

void Image::merge(const Image &other, Point pos) {
    // Check if the two images have the same dimensions
    if (width != other.width || height != other.height) {
        std::cerr << "Error: Images have different dimensions and cannot be merged." << std::endl;
        std::cout << "width: " << width << " other.width: " << other.width << std::endl;
        std::cout << "height: " << height << " other.height: " << other.height << std::endl;
        return;
    }

    // Iterate through the Colors of the parameter image
    for (int w = 0; w < other.width; w++) {
        for (int h = 0; h < other.height; h++) {
            Point otherPos(w, h);
            Color Color = other.getColor(otherPos);

            // Only merge non-black Colors
            if (!Color.isBlack()) {
                Point newPos = pos + otherPos;
                setRepColor(Color, &newPos);
            }
        }
    }
}

void Image::mergeExcept(const Image &other, const Image &except) {
    // Check if the two images have the same dimensions
    if (width != other.width || height != other.height || width != except.width || height != except.height) {
        std::cerr << "Error: Images have different dimensions and cannot be merged." << std::endl;
        std::cout << "width: " << width << " other.width: " << other.width << std::endl;
        std::cout << "height: " << height << " other.height: " << other.height << std::endl;
        return;
    }

    // Iterate through the Colors of the parameter image
    for (int w = 0; w < other.width; w++) {
        for (int h = 0; h < other.height; h++) {

            // Check if the Color is black in the except image
            if (except.getColor(Point(w, h)) == Color(0, 0, 0) && other.getColor(Point(w, h)) != Color(0, 0, 0)) {
                Point pos(w, h);
                Color Color = other.getColor(pos);
                setNoRepColor(Color, pos);
            }
        }
    }
}

void Image::mergeExcept(const Image &other, const Image &except, Point pos) {
    // Check if the two images have the same dimensions
    if (width != other.width || height != other.height || width != except.width || height != except.height) {
        std::cerr << "Error: Images have different dimensions and cannot be merged." << std::endl;
        std::cout << "width: " << width << " other.width: " << other.width << std::endl;
        std::cout << "height: " << height << " other.height: " << other.height << std::endl;
        return;
    }

    // Iterate through the Colors of the parameter image
    for (int w = 0; w < other.width; w++) {
        for (int h = 0; h < other.height; h++) {

            // Check if the Color is black in the except image
            if (except.getColor(Point(w, h)) == Color(0, 0, 0) && other.getColor(Point(w, h)) != Color(0, 0, 0)) {
                Point otherPos(w, h);
                Color Color = other.getColor(otherPos);
                Point newPos = pos + otherPos;
                setNoRepColor(Color, newPos);
            }
        }
    }
}

void Image::mergeLayerRep(const Image &other, Point pos) {

    // Iterate through the Colors of the parameter image
    for (int w = 0; w < other.width; w++) {
        for (int h = 0; h < other.height; h++) {
            Point otherPos(w, h);
            Point newPos = pos + otherPos;

            //If Color is not black
            if (other.getColor(otherPos) != Color(0, 0, 0)) {
                setRepColor(other.getColor(otherPos), &newPos);
            }
        }
    }
}

void Image::mergeLayerNoRep(const Image &other, Point pos) {

    // Iterate through the Colors of the parameter image
    for (int w = 0; w < other.width; w++) {
        for (int h = 0; h < other.height; h++) {
            Point otherPos(w, h);

            setNoRepColor(other.getColor(otherPos), pos + otherPos);
        }
    }
}

void Image::expand(const Image &other) {
    // Calculate the new dimensions
    int newWidth = width + other.width;
    int newHeight = std::max(height, other.height);

    // Create a new image buffer for the expanded image and fill it with black Colors
    Color* expandedColors = new Color[newWidth * newHeight];
    for (int i = 0; i < newWidth * newHeight; i++) {
        expandedColors[i] = Color(0, 0, 0); // Black Color
    }

    // Copy the Colors from the current image to the expanded image
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            Point pos(w, h);
            Color Color = getColor(pos);
            expandedColors[h * newWidth + w] = Color;
        }
    }

    // Copy the Colors from the parameter image to the expanded image
    for (int w = 0; w < other.width; w++) {
        for (int h = 0; h < other.height; h++) {
            Point pos(w, h);
            Color Color = other.getColor(pos);
            expandedColors[h * newWidth + w + width] = Color;
        }
    }

    // Update the image dimensions and Color buffer
    width = newWidth;
    height = newHeight;
    delete[] Colors;
    Colors = expandedColors;
}

// Operators
std::ostream &operator<<(std::ostream &os, const Image &img)
{
    os << img.width << "x" << img.height;
    return os;
}

