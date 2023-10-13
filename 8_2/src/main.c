#include "main.h"

#include <memory.h>
#include <stdlib.h>

void AddHorizontalLineToImage(ppm *image) {
  if (NULL == image) {
    return;
  }

  for (unsigned int x_coordinate = 0; x_coordinate < kImageWidth;
       x_coordinate++) {
    set_pixel(image, x_coordinate, kImageHeight / 2, make_pixel(0, 0, 0));
  }
}

void AddHorizontalLineWithThicknessToImage(ppm *image,
                                           const unsigned short thickness) {
  if (NULL == image || 0 == thickness || kImageHeight < thickness ||
      kImageWidth < thickness) {
    return;
  }

  const unsigned int kVerticalPosition = kImageHeight / 2;
  const unsigned int kNumberOfRowsFromBaseLine = thickness / 2;
  unsigned int upper_limit_row = kVerticalPosition + kNumberOfRowsFromBaseLine;

  if (1 == thickness % 2) {
    upper_limit_row++;
  }

  for (unsigned int x_coordinate = 0; x_coordinate < kImageWidth;
       x_coordinate++) {
    for (unsigned int y_coordinate =
             kVerticalPosition - kNumberOfRowsFromBaseLine;
         y_coordinate < upper_limit_row; y_coordinate++) {
      set_pixel(image, x_coordinate, y_coordinate, make_pixel(0, 0, 0));
    }
  }
}

void AddVerticalLineToImage(ppm *image) {
  if (NULL == image) {
    return;
  }

  const unsigned int kColumn[kImageHeight] = {0};

  // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
  memcpy(image->pixels[kImageWidth / 2], kColumn, sizeof(kColumn));
}

void AddVerticalLineWithThicknessToImage(ppm *image,
                                         const unsigned short thickness) {
  if (NULL == image || 0 == thickness || kImageHeight < thickness ||
      kImageWidth < thickness) {
    return;
  }

  const unsigned int kColumn[kImageHeight] = {0};
  const unsigned int kStartColumn = (kImageWidth / 2) - (thickness / 2);

  for (unsigned int x_coordinate = kStartColumn;
       x_coordinate < kStartColumn + thickness; x_coordinate++) {
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    memcpy(image->pixels[x_coordinate], kColumn, sizeof(kColumn));
  }
}

void AddFilledRectangleToImage(ppm *image, Color *color) {
  for (unsigned int x_coordinate = kImageWidth / 4;
       x_coordinate < (kImageWidth / 4) * 3; x_coordinate++) {
    for (unsigned int y_coordinate = kImageHeight / 4;
         y_coordinate < (kImageHeight / 4) * 3; y_coordinate++) {
      set_pixel(image, x_coordinate, y_coordinate,
                make_pixel(color->red, color->green, color->blue));
    }
  }
}

void PlotCirclePoints(ppm *image, unsigned int x_coordinate,
                      unsigned int y_coordinate, Color *color) {
  const unsigned int kXCenter = kImageWidth / 2;
  const unsigned int kYCenter = kImageHeight / 2;

  set_pixel(image, kXCenter + x_coordinate, kYCenter + y_coordinate,
            make_pixel(color->red, color->green, color->blue));
  set_pixel(image, kXCenter + x_coordinate, kYCenter - y_coordinate,
            make_pixel(color->red, color->green, color->blue));
  set_pixel(image, kXCenter - x_coordinate, kYCenter + y_coordinate,
            make_pixel(color->red, color->green, color->blue));
  set_pixel(image, kXCenter - x_coordinate, kYCenter - y_coordinate,
            make_pixel(color->red, color->green, color->blue));
  set_pixel(image, kXCenter + y_coordinate, kYCenter + x_coordinate,
            make_pixel(color->red, color->green, color->blue));
  set_pixel(image, kXCenter + y_coordinate, kYCenter - x_coordinate,
            make_pixel(color->red, color->green, color->blue));
  set_pixel(image, kXCenter - y_coordinate, kYCenter + x_coordinate,
            make_pixel(color->red, color->green, color->blue));
  set_pixel(image, kXCenter - y_coordinate, kYCenter - x_coordinate,
            make_pixel(color->red, color->green, color->blue));
}

void AddCircleToImage(ppm *image, int radius, Color *color) {
  int x_coordinate = 0;
  int y_coordinate = radius;
  int decision = 1 - radius;

  PlotCirclePoints(image, x_coordinate, y_coordinate, color);

  while (y_coordinate > x_coordinate) {
    if (decision < 0) {
      decision += 2 * x_coordinate + 3;
    } else {
      // NOLINTNEXTLINE(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
      decision += 2 * (x_coordinate - y_coordinate) + 5;
      y_coordinate -= 1;
    }

    x_coordinate += 1;

    PlotCirclePoints(image, x_coordinate, y_coordinate, color);
  }
}

int main() {
  // NOLINTBEGIN(readability-magic-numbers)
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  ppm *image_one =
      make_image(kImageWidth, kImageHeight, make_pixel(255, 255, 255));
  AddHorizontalLineToImage(image_one);
  write_image(image_one, "image_one.pnm");

  ppm *image_two =
      make_image(kImageWidth, kImageHeight, make_pixel(255, 255, 255));
  AddVerticalLineToImage(image_two);
  write_image(image_two, "image_two.pnm");

  ppm *image_three =
      make_image(kImageWidth, kImageHeight, make_pixel(255, 255, 255));
  AddHorizontalLineWithThicknessToImage(image_three, 6);
  write_image(image_three, "image_three.pnm");

  ppm *image_four =
      make_image(kImageWidth, kImageHeight, make_pixel(255, 255, 255));
  AddVerticalLineWithThicknessToImage(image_four, 5);
  write_image(image_four, "image_four.pnm");

  ppm *image_five =
      make_image(kImageWidth, kImageHeight, make_pixel(255, 255, 255));
  AddFilledRectangleToImage(image_five, &(struct Color){252, 186, 3});
  write_image(image_five, "image_five.pnm");

  ppm *image_six =
      make_image(kImageWidth, kImageHeight, make_pixel(255, 255, 255));
  AddCircleToImage(image_six, 150, &(struct Color){252, 186, 3});
  write_image(image_six, "image_six.pnm");
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
  // NOLINTEND(readability-magic-numbers)

  return EXIT_SUCCESS;
}
