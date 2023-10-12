#ifndef EXERCISES_8_2_SRC_MAIN_H_
#define EXERCISES_8_2_SRC_MAIN_H_

#include "ppm.h"

enum Constants { kImageWidth = 500, kImageHeight = 500 };

typedef struct Color {
  unsigned short red;
  unsigned short green;
  unsigned short blue;
} Color;

void AddHorizontalLineToImage(ppm *image);

void AddHorizontalLineWithThicknessToImage(ppm *image,
                                           unsigned short thickness);

void AddVerticalLineToImage(ppm *image);

void AddVerticalLineWithThicknessToImage(ppm *image, unsigned short thickness);

void AddFilledRectangleToImage(ppm *image, Color *color);

void PlotCirclePoints(ppm *image, unsigned int x_coordinate,
                      unsigned int y_coordinate, Color *color);

/**
 * @brief This function uses the midpoint circle algorithm to add a circle to
 * the PPM image.
 *
 * @param image The image data.
 * @param radius The circle's radius.
 * @param color RGB color parameters.
 */
void AddCircleToImage(ppm *image, int radius, Color *color);

#endif  // EXERCISES_8_2_SRC_MAIN_H_
