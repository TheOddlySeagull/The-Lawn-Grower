#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>
#include <unistd.h>
#include <thread>

#include "Canvas.hpp"
#include "FlowerColors.hpp"
#include "Point.hpp"
#include "TextureZone.hpp"

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
Image generatePetalModel(petal_values petal) {

    // Generate the image based on the size
    int imageWidth = (petal.length + petal.pointOffset) * 3;
    // Turn imageWidth into the highest 100 multiple
    imageWidth = (imageWidth / 100 + 1) * 100;
    int imageHeight = imageWidth;
    Image petalImage(imageWidth, imageHeight);

    // Get the center point
    Point center(imageWidth / 2, imageHeight / 2);

    Point top(center.x, center.y + petal.length);

    // Get the side points
    Point sideR(top.x + petal.topWidth / 2, top.y);
    Point sideL(top.x - petal.topWidth / 2, top.y);

    top.y = top.y + petal.topCurvature/2 + petal.pointOffset;

    //std::cout << "center: " << center << ", top: " << top << std::endl;

    //petalImage.drawLine(color, center, top, 0);
    //petalImage.drawLine(color, sideR, sideL, 0);
    petalImage.drawCurve(petal.color, sideR, sideL, -petal.topCurvature);
    petalImage.drawCurve(petal.color, center, sideR, -petal.topWidth * petal.sideCurveFactor);
    petalImage.drawCurve(petal.color, center, sideL, petal.topWidth * petal.sideCurveFactor);
    //petalImage.drawCurve(color, top, sideL, -topWidth / 20);
    //petalImage.drawCurve(color, top, sideR, topWidth / 20);

    // flood fill center of the petal (between center and top)
    Point centerTop((center.x + top.x) / 2, (center.y + top.y) / 2);
    petalImage.floodNoRepColor(petal.color, centerTop);


    return petalImage;
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
void drawPoppyFlower(Canvas& img, Point pos, double sizeFactor, double darkenFactor, TextureZone layer) {

    if (darkenFactor > 0.99)
        darkenFactor = 0.99;

    if (sizeFactor > 0.99)
        sizeFactor = 0.99;

    if (sizeFactor < 0.01)
        sizeFactor = 0.01;


    // Calculate the radius of the main circle based on sizeFactor
    int circleRadius = img.getScale() * sizeFactor;

    std::vector<Color> petal_color_list;

    // Get the colors for the poppy
    Color main_color = getRandomFlowerColor();
    petal_color_list.push_back(main_color);

    Color petal_color = getRandomFlowerColorExcept(petal_color_list);
    petal_color_list.push_back(petal_color);

    Color pistil_color = getRandomFlowerColorExcept(petal_color_list);

    std::cout << "Drawing Flower (poppy type) with colors: " << main_color << ", " << petal_color << ", " << pistil_color << std::endl;

    // Draw the base petal circle
    img.drawCircle(petal_color, pos, circleRadius);
    
    
    // Draw the center circle
    img.drawCircle(main_color, pos, circleRadius / 2);

    // Random petal count between 5 and 10
    int petalCount = 5 + rand() % 6;
    double angleIncrement = 2 * M_PI / petalCount;
    for (int i = 0; i < petalCount; i++) {
        // Calculate the position of the petal
        Point petalPos;
        petalPos.x = pos.x + circleRadius * cos(i * angleIncrement);
        petalPos.y = pos.y + circleRadius * sin(i * angleIncrement);

        img.drawCircle(petal_color, petalPos, circleRadius / 2);
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
            // Check if the Color is within the circle using the circle equation
            if ((x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y) <= circleRadius * circleRadius) {
                img.setRepColor(pistil_color, new Point(x, y));
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
    Color petal_color = getRandomFlowerColor();

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
       

        img.drawPartialCheeseWheel(circleRadius * 5, angleStart, angleEnd, petalPos, petal_color);
    }

}

Image generatePetaledFlower(petal_values petal_1_values, petal_values petal_2_values, petal_values petal_3_values, bool get_stepped = false) {

    // Generate the petal models
    Image petal_1=generatePetalModel(petal_1_values);
    Image petal_2=generatePetalModel(petal_2_values);
    Image petal_3=generatePetalModel(petal_3_values);

    // Generate the canvas for the flower
    Image final_image(500, 500);

    // Create a placeholder image to store the half of the flower to avoid the last petal overlapping
    Image half_final_image(500, 500);

    // If get_stepped is true, create a placeholder image to store the stepped version of the flower generation
    Image final_stepped_image(500, 500);

    // Get a random number of petals to populate the flower (between 5 and 13)
    int petal_count = 5 + rand() % 8;

    // Trim the petal 1 and 2 to the same size
    petal_1.trim(500, 500);
    petal_2.trim(500, 500);

    // Merge the petal 1 and 2 to create the main petal model
    Image main_petal(petal_1);
    main_petal.merge(petal_2);

    // Rotate the petal 3 to create the secondary petal crown of the flower
    petal_3.rotate(360 / petal_count / 2);

    // Generate the main petal crown
    for (int i = 0; i < petal_count; i++) {

        //Rotating
        main_petal.rotate(360 / petal_count);

        //Trim
        main_petal.trim(final_image.getWidth(), final_image.getHeight());

        // If at the half of the petal count, save the image
        if (i == int(petal_count / 2)) {
            //std::cout << "Saving half image at " << i << " petals." << std::endl;
            half_final_image.merge(final_image);
        }

        //Merging
        // If last petal
        if (i == petal_count - 1) {
            //std::cout << "Merging last petal at " << i << " petals." << std::endl;
            final_image.mergeExcept(main_petal, half_final_image);
        }
        else {
            final_image.merge(main_petal);
        }

        if (get_stepped)
            final_stepped_image.expand(final_image);
    
    }

    // Generate the secondary petal crown
    for (int i = 0; i < petal_count; i++) {
        petal_3.rotate(360 / petal_count);
        petal_3.trim(final_image.getWidth(), final_image.getHeight());
        final_image.merge(petal_3);
    }

    if (get_stepped)
        final_stepped_image.expand(final_image);

    // Return the final image
    if (get_stepped)
        return final_stepped_image;
    else
        return final_image;

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
 * @param color The color of the grass (Color object).
 * @param darkenFactor A factor to control the darkness of the grass color (0.0 - 1.0). 0.0 means maximum darkening, 1.0 means no darkening (original color).
 * @param heightFactor A factor to control the maximum height of the grass lines (0.0 - 1.0). 0.0 means very short grass, 1.0 means grass can reach the entire layer height.
 * @param density A factor to control the density of the grass lines (0.0 - 1.0). 0.0 means no grass, 1.0 means maximum density.
 */
void drawFlatGrass(Canvas& img, TextureZone zone, Color color, double darkenFactor, double heightFactor, double density) {

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
        img.drawLine(color.getDarkened(random_darken_factor), pos, Point(pos.x - angle, pos.y + height), thickness);
   
    }
}


//drawPetaledFlower
void drawPetaledFlower(Canvas& main_canvas, Point pos, petal_values petal_1_values, petal_values petal_2_values, petal_values petal_3_values) {


    // Get the petaled flower
    Image petaled_flower = generatePetaledFlower(petal_1_values, petal_2_values, petal_3_values);

    // Scale up/down
    petaled_flower.scale(main_canvas.getScale());

    // Draw the petaled flower
    main_canvas.mergeLayerRep(petaled_flower, pos);
}

    

int main()
{
    // Generate a seed for the random number generator
    srand(time(NULL));

    // Create an image with scale
    Canvas main_canvas(4000, 4000, 2000);

    if (main_canvas.getScale() < 160)
    {
        std::cout << "Scale is too small" << std::endl;
        return 1;
    }

    // Define the zones to populate
    TextureZone poppy_zone(Point(0, 0), Point(main_canvas.getWidth(), main_canvas.getHeight()));
    TextureZone grass_zone(Point(0, 0), Point(main_canvas.getWidth(), main_canvas.getHeight()));

    //----------------------------------------------------------------------------------
    // Grass
    //----------------------------------------------------------------------------------
    
    drawFlatGrass(main_canvas, grass_zone, Color(0, 200, 0), 0.20, 0.5, 1.0);
    drawFlatGrass(main_canvas, grass_zone, Color(0, 200, 0), 0.50, 0.7, 0.4);
    drawFlatGrass(main_canvas, grass_zone, Color(0, 200, 0), 0.75, 1.0, 0.2);

    //----------------------------------------------------------------------------------
    // Flower counts
    //----------------------------------------------------------------------------------

    // get a random number of poppies to populate the zone
    int poppyCount = 1 + rand() % ((poppy_zone.GetSurfaceArea() / main_canvas.getScale()) / 20);

    // get a random number of petaled flowers to populate the zone
    int petaledCount = 1 + rand() % ((poppy_zone.GetSurfaceArea() / main_canvas.getScale()) / 20);

    std::cout << "Drawing " << petaledCount + poppyCount << " flowers: " << poppyCount << " poppy type and " << petaledCount << " petaled type" << std::endl;

    //----------------------------------------------------------------------------------
    // Poppy type flowers
    //----------------------------------------------------------------------------------

    // Draw the poppies
    for (int i = 0; i<poppyCount; i++)
    {

        std::cout << i + 1 << "/" << poppyCount << " - ";

        // Random position
        Point pos = poppy_zone.GetRandomAvailablePosition(&main_canvas);

        // Size factor
        double sizeFactor = 0.005 + (rand() % 100) / 100.0 * 0.015;

        //Darken factor
        double darkenFactor = 0.5 + (rand() % 100) / 100.0 * 0.5;

        drawPoppyFlower(main_canvas, pos, sizeFactor, darkenFactor, poppy_zone);
    }

    //----------------------------------------------------------------------------------
    // Petaled type flowers
    //----------------------------------------------------------------------------------
    
    // Draw the petaled flowers
    for (int i = 0; i<petaledCount; i++)
    {

        // Random position
        Point pos = poppy_zone.GetRandomAvailablePosition(&main_canvas);

        // Make a list of the used colors
        std::vector<Color> petal_color_list;

        // Random petal colors
        Color petal_color_1 = getRandomFlowerColor();
        petal_color_list.push_back(petal_color_1);

        Color petal_color_2 = getRandomFlowerColorExcept(petal_color_list);
        petal_color_list.push_back(petal_color_2);
        
        Color petal_color_3 = getRandomFlowerColorExcept(petal_color_list);

        std::cout  << i + 1 << "/" << petaledCount << " - Drawing Flower (petaled type) with colors: " << petal_color_1 << ", " << petal_color_2 << ", " << petal_color_3 << std::endl;

        //Create all the petal values
        petal_values petal_1_values = {100 + rand() % 100, 40 + rand() % 40, 30 + rand() % 30, 2 + rand() % 2, 0.5 + (rand() % 100) / 100.0 * 0.5, petal_color_1};
        petal_values petal_2_values = {80 + rand() % 100, 20 + rand() % 40, 20 + rand() % 30, 2 + rand() % 2, 0.5 + (rand() % 100) / 100.0 * 0.5, petal_color_2};
        petal_values petal_3_values = {60 + rand() % 100, 10 + rand() % 40, 10 + rand() % 30, 2 + rand() % 2, 0.5 + (rand() % 100) / 100.0 * 0.5, petal_color_3};

        //Run drawPetaledFlower on another thread
        std::thread t1(drawPetaledFlower, std::ref(main_canvas), pos, petal_1_values, petal_2_values, petal_3_values);
        t1.detach();
    }

    //----------------------------------------------------------------------------------
    // Grass again
    //----------------------------------------------------------------------------------

    drawFlatGrass(main_canvas, grass_zone, Color(0, 200, 0), 0.75, 1.0, 0.05);

    //----------------------------------------------------------------------------------
    // Other and finalization
    //----------------------------------------------------------------------------------
    
    std::cout << "Adding noise" << std::endl;
    main_canvas.addNoise(1, 10, 1, 255);

    std::cout << "Exporting images" << std::endl;

    // Export the image
    main_canvas.exportImage("output.bmp", 1, 1);

    std::cout << "Done" << std::endl;

    return 0;
}