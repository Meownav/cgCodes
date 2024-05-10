#include <iostream>

int main()
{
    float x, y, xn, yn, dx, dy, m, p;

    std::cout << "Enter init and final points.";
    std::cin >> x >> y >> xn >> yn;

    dx = xn - x;
    dy = yn - y;
    m = dy / dx;

    p = 2 * dy - dx;

    std::cout << x << "  " << y << std::endl;

    while (x < xn && y < yn)
    {
        if (p > 0)
        {
            x++;
            y++;
            if (m < 1)
            {
                p += 2 * (dy - dx);
            }
            else
            {
                p += 2 * (dx - dy);
            }
        }
        else
        {
            if (m < 1)
            {
                x++;
                p += 2 * dy;
            }
            else
            {
                y++;
                p += 2 * dx;
            }
        }
        std::cout << x << "  " << y << std::endl;
    }
}