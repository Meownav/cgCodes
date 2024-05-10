#include <iostream>

int main()
{
    std::cout << "Enter the start and end points.";
    float x, y, xn, yn;
    std::cin >> x >> y;
    std::cin >> xn >> yn;
    float dx = xn - x;
    float dy = yn - y;
    float m = dy / dx;
    std::cout << x << "   " << y << std::endl;

    while ((x < xn))
    {
        if (dx < dy)
        {
            x += (1 / m);
            y++;
            std::cout << x << "   " << y << std::endl;
        }
        else
        {
            x++;
            y += m;
            std::cout << x << "   " << y << std::endl;
        }
    }
}