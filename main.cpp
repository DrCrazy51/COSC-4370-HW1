#include <iostream>
#include "BMP.h"
#include <cmath>

void drawEllipse(BMP &bmp, int xc, int yc, int a, int b) {
    int x = 0, y = b; //start at topmost position of (0,25)
    int a2 = a * a, b2 = b * b; //a^2 and b^2
    int d1 = b2 - a2 * b + 0.25 * a2; //decision parameter used to determine what direction to go for region 1 part of function
    int dx = 2 * b2 * x, dy = 2 * a2 * y;

    // Region 1
    while (dx < dy) { //while condition checks for if the slope is steep still or not
        bmp.set_pixel(xc - x, yc + y, 255, 255, 255, 0);
        bmp.set_pixel(xc - x, yc - y, 255, 255, 255, 0); //xc -x because we only want to show ellipse in 2nd and 3rd quadrant
        if (d1 < 0) { // if d1 is negative, go right (E)
            x++;
            dx += 2 * b2;
            d1 += dx + b2;
        } else {
            x++; //if d1 is positive, go right and down (SE)
            y--;
            dx += 2 * b2;
            dy -= 2 * a2;
            d1 += dx - dy + b2;
        }
    }

    // Region 2 
    int d2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2; //decision parameter to determine direction for region 2
    while (y >= 0) { //reaches Region 2 once the slope gets flattened out, (dx >= dy)
        bmp.set_pixel(xc - x, yc + y, 255, 255, 255, 0);
        bmp.set_pixel(xc - x, yc - y, 255, 255, 255, 0);
        if (d2 > 0) { //if d2 is positive, direction is downward (S)
            y--;
            dy -= 2 * a2;
            d2 += a2 - dy;
        } else {
            x++; //if d2 is negative, direction is downward and right (SE)
            y--;
            dx += 2 * b2;
            dy -= 2 * a2;
            d2 += dx - dy + a2;
        }
    }
}

int main() {
    const int width = 200, height = 200;
    BMP bmpNew(width, height, false);
    bmpNew.fill_region(0, 0, width, height, 0, 0, 0, 0);
    drawEllipse(bmpNew, 100, 100, 16, 25);
    bmpNew.write("output.bmp");
    return 0;
}

