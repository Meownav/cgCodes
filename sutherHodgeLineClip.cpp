#include <iostream>
#include <cmath>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int computeCode(double x, double y, int x_max, int x_min, int y_max, int y_min)
{
    int code = INSIDE;

    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;

    return code;
}

void cohenSutherlandClip(double x1, double y1, double x2, double y2, int x_min, int x_max, int y_min, int y_max)
{
    int code1 = computeCode(x1, y1, x_max, x_min, y_max, y_min);
    int code2 = computeCode(x2, y2, x_max, x_min, y_max, y_min);
    bool accept = false;

    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            break;
        }
        else
        {
            int code_out;
            double x, y;

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP)
            {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, x_max, x_min, y_max, y_min);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2, x_max, x_min, y_max, y_min);
            }
        }
    }
    accept
        ? std::cout << "Line accepted from " << x1 << ", " << y1 << " to " << x2 << ", " << y2 << std::endl
        : std::cout << "Line rejected" << std::endl;
}

int main()
{
    double x1, y1, x2, y2, x_max, x_min, y_max, y_min;
    std::cout << "Enter x1, y1, x2, y2:" << std::endl;
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << "Enter xMin, yMin, xMax, yMax";
    std::cin >> x_min >> y_min >> x_max >> y_max;
    cohenSutherlandClip(x1, y1, x2, y2, x_min, x_max, y_min, y_max);
}
