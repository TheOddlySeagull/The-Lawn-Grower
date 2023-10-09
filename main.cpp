#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>
#include <unistd.h>

#include "Canvas.hpp"
#include "FlowerColors.hpp"
#include "Point.hpp"
#include "TextureZone.hpp"
#include "Image.hpp"


/**
 * @brief Draw a circle on the image.
 * 
 * This function draws a circle on the provided image with the specified color,
 * center, and radius.
 * 
 * @param img This is a reference to the Canvas object you want to draw on. It's the canvas you'll be modifying.
 * @param color The color of the circle (Pixel object).
 * @param center The center of the circle (Point object).
 * @param radius The radius of the circle.
 */
void drawCircle(Canvas& img, Pixel color, Point center, int radius) {
    for (int x = center.x - radius; x <= center.x + radius; x++) {
        for (int y = center.y - radius; y <= center.y + radius; y++) {
            // Check if the pixel is within the circle using the circle equation
            if ((x - center.x) * (x - center.x) + (y - center.y) * (y - center.y) <= radius * radius) {
                img.setPixel(color, x, y);
            }
        }
    }
}

/**
 * @brief Draw a partial arche on the image.
 *
 * This function draws a partial circle on the provided image with the specified radius,
 * start angle, end angle, position, and color. The circle is drawn as a "cheese wheel,"
 * where you can specify the start and end angles to create partial circles.
 *
 * @param img The Canvas object to draw on.
 * @param radius The radius of the circle in pixels.
 * @param startAngle The angle at which the circle starts (in degrees).
 * @param endAngle The angle at which the circle ends (in degrees).
 * @param center The position of the center of the circle (Point object).
 * @param color The color of the circle (Pixel object).
 */
void drawPartialEmptyCircle(Canvas& img, int radius, double startAngle, double endAngle, Point center, Pixel color) {
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

        // Make sure the calculated pixel coordinates are within the image bounds
        if (x >= 0 && x < img.getWidth() && y >= 0 && y < img.getHeight()) {
            img.setPixel(color, x, y);
        }
    }
}

/**
 * @brief Draw a solid partial cheese wheel-like circle on the image.
 *
 * This function draws a solid partial cheese wheel-like circle on the provided image
 * with the specified radius, start angle, end angle, position, color, and image object.
 * If negative angles are provided, the circle is divided into two parts and drawn separately.
 *
 * @param img The Canvas object to draw on.
 * @param radius The radius of the circle in pixels (int).
 * @param startAngle The angle at which the circle starts (degrees).
 * @param endAngle The angle at which the circle ends (degrees).
 * @param position The position of the center of the circle (Point object).
 * @param color The color of the circle (Pixel object).
 */
void drawPartialCheeseWheel(Canvas& img, int radius, double startAngle, double endAngle, Point position, Pixel color) {
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
        drawPartialCheeseWheel(img, radius, new_startAngle_1, new_endAngle_1, position, color);
        drawPartialCheeseWheel(img, radius, new_startAngle_2, new_endAngle_2, position, color);

        return;
    }

    // Calculate the bounding box for the partial circle
    int xMin = position.x - radius;
    int xMax = position.x + radius;
    int yMin = position.y - radius;
    int yMax = position.y + radius;

    // Loop through the bounding box and check each pixel if it's inside the partial circle
    for (int x = xMin; x <= xMax; x++) {
        for (int y = yMin; y <= yMax; y++) {
            // Calculate the angle of the current pixel relative to the circle's center
            double pixelAngle = atan2(y - position.y, x - position.x) * (180.0 / M_PI);

            // Ensure pixelAngle is within [0, 360] degrees
            pixelAngle = (pixelAngle < 0) ? pixelAngle + 360.0 : pixelAngle;

            // Check if the pixel is within the specified angle range
            if (pixelAngle >= startAngle && pixelAngle <= endAngle) {
                // Calculate the distance from the center of the circle to the current pixel
                double distance = sqrt(pow(x - position.x, 2) + pow(y - position.y, 2));

                // Check if the pixel is within the circle's radius
                if (distance <= radius) {
                    // Set the pixel color
                    img.setPixel(color, x, y);
                }
            }
        }
    }
}

/**
 * @brief Draw a line on the image with specified line thickness.
 *
 * This function draws a line on the provided image from Point p1 to Point p2
 * using the specified color and line thickness.
 *
 * @param img This is a reference to the Canvas object you want to draw on. It's the canvas you'll be modifying.
 * @param color The color of the line (Pixel object).
 * @param p1 The starting Point.
 * @param p2 The ending Point.
 * @param thickness The thickness of the line.
 */
void drawLine(Canvas& img, Pixel color, Point p1, Point p2, int thickness) {
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;
    int err2;
    
    while (true) {
        // Draw the central pixel
        img.setPixel(color, p1.x % img.getWidth(), p1.y % img.getHeight());

        // Draw additional pixels for thickness
        for (int t = 1; t <= thickness; t++) {
            int xt = p1.x + t * sx;
            int yt = p1.y + t * sy;

            img.setPixel(color, xt % img.getWidth(), yt % img.getHeight());
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


/**
 * @brief Generate a petal model.
 * 
 * @param length The length of the petal
 * @param topWidth The max width of the petal
 * @param topCurvature The curvature of the top of the petal
 * @param pointOffset The offset of the point of the petal from the top curvature
 * @param color The color of the petal
 * @return The generated petal model as a Image object
 */
Image generatePetalModel(int length, int topWidth, int topCurvature, int pointOffset, double sideCurveFactor, Pixel color) {

    // Generate the image based on the size
    int imageWidth = (length + pointOffset) * 3;
    // Turn imageWidth into the highest 100 multiple
    imageWidth = (imageWidth / 100 + 1) * 100;
    int imageHeight = imageWidth;
    Image petalImage(imageWidth, imageHeight);

    // Get the center point
    Point center(imageWidth / 2, imageHeight / 2);

    Point top(center.x, center.y + length);

    // Get the side points
    Point sideR(top.x + topWidth / 2, top.y);
    Point sideL(top.x - topWidth / 2, top.y);

    top.y = top.y + topCurvature/2 + pointOffset;

    std::cout << "center: " << center << ", top: " << top << std::endl;

    //petalImage.drawLine(color, center, top, 0);
    //petalImage.drawLine(color, sideR, sideL, 0);
    petalImage.drawCurve(color, sideR, sideL, -topCurvature);
    petalImage.drawCurve(color, center, sideR, -topWidth * sideCurveFactor);
    petalImage.drawCurve(color, center, sideL, topWidth * sideCurveFactor);
    //petalImage.drawCurve(color, top, sideL, -topWidth / 20);
    //petalImage.drawCurve(color, top, sideR, topWidth / 20);

    // flood fill center of the petal (between center and top)
    Point centerTop((center.x + top.x) / 2, (center.y + top.y) / 2);
    petalImage.floodNoRepPixel(color, centerTop);


    return petalImage;
}

/**
 * @brief Draw a filled circle with a border on the image.
 *
 * This function draws a filled circle on the provided image with the specified fill color
 * and a border circle with a different color to create a border effect.
 *
 * @param img The Canvas object to draw on.
 * @param fillColor The color to fill the inner circle (Pixel object).
 * @param borderColor The color to use for the border circle (Pixel object).
 * @param center The center coordinates of the circle (Point object).
 * @param radius The radius of the outer circle, which determines the size of the filled circle and its border.
 */
void drawFilledCircleWithBorder(Canvas& img, Pixel fillColor, Pixel borderColor, Point center, int radius) {
    // Draw the filled circle with the fillColor
    drawCircle(img, fillColor, center, radius);

    // Draw a slightly smaller circle with the borderColor to create the border effect
    drawCircle(img, borderColor, center, radius - 1);
}

/**
 * @brief Add noise to an Canvas object.
 * 
 * This function adds noise to an Canvas object. The noise is added to each non-black pixel
 * with a probability determined by the noiseDensity parameter. The noise is a random value
 * between -noiseSpread and +noiseSpread. The noise is added to each color channel (red, green,
 * and blue) with a random value between -noiseColorfulness and +noiseColorfulness. The noise
 * values are then clamped to the range [0, noiseSaturation].
 * 
 * @param img This is a reference to the Canvas object you want to add noise to. It's the canvas you'll be modifying.
 * @param noiseDensity This parameter determines the probability of adding noise to each non-black pixel. It's a value between 0 and 1, where 0 means no noise is added, and 1 means noise is added to all non-black pixels.
 * @param noiseSpread This parameter controls the spread or intensity of the noise. A higher value will result in more significant deviations from the original pixel values.
 * @param noiseColorfulness This parameter controls the colorfulness of the noise. A higher value will result in more colorful noise. It's a value between 0 and 1, where 1 means no color is added, and 0 means the noise is as colorful as possible.
 * @param noiseSaturation This parameter sets the upper limit for the color values of the noise. It ensures that the noise values do not exceed this limit for each color channel (red, green, and blue).
 * 
 */
void addNoise(Canvas& img, double noiseDensity, int noiseSpread, int noiseColorfulness, int noiseSaturation) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int x = 0; x < img.getWidth(); x++) {
        for (int y = 0; y < img.getHeight(); y++) {
            Pixel& pixel = img.getPixels()[y * img.getWidth() + x];
            if (pixel.getRed() + pixel.getGreen() + pixel.getBlue() > 0 && dis(gen) < noiseDensity) {

                //Random value between -noiseSpread and +noiseSpread
                int radius = rand() % (2 * noiseSpread) - noiseSpread;

                int noiseR = pixel.getRed() + radius + (rand() % (2 * noiseColorfulness) - noiseColorfulness);
                int noiseG = pixel.getGreen() + radius + (rand() % (2 * noiseColorfulness) - noiseColorfulness);
                int noiseB = pixel.getBlue() + radius + (rand() % (2 * noiseColorfulness) - noiseColorfulness);

                // Ensure that the noise values do not exceed the specified saturation
                noiseR = std::min(std::max(noiseR, 0), noiseSaturation);
                noiseG = std::min(std::max(noiseG, 0), noiseSaturation);
                noiseB = std::min(std::max(noiseB, 0), noiseSaturation);

                pixel.setRed(noiseR);
                pixel.setGreen(noiseG);
                pixel.setBlue(noiseB);
            }
        }
    }
}

/**
 * @brief Draw a poppy on the image.
 * 
 * @param img This is a reference to the Canvas object you want to draw on. It's the canvas you'll be modifying.
 * @param pos This parameter represents the X and Y coordinates of the poppy's center position on the canvas.
 * @param sizeFactor This parameter determines the size of the poppy. It scales the radius of the main circle and the circles around it.
 * @param darkenFactor This new parameter controls how much the colors are darkened or made more opaque when drawing the poppy. A higher darkenFactor will result in darker colors.
 * @param layer This parameter represents the layer on which the poppy will be drawn.
 */
void drawFlower(Canvas& img, Point pos, double sizeFactor, double darkenFactor, TextureZone layer) {

    if (darkenFactor > 0.99)
        darkenFactor = 0.99;

    if (sizeFactor > 0.99)
        sizeFactor = 0.99;

    if (sizeFactor < 0.01)
        sizeFactor = 0.01;


    // Calculate the radius of the main circle based on sizeFactor
    int circleRadius = img.getScale() * sizeFactor;

    // Get the colors for the poppy
    Pixel main_color = getRandomFlowerColor().getDarkened(darkenFactor);
    Pixel petal_color = getRandomFlowerColorExcept(getFlowerColor(main_color)).getDarkened(darkenFactor);
    Pixel pistil_color = getRandomFlowerColorExcept(getFlowerColor(main_color)).getDarkened(darkenFactor);

    std::cout << "Drawing poppy at " << pos.x << ", " << pos.y << " with radius " << circleRadius << " with colors: " << main_color << ", " << petal_color << ", " << pistil_color << std::endl;

    // Draw the base petal circle
    drawCircle(img, petal_color, pos, circleRadius);
    
    
    // Draw the center circle
    drawCircle(img, main_color, pos, circleRadius / 2);

    // Draw circles around the main circle as petals

    // Random petal count between 5 and 10
    int petalCount = 5 + rand() % 6;
    double angleIncrement = 2 * M_PI / petalCount;
    for (int i = 0; i < petalCount; i++) {
        // Calculate the position of the petal
        Point petalPos;
        petalPos.x = pos.x + circleRadius * cos(i * angleIncrement);
        petalPos.y = pos.y + circleRadius * sin(i * angleIncrement);

        drawCircle(img, petal_color, petalPos, circleRadius / 2);
    }

    // Draw a small black circle in the center (darkened)
    // Get a random number between 0.12 and 0.40
    double circleRadiusMult = 0.12 + (rand() % 100) / 100.0 * 0.28;

    circleRadius = circleRadius * circleRadiusMult;
    if (circleRadius < 1) {
        circleRadius = 1;
    }
    
    for (int x = pos.x - circleRadius; x <= pos.x + circleRadius; x++) {
        for (int y = pos.y - circleRadius; y <= pos.y + circleRadius; y++) {
            // Check if the pixel is within the circle using the circle equation
            if ((x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y) <= circleRadius * circleRadius) {
                img.setPixel(pistil_color, x, y); // Darkened color for the circle
            }
        }
    }
}

void drawFlowerCrown(Canvas& img, Point pos, double sizeFactor, double darkenFactor, TextureZone layer, double petalExtraRotation, double petalExtraOffsetDivider) {

    if (darkenFactor > 0.99)
        darkenFactor = 0.99;

    if (sizeFactor > 0.99)
        sizeFactor = 0.99;

    if (sizeFactor < 0.01)
        sizeFactor = 0.01;

    // Calculate the radius of the main circle based on sizeFactor
    int circleRadius = img.getScale() * sizeFactor / 10;

    // Get the colors for the crown
    Pixel petal_color = getRandomFlowerColor();

    // Random petal count
    int petalCount = 6 + rand() % 6;
    double angleIncrement = 2 * M_PI / petalCount;
    int petalWidth = (12 / petalCount) * img.getScale() / 100;

    std::cout << "Drawing " << petalCount << " petals with width " << petalWidth << std::endl;
    for (int i = 0; i < petalCount; i++) {
        // Calculate the position of the petal
        Point petalPos;
        Point petalEndPos;
        petalPos.x = pos.x + circleRadius * cos(i * angleIncrement + petalExtraRotation);
        petalPos.y = pos.y + circleRadius * sin(i * angleIncrement + petalExtraRotation);

        // Convert the angle to degrees
        int degreeIncrement = angleIncrement * 180 / M_PI;

        double genericPetalAngle = (360 / petalCount);

        int angleStart = (degreeIncrement * i) - genericPetalAngle / petalExtraOffsetDivider;
        int angleEnd = angleStart + genericPetalAngle;

        std::cout << "Drawing petal at " << petalPos << " with angle start " << angleStart << " and angle end " << angleEnd << std::endl;
       

        drawPartialCheeseWheel(img, circleRadius * 5, angleStart, angleEnd, petalPos, petal_color);
    }

}


/**
 * @brief Draw grass on the image.
 * 
 * This function draws grass on the provided layer, on the image with the specified color.
 * The height of the grass will stay within the layer's height range, and lower heightFactor
 * values will result in shorter grass. The density of the grass can be controlled with the
 * density parameter. Higher density values will result in more grass lines.
 * 
 * @param img This is a reference to the Canvas object you want to draw on. It's the canvas you'll be modifying.
 * @param layer This parameter represents the layer on which the grass will be drawn.
 * @param color The color of the grass (Pixel object).
 * @param darkenFactor A factor to control the darkness of the grass color (0.0 - 1.0). 0.0 means maximum darkening, 1.0 means no darkening (original color).
 * @param heightFactor A factor to control the maximum height of the grass lines (0.0 - 1.0). 0.0 means very short grass, 1.0 means grass can reach the entire layer height.
 * @param density A factor to control the density of the grass lines (0.0 - 1.0). 0.0 means no grass, 1.0 means maximum density.
 */
void drawFlatGrass(Canvas& img, TextureZone zone, Pixel color, double darkenFactor, double heightFactor, double density) {

    if ( darkenFactor > 0.99)
        darkenFactor = 0.99;
    
    if (heightFactor > 0.99)
        heightFactor = 0.99;

    if (density > 0.99)
        density = 0.99;
    
    // get a random number of blade of grass to populate the zone
    int min_blade_count = (zone.GetSurfaceArea() / img.getScale()) * 10;
    int max_blade_count = (zone.GetSurfaceArea() / img.getScale()) * 20;
    int bladeCount = min_blade_count + rand() % (max_blade_count - min_blade_count);
    bladeCount = (int)(bladeCount * density);

    std::cout << "Drawing " << bladeCount << " blades of grass" << std::endl;

    for (int i = 0; i < bladeCount; i++) {
        // Random position
        Point pos = zone.GetRandomAvailablePosition(&img);

        // Random height
        int min_height = (int)((img.getScale() / 20) * (heightFactor / 2));
        int max_height = (int)((img.getScale() / 20) * heightFactor);
        int height = rand() % (max_height - min_height) + min_height;

        // Random angle
        int angle = rand() % (height / 2);
        // 1/2 chance to be negative
        if (rand() % 2 == 0) {
            angle = -angle;
        }

        // Random darkening
        double random_darken_factor = (darkenFactor - 0.1 + (rand() % 100) / 100.0 * 0.2);

        // Random thickness
        int thickness = 1 + rand() % img.getScale() / 500;


        // Draw the grass line
        drawLine(img, color.getDarkened(random_darken_factor), pos, Point(pos.x - angle, pos.y + height), thickness);
    }
}

int main()
{
    // Generate a seed for the random number generator
    srand(time(NULL));

    // Create an image with scale
    Canvas img(4000, 4000, 2000);

    if (img.getScale() < 160)
    {
        std::cout << "Scale is too small" << std::endl;
        return 1;
    }


    //Setup layers
    int layer_height_pixel = (int)((img.getScale() / 1000) * 7);
    std::cout << "Layer height: " << layer_height_pixel << " for image with height: " << img.getHeight() << std::endl;

    int step_pixel = (int)(layer_height_pixel / 2);
    std::cout << "Step: " << step_pixel << std::endl;

    TextureZone poppy_zone(Point(0, 0), Point(img.getWidth(), img.getHeight()));
    TextureZone grass_zone(Point(0, 0), Point(img.getWidth(), img.getHeight()));

    //----------------------------------------------------------------------------------
    // Grass
    //----------------------------------------------------------------------------------

    drawFlatGrass(img, grass_zone, Pixel(0, 200, 0), 0.20, 0.5, 1.0);
    drawFlatGrass(img, grass_zone, Pixel(0, 200, 0), 0.50, 0.7, 0.4);
    drawFlatGrass(img, grass_zone, Pixel(0, 200, 0), 0.75, 1.0, 0.2);

    //----------------------------------------------------------------------------------
    // Poppies
    //----------------------------------------------------------------------------------

    // get a random number of poppies to populate the zone
    int poppyCount = 1 + rand() % ((poppy_zone.GetSurfaceArea() / img.getScale()) / 10);

    std::cout << "Drawing " << poppyCount << " poppies" << std::endl;

    for (int i = 0; i<poppyCount; i++)
    {
        // Random position
        Point pos = poppy_zone.GetRandomAvailablePosition(&img);

        // Size factor
        double sizeFactor = 0.005 + (rand() % 100) / 100.0 * 0.015;

        //Darken factor
        double darkenFactor = 0.5 + (rand() % 100) / 100.0 * 0.5;

        drawFlower(img, pos, sizeFactor, darkenFactor, poppy_zone);
    }

    drawFlatGrass(img, grass_zone, Pixel(0, 200, 0), 0.75, 1.0, 0.05);

    //----------------------------------------------------------------------------------
    // Roses
    //----------------------------------------------------------------------------------

    /*
    drawFlowerCrown(img, Point(img.getWidth()/2, img.getHeight()/2), 0.05, 1.0, poppy_zone, 0, 2);
    drawFlowerCrown(img, Point(img.getWidth()/2, img.getHeight()/2), 0.045, 1.0, poppy_zone, 0, 4);
    drawFlowerCrown(img, Point(img.getWidth()/2, img.getHeight()/2), 0.04, 1.0, poppy_zone, 0, 4);
    drawFlowerCrown(img, Point(img.getWidth()/2, img.getHeight()/2), 0.035, 1.0, poppy_zone, 0, 2);
    drawFlowerCrown(img, Point(img.getWidth()/2, img.getHeight()/2), 0.03, 1.0, poppy_zone, 0, 6);
    drawCircle(img, getRandomFlowerColor(), Point(img.getWidth()/2, img.getHeight()/2), 50);
    */

    std::cout << "Adding noise" << std::endl;
    addNoise(img, 1, 10, 1, 255);

    //----------------------------------------------------------------------------------
    // Testing
    //----------------------------------------------------------------------------------
    
    Canvas test(100, 100, 100);
    Image test_image(100, 100);

    Point pixelPos;
    // Draw a 50 by 50 empty square on the image
    for (int x = -10; x < 40; x++)
    {
        for (int y = -10; y < 40; y++)
        {
            pixelPos.x = x;
            pixelPos.y = y;
            if (x == -10 || x == 39 || y == -10 || y == 39)
            {
                test_image.setRepPixel(Pixel(255, 0, 0), pixelPos);
            }
        }
    }

    /*test_image.floodRepPixel(Pixel(0, 255, 0), Point(10, 10));
    test_image.floodRepPixel(Pixel(0, 0, 255), Point(42, 42));*/

    //drawPartialEmptyCircle(test, 100, 0, 180, Point(500, 500), Pixel(255, 0, 0));

    Image image=generatePetalModel(120, 60, 40, 2, 0.5, Pixel(255, 0, 0));
    Image image2=generatePetalModel(100, 40, 30, 2, 0.5, Pixel(0, 255, 0));
    std::cout << "Generated petal models: " << image << ", " << image2 << std::endl;

    //Rotating
    //image.rotateImage(45);
    
    std::cout << "Exporting images" << std::endl;

    img.exportImage("output.bmp", 1, 1);
    image.exportImage("petal.bmp", 1, 1);
    image2.exportImage("petal2.bmp", 1, 1);
    //test.exportImage("test.bmp", 1, 1);
    //test_image.exportImage("floodfilltest.bmp", 1, 1);

    return 0;
}